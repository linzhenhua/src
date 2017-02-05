/******************************************************************************
*    > File Name: arp.h
*
*    >Description:
*
*    >Version: 1.0
*    > Created Time: 2014年04月27日 星期日 16时49分12秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com
*    > Company:
*
******************************************************************************/
#ifndef _ARP_H
#define _ARP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <pthread.h>
#include <pcap.h>
#include <libnet.h>

#define OK      0
#define ERROR   -1
#define TRUE    1
#define FALSE   0

#define ARP_LEN 28

/*****************************************************************************/
pcap_t *pcap_handle;                    //pcap句柄
char error_content[PCAP_ERRBUF_SIZE];   //存储错误信息
char *dev;                              //网络设备

pthread_t pthread_id2;                  //线程2的id，捕获ARP帧

/*arp帧结构*/
struct arp_head
{
    /*顺序不要写错*/
    u_int16_t hardware_type;            //硬件类型
    u_int16_t protocol_type;            //协议类型
    u_int8_t  hardware_addr_len;        //硬件地址长度
    u_int8_t  protocol_addr_len;        //协议地址长度
    u_int16_t operation_field;          //操作字段
    u_int8_t  source_mac_addr[6];       //源mac地址
    u_int8_t  source_ip_addr[4];        //源ip地址
    u_int8_t  dest_mac_addr[6];         //目的mac地址
    u_int8_t  dest_ip_addr[4];          //目的ip地址
};

/*以太网帧结构*/
struct ethernet_head
{
    u_int8_t dest_mac_addr[6];          //目的mac地址
    u_int8_t source_mac_addr[6];        //源mac地址
    u_int16_t type;                     //帧类型
};

//用于线程
struct my_data
{
    struct in_addr source_ip;           //本地ip地址，字节流形式
    u_char source_mac[ETH_ALEN];        //本地mac地址，字节流形式
};
/*****************************************************************************/

/*****************************************************************************/
typedef int status;

typedef struct element_type
{
    unsigned int flag;              //标记
    u_char mac[18];                 //mac地址
    struct in_addr ip;              //ip地址
}attack_target;

typedef struct list_node
{
    attack_target data;
    struct list_node *next;
}position;

typedef struct 
{
    position *head;
    position *rear;
    unsigned int length;
}linklist;

linklist l;                         //定义一个链表

/******************************************************************************
 *功能：获取本地的ip地址，mac地址，子网掩码mask
 *参数1：返回mac地址
 *参数2：返回ip地址
 *参数3：返回子网掩码
******************************************************************************/
void get_local_info(u_char *mac, struct in_addr *ip, struct in_addr *mask);

/******************************************************************************
 *功能：发送arp帧
 *参数1：指向结构体的指针
******************************************************************************/
void *send_arp_packet(void *tag);

/******************************************************************************
 *功能：pcap_loop的回调函数
 *参数1：pcap_loop的最后一个参数，当收到足够数量的包后pcap_loop会调用callback回调函数，
 *同时将pcap_loop()的最后一个参数传递给它
 *参数2：收到的数据包的pcap_pkthdr类型的指针
 *参数3：收到的数据包数据
******************************************************************************/
void callback(u_char *argument, const struct pcap_pkthdr *packet_hander,
        const u_char *packet_content);

/******************************************************************************
 *功能：捕获arp包的函数
 *参数：无
******************************************************************************/
void *capture_arp_packet(void);

/******************************************************************************
 *功能：初始化链表
 *参数：待初始化的链表
 *****************************************************************************/
status linklist_init(linklist *l);

/******************************************************************************
 *功能：向链表插入元素
 *参数1：待插入的链表
 *参数2：待插入的元素
 *****************************************************************************/
status linklist_add(linklist *l, const attack_target *x);

/******************************************************************************
 *功能：遍历链表
 *参数：待遍历的链表
 *****************************************************************************/
status linklist_show(const linklist *l);

/******************************************************************************
 *功能：销毁链表
 *参数: 待销毁的链表
 *****************************************************************************/
void linklist_destroy(linklist *l);

/******************************************************************************
 * 功能： 提取mac地址到buf中
 * 参数1： 待提取的mac地址
 * 参数2： 保存mac地址的缓存
 * 返回值： 无
******************************************************************************/
void mac_str(char *mac, char *buf);

/******************************************************************************
 * 功能： 提取IP地址到buf中
 * 参数1： 待提取的ip地址
 * 参数2： 保存IP地址的缓存
 * 返回值： 无
******************************************************************************/
void ip_str(char *ip, char *buf);

/******************************************************************************
 * 功能： 封装以太网帧到buf中
 * 参数1： 目的mac地址
 * 参数2： 源mac地址
 * 参数3： 以太网类型
 * 参数4： 保存以太网帧的缓存
 * 返回值： 无
******************************************************************************/
void encapsulate_frame(char *dest_mac, char *source_mac, unsigned int type, char *buf);

/******************************************************************************
 * 功能： 封装arp帧到buf中
 * 参数1： arp操作字段
 * 参数2： 源mac地址
 * 参数3： 源IP地
 * 参数4： 目的mac地址
 * 参数5： 目的IP地址
 * 参数6： 保存arp帧的缓存
 * 返回值： 无
******************************************************************************/
void encapsulate_arp(unsigned short ar_op, char *source_mac, char *source_ip, 
        char *dest_mac, struct in_addr *dest_ip, char *buf);

/******************************************************************************
 * 功能： 创建套接字
 * 参数： 无
 * 返回值：返回创建的套接字
******************************************************************************/
int open_packet_socket(void);

/******************************************************************************
 * 功能： arp攻击
 * 返回值： 无
******************************************************************************/
void *arp_attack(void);

#endif
