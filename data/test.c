/******************************************************************************
*    > File Name: 1.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月14日 星期四 08时54分33秒
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
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <pcap.h>

void encapsulate_arp(const char *source_mac, const char *source_ip, const char *dest_ip);
void mac_str(const char *mac, char *buf);
void ip_str(const char *ip, char *buf);
void getLocalIp(char *ip);
void getLocalMac(char *mac);
void getLocalMask(char *mask);

/*****************************************************************************/
/*ARP协议数据结构*/
struct ether_arp
{   /*顺序不要写错了*/
    struct arphdr ea_hdr;           //ARP头部信息(函数库自带的)
    u_char arp_sha[6];              //源mac地址
    u_char arp_spa[4];              //源IP地址
    u_char arp_tha[6];              //目的mac地址
    u_char arp_tpa[4];              //目的IP地址
};

/*ARP报文格式(以太网帧+ARP协议数据结构)*/
struct arppacket
{
    struct ether_header eh;          //14个字节(函数库自带的)
    struct ether_arp ea;             //28个字节
}arp;

/*****************************************************************************/
/*封装ARP帧*/
void encapsulate_arp(const char *source_mac, const char *source_ip, const char *dest_ip)
{
    char *mac_buf;                  //缓存
    char *ip_buf;

    mac_buf = (char *)malloc(6*sizeof(char));
    if(NULL == mac_buf)
        exit(-1);

    ip_buf = (char *)malloc(4*sizeof(char));
    if(NULL == ip_buf)
        exit(-1);

    mac_str("FF:FF:FF:FF:FF:FF", mac_buf);      //填充目的mac地址
    memcpy(arp.eh.ether_dhost, mac_buf, 6);
    memset(mac_buf, '\0', sizeof(mac_buf));

    mac_str(source_mac, mac_buf);               //填充源mac地址
    memcpy(arp.eh.ether_shost, mac_buf, 6);
    memset(mac_buf, '\0', sizeof(mac_buf));

    arp.eh.ether_type = htons(ETHERTYPE_ARP);   //填充类型(ARP类型)

    arp.ea.ea_hdr.ar_hrd = htons(ARPHRD_ETHER); //硬件类型
    arp.ea.ea_hdr.ar_pro = htons(ETHERTYPE_IP); //协议类型
    arp.ea.ea_hdr.ar_hln = 6;                   //硬件地址长度
    arp.ea.ea_hdr.ar_pln = 4;                   //协议地址长度
    arp.ea.ea_hdr.ar_op = htons(ARPOP_REQUEST); //操作字段(ARP请求)

    mac_str(source_mac, mac_buf);
    memcpy(arp.ea.arp_sha, mac_buf, 6);         //填充源地址
    memset(mac_buf, '\0', sizeof(mac_buf));

    ip_str(source_ip, ip_buf);
    memcpy(arp.ea.arp_spa, ip_buf, 4);          //填充IP地址
    memset(ip_buf, '\0', sizeof(ip_buf));

    mac_str("FF:FF:FF:FF:FF:FF", mac_buf);
    memcpy(arp.ea.arp_tha, mac_buf, 6);         //填充目地地址

    ip_str(dest_ip, ip_buf);
    memcpy(arp.ea.arp_tpa, ip_buf, 4);          //填充目的IP地址
}

/*****************************************************************************/
/*mac地址转换*/
void mac_str(const char *mac, char *buf)
{
    sscanf(mac, "%x:%x:%x:%x:%x:%x", buf+0, buf+1, buf+2, buf+3, buf+4, buf+5);
}

/*****************************************************************************/
/*IP地址转换*/
void ip_str(const char *ip, char *buf)
{
    sscanf(ip, "%d.%d.%d.%d", buf+0, buf+1, buf+2, buf+3);
}

/*****************************************************************************/
/*获取本机的IP地址*/
void getLocalIp(char *ip)
{
    int sockfd;
    //char ip[8];
    
    struct ifreq req;
    struct sockaddr_in *sin;

    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }

    memset(&req, '\0', sizeof(req));
    strcpy(req.ifr_name, "eth0");
    //memset(ip, '\0', sizeof(ip));
    /*获取ip地址*/
    if( ioctl(sockfd, SIOCGIFADDR, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sin = (struct sockaddr_in *)&req.ifr_addr;
    strcpy(ip, inet_ntoa(sin->sin_addr));

    close(sockfd);
}

/*****************************************************************************/
/*获取本机的MAC地址*/
void getLocalMac(char *mac)
{
    int sockfd;
    //char mac[12];
    
    struct ifreq req;

    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }

    /*获取mac地址*/
    //memset(mac, '\0', sizeof(mac));
    memset(&req, '\0', sizeof(req));
    strcpy(req.ifr_name, "eth0");

    if( ioctl(sockfd, SIOCGIFHWADDR, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
            (u_char)req.ifr_hwaddr.sa_data[0],
            (u_char)req.ifr_hwaddr.sa_data[1],
            (u_char)req.ifr_hwaddr.sa_data[2],
            (u_char)req.ifr_hwaddr.sa_data[3],
            (u_char)req.ifr_hwaddr.sa_data[4],
            (u_char)req.ifr_hwaddr.sa_data[5]);

    close(sockfd);
}
/*****************************************************************************/
/*获取本机的mask地址*/
void getLocalMask(char *mask)
{
    int sockfd;
    
    struct ifreq req;
    struct sockaddr_in *sin;

    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }

    memset(&req, '\0', sizeof(req));
    strcpy(req.ifr_name, "eth0");

    /*获取mask地址*/
    if( ioctl(sockfd, SIOCGIFNETMASK, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sin = (struct sockaddr_in *)&req.ifr_netmask;
    strcpy(mask, inet_ntoa(sin->sin_addr));

    close(sockfd);
}

int main(int argc, char **argv)
{
    char *dev;
    char errbuf[1024];
    char select = 'a';

    char source_mac[12];        //源mac地址
    char source_ip[8];          //源ip地址
    char source_mask[8];        //源mask地址

    /*清0*/
    memset(source_mac, '\0', sizeof(source_mac));
    memset(source_ip, '\0', sizeof(source_ip));
    memset(source_mask, '\0', sizeof(source_mask));

    /*获得本机mac地址*/
    getLocalMac(source_mac);
    printf("local mac: %s\n", source_mac);

    /*获取本机的IP地址*/
    getLocalIp(source_ip);
    printf("local ip: %s\n", source_ip);

    /*获取本机的mask地址*/
    getLocalMask(source_mask);
    printf("local mask: %s\n", source_mask);

    printf("select(dispaly the packet in detail):(y/n)?");
    scanf("%c", &select);
    while(select != 'y' && select != 'Y' && select != 'n' && select != 'N')
    {
        printf("input the error! please input the y/Y/n/N:");
        scanf("%c", &select);
    }

    //look for the net device
    dev = pcap_lookupdev(errbuf);
    if(NULL == dev)
    {
        printf("couldn't find default device: %s\n", errbuf);
        exit(-1);
    }
    else
    {
        printf("find success device: %s\n", dev);
    }

    return 0;
}
