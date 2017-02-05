/******************************************************************************
*    > File Name: get_mac_ip.c
*
*    >Description:
*
*    >Version: 1.0
*    > Created Time: 2014年04月07日 星期一 20时28分31秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com
*    > Company:
*
******************************************************************************/
#include "arp.h"

/******************************************************************************
 * 功能：获取本地的ip地址，mac地址，子网掩码mask
 * 参数1：返回mac地址
 * 参数2：返回ip地址
 * 参数3：返回子网掩码
******************************************************************************/
void get_local_info(u_char *mac, struct in_addr *ip, struct in_addr *mask)
{
    int sockfd;
    struct ifreq req;
    struct sockaddr_in *sin;

    /*创建套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }

    memset(&req, 0, sizeof(req));
    strcpy(req.ifr_name, "eth0");

    /*获取本地mac地址*/
    if( ioctl(sockfd, SIOCGIFHWADDR, &req) == -1)
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    memcpy(mac, req.ifr_hwaddr.sa_data, ETH_ALEN);

    /*获取本地的ip地址*/
    if( ioctl(sockfd, SIOCGIFADDR, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sin = (struct sockaddr_in *)&req.ifr_addr;
    memcpy(ip, &sin->sin_addr, sizeof(struct in_addr));

    /*获取本地的mask地址*/
    if( ioctl(sockfd, SIOCGIFNETMASK, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sin = (struct sockaddr_in *)&req.ifr_netmask;
    memcpy(mask, &sin->sin_addr, sizeof(struct in_addr));

    close(sockfd);
}

/******************************************************************************
 * 功能：发送arp帧(线程1)
 * 参数：指向结构体的指针
******************************************************************************/
void *send_arp_packet(void *tag)
{
    int i;
    struct my_data *pdata = (struct my_data *)tag;
    u_char source_mac[ETH_ALEN];
    struct in_addr source_ip;

    unsigned long send_ip;
    struct in_addr temp;

    struct ethernet_head eh;                    //以太网帧结构
    struct arp_head ah;                         //arp帧结构

    u_char send_buffer[42];                     //用于存储arp帧

    bpf_u_int32 netp;                           //网络号
    bpf_u_int32 maskp;                          //子网掩码

    //为什么要memset呢？因为后面要用%s输出，%s遇到'\0'结束
    memset(source_mac, 0, ETH_ALEN);
    memcpy(source_mac, pdata->source_mac, ETH_ALEN);
    source_ip.s_addr = (pdata->source_ip).s_addr;

    if( -1 == (pcap_lookupnet(dev, &netp, &maskp, error_content)) )
    {
        printf("couldn't detect the ip and mask: %s\n", error_content);
        pthread_exit(NULL);
    }
    else
    {
        printf("lookupnet OK\n");
    }

    bzero(&ah, sizeof(ah));
    bzero(&eh, sizeof(eh));

    memset(eh.dest_mac_addr, 0xff, ETH_ALEN);               //填充目的mac地址

    memcpy(eh.source_mac_addr, source_mac, ETH_ALEN);       //填充源mac地址

    eh.type = htons(ETHERTYPE_ARP);                         //填充类型(arp类型)

    ah.hardware_type = htons(ARPHRD_ETHER);                 //硬件类型

    ah.protocol_type = htons(ETHERTYPE_IP);                 //协议类型

    ah.hardware_addr_len = ETH_ALEN;                        //硬件地址长度

    ah.protocol_addr_len = 4;                               //协议地址长度

    ah.operation_field = htons(ARPOP_REQUEST);              //操作字段(arp请求)

    memcpy(ah.source_mac_addr, source_mac, ETH_ALEN);       //填充源mac地址

    memcpy(ah.source_ip_addr, &(source_ip.s_addr), 4);      //填充源ip地址

    memset(ah.dest_mac_addr, 0x00, ETH_ALEN);               //填充目的mac地址

    for(i = 97; i < 103; i++)
    {
        send_ip = htonl(netp) + i;                          //填充目的ip地址
	    temp.s_addr = htonl(send_ip);
        inet_aton(inet_ntoa(temp), ah.dest_ip_addr );

        memset(send_buffer, 0, sizeof(send_buffer));
        memcpy(send_buffer, &eh, sizeof(eh));
        memcpy(send_buffer+sizeof(eh), &ah, sizeof(ah));
        if( -1 == pcap_sendpacket(pcap_handle, send_buffer, 42) )
        {
            printf("Send ARP error!\n");
            //pthread_exit(NULL);
        }
        //printf("Send IP: %s\n", inet_ntoa(temp));
        sleep(1);
    }

    //printf("Send ARP finish\n");

    return NULL;
}

/******************************************************************************
 *功能：pcap_loop的回调函数
 *参数1：pcap_loop的最后一个参数，当收到足够数量的包后pcap_loop会调用callback回调函数，
 *同时将pcap_loop()的最后一个参数传递给它
 *参数2：收到的数据包的pcap_pkthdr类型的指针
 *参数3：收到的数据包数据
******************************************************************************/
void callback(u_char *argument, const struct pcap_pkthdr *packet_hander,
        const u_char *packet_content)
{
    u_char mac_string[18];
    
    attack_target element;

    struct arp_head *arp_protocol;
    unsigned short operation_code;
    struct in_addr source_ip_address;
    
    arp_protocol = (struct arp_head *)(packet_content+14);
    operation_code = ntohs(arp_protocol->operation_field);
    if(2 == operation_code)                                         //数字2为ARP应答
    {
        memcpy( (void *)&source_ip_address, (void *)&arp_protocol->source_ip_addr,
                sizeof(struct in_addr) );
        //复制ip
        element.ip.s_addr = source_ip_address.s_addr;

        //printf("IP: %s\n", inet_ntoa(source_ip_address));

        memset(mac_string, 0, 18);
        sprintf(mac_string, "%02x:%02x:%02x:%02x:%02x:%02x",
        arp_protocol->source_mac_addr[0],
        arp_protocol->source_mac_addr[1],
        arp_protocol->source_mac_addr[2],
        arp_protocol->source_mac_addr[3],
        arp_protocol->source_mac_addr[4],
        arp_protocol->source_mac_addr[5]
        );

        //复制mac地址到链表当中
        memset(element.mac, 0, 18);
        memcpy(element.mac, mac_string, 18); 
        linklist_add(&l, &element);

        //printf("MAC: %s\n", mac_string);
    }

    //linklist_show(&l);
}

/******************************************************************************
 *功能：捕获arp包的函数(线程2)
 *参数：无
******************************************************************************/
void *capture_arp_packet(void)
{
    struct bpf_program filter;

    printf("Capturing ARP packet................\n");

    if( -1 == pcap_compile(pcap_handle, &filter, "arp", 0, 0) )
    {
        printf("pcap_compile: %s\n", pcap_geterr(pcap_handle));
        pthread_exit(NULL);
    }

    if( -1 == pcap_setfilter(pcap_handle, &filter) )
    {
        printf("pcap_setfilter: %s\n", pcap_geterr(pcap_handle));
        pthread_exit(NULL);
    }

    if( DLT_EN10MB != pcap_datalink(pcap_handle) )
    {
        printf("pcap_datalink: %s\n", pcap_geterr(pcap_handle));
        pthread_exit(NULL);
    }
    
    pthread_testcancel();    //如果线程3攻击时，这个线程就马上结束

    pcap_loop(pcap_handle, -1, callback, NULL);

    pcap_close(pcap_handle);

    return NULL;
}

