/******************************************************************************
*    > File Name: 1.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年04月09日 星期三 20时07分25秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/types.h>
#include <asm/types.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <linux/if_packet.h>
#include <pcap.h>
#include <pthread.h>

#define MAC_BCAST_ADDR  (uint8_t *) "\xff\xff\xff\xff\xff\xff"
#define ETHER_LEN  sizeof(struct eth_header)
#define ARP_LEN  sizeof(struct arp_header)
pcap_t* pcap_handle;
char error_content[PCAP_ERRBUF_SIZE];
char *net_interface;

char bpf_filter_string[] = "arp";
bpf_u_int32 net_mask;
bpf_u_int32 net_ip;

struct eth_header {
    u_int8_t ether_dhost[6];
    u_int8_t ether_shost[6];
    u_int16_t ether_type;
};
typedef u_int32_t in_addr_t;

struct arp_header {
    u_int16_t arp_hardware_type;
    u_int16_t arp_protocol_type;
    u_int8_t arp_hardware_length;
    u_int8_t arp_protocol_length;
    u_int16_t arp_operation_code;
    u_int8_t arp_source_ethernet_address[6];
    u_int8_t arp_source_ip_address[4];
    u_int8_t arp_destination_ethernet_address[6];
    u_int8_t arp_destination_ip_address[4];
};

int get_interface(char *dev, char * mac, int maclen, struct in_addr *lc_addr, int iplen){
        int reqfd, n;
        struct ifreq macreq;
        reqfd = socket(AF_INET, SOCK_DGRAM, 0);
        strcpy(macreq.ifr_name, dev);
        /* 获取本地接口MAC地址*/
        if(ioctl(reqfd, SIOCGIFHWADDR, &macreq) != 0)
                return 1;
        memcpy(mac, macreq.ifr_hwaddr.sa_data, maclen);
        /* 获取本地接口IP地址*/
        if(ioctl(reqfd, SIOCGIFADDR, &macreq) != 0)
                return 1;
        memcpy(lc_addr, &((struct sockaddr_in *)(&macreq.ifr_addr))->sin_addr, iplen);
        return 0;
}
void arp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content) {
    struct arp_header *arp_protocol;
    u_short operation_code;
    u_char *mac_string;
    struct in_addr source_ip_address;

    arp_protocol = (struct arp_header *) (packet_content + 14);
    operation_code = ntohs(arp_protocol->arp_operation_code);
    if(operation_code == 2){
    memcpy((void *) & source_ip_address, (void *) & arp_protocol->arp_source_ip_address, sizeof (struct in_addr));
    printf("IP:%s ", inet_ntoa(source_ip_address));
    printf("MAC:");
    mac_string = arp_protocol->arp_source_ethernet_address;
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
    }
}

void capture(){
    struct bpf_program bpf_filter;
    printf("Capturing ARP packet.............\n");
        pcap_compile(pcap_handle, &bpf_filter, bpf_filter_string, 0, net_ip);
    pcap_setfilter(pcap_handle, &bpf_filter);
    if (pcap_datalink(pcap_handle) != DLT_EN10MB)
        return;
    pcap_loop(pcap_handle, -1, arp_protocol_packet_callback, NULL);
    pcap_close(pcap_handle);
}


int main() {
    struct arp_header a_header;
    struct eth_header e_header;
    struct in_addr local_addr;
    u_char *mac;
    int n;
    u_char frame[ETHER_LEN + ARP_LEN];
    unsigned long sendip;
    pthread_t tid;

    mac = (char *) malloc(ETH_ALEN);
    bzero(&a_header, sizeof (a_header));
    bzero(&e_header, sizeof (e_header));

    if (get_interface("eth0", mac, ETH_ALEN, &local_addr, 4)) {
        fprintf(stderr, "Error: Get host’s information failed\n");
        exit(0);
    }
    printf("Local IP:%s\n",inet_ntoa(local_addr.s_addr));


    memcpy(e_header.ether_dhost, MAC_BCAST_ADDR, ETH_ALEN);
    memcpy(e_header.ether_shost, mac, ETH_ALEN);
    e_header.ether_type = htons(ETHERTYPE_ARP);
    memcpy(frame, &e_header, ARP_LEN);
    a_header.arp_hardware_type = htons(ARPHRD_ETHER);
    a_header.arp_protocol_type = htons(ETHERTYPE_IP);
    a_header.arp_hardware_length = ETH_ALEN;
    a_header.arp_protocol_length = 4;
    a_header.arp_operation_code = htons(ARPOP_REQUEST);
    memcpy(a_header.arp_source_ethernet_address, mac, ETH_ALEN);
    memcpy(a_header.arp_source_ip_address, &local_addr, 4);

    net_interface = pcap_lookupdev(error_content);
    pcap_lookupnet(net_interface, &net_ip, &net_mask, error_content);
    pcap_handle = pcap_open_live(net_interface, BUFSIZ, 1, 0, error_content);

    printf("Local Net: %s \n",inet_ntoa(net_ip));
    printf("Net   Mask:%s \n", inet_ntoa(net_mask));
    if ((errno = pthread_create(&tid, NULL, capture, NULL)) < 0)
        perror("pthread:");
    sleep(1);
    for (n = 1; n < 255; n++) {
        sendip = htonl(net_ip) + n;
        inet_aton(inet_ntoa(htonl(sendip)), a_header.arp_destination_ip_address);
        memset(a_header.arp_destination_ethernet_address, 0, 6);
        memcpy(&frame[ETHER_LEN], &a_header, ARP_LEN);
        pcap_sendpacket(pcap_handle, frame, ETHER_LEN + ARP_LEN);
        //printf("Send IP: %s \n", inet_ntoa(htonl(sendip)));
    }

    pthread_join(tid, NULL);
    return 0;
}
