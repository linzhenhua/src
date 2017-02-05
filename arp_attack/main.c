/******************************************************************************
*    > File Name: main.c
*
*    >Description:
*
*    >Version: 1.0
*    > Created Time: 2014年04月27日 星期日 17时13分40秒
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
 * 功能：主函数
 * 参数：无
******************************************************************************/
int main(int argc, char **argv)
{
    struct hostent *host;

    u_char source_mac[18];          //源mac

    struct my_data pdata;

    int pthread_err;                //线程返回值
    pthread_t pthread_id1;          //线程1为发送ARP帧
    pthread_t pthread_id3;          //线程3为arp攻击

    struct in_addr local_ip;        //本地ip地址，字节流形式
    struct in_addr local_mask;      //本地mask地址，字节流形式

    u_char *local_mac = NULL;       //本地mac地址，字节流形式
    local_mac = (u_char *)malloc(ETH_ALEN);
    if(NULL == local_mac)
    {
        printf("Memory allocation failure\n");
        exit(-1);
    }
    memset(local_mac, 0, ETH_ALEN);

    get_local_info(local_mac, &local_ip, &local_mask);

    pdata.source_ip.s_addr = local_ip.s_addr;
    memcpy(pdata.source_mac, local_mac, ETH_ALEN);

    memset(source_mac, 0, 18);
    sprintf(source_mac, "%02x:%02x:%02x:%02x:%02x:%02x",
            *(local_mac+0), *(local_mac+1), *(local_mac+2),
            *(local_mac+3), *(local_mac+4), *(local_mac+5)
            );

    host = gethostbyaddr(&local_ip, sizeof(struct in_addr), AF_INET);
    if(NULL == host)
    {
        printf("gethostbyaddr error: %s\n", hstrerror(h_errno));
        exit(-1);
    }


    printf("\n=======================================================================================================\n");
    printf("local infomation:\n");
    printf("hostname: %s   ", host->h_name);
    printf("ip: %s   ", inet_ntoa(local_ip));
    printf("mac: %s   ", source_mac);
    printf("mask: %s", inet_ntoa(local_mask));
    printf("\n=======================================================================================================\n");
 
    if( OK != linklist_init(&l) )             //初始化链表
    {
        printf("初始化链表失败\n");
        exit(-1);
    }

    //查找网络设备
    dev = pcap_lookupdev(error_content);
    if(NULL == dev)
    {
        printf("couldn't find default device: %s\n", error_content);
        exit(-1);
    }
    else
    {
        printf("find success device : %s\n", dev);
    }

    //打开网络设备(网卡必须要设置为混杂模式：ifconfig eth0 promise)
    pcap_handle = pcap_open_live(dev, 65535, 1, 0, error_content);
    if(NULL == pcap_handle)
    {
        printf("couldn't open the net device: %s\n", error_content);
        exit(-1);
    }
    else
    {
        printf("open net device success\n");
    }

    //创建线程
    pthread_err = pthread_create(&pthread_id1, NULL, send_arp_packet, &(pdata));
    if(pthread_err != 0)
    {
        printf("Can't create thread: %s\n", strerror(pthread_err));
        exit(-1);
    }

    pthread_err = pthread_create(&pthread_id2, NULL, capture_arp_packet, NULL);
    if(pthread_err != 0)
    {
        printf("Can't create thread: %s\n", strerror(pthread_err));
        exit(-1);
    } 

    sleep(10);
    pthread_err = pthread_create(&pthread_id3, NULL, arp_attack, NULL);
    if(pthread_err != 0)
    {
        printf("Can't create thread: %s\n", strerror(pthread_err));
        exit(-1);
    }

    //等待线程结束
    pthread_join(pthread_id1, NULL);
    pthread_join(pthread_id2, NULL);
    pthread_join(pthread_id3, NULL);

    free(local_mac);
    local_mac = NULL;
    
    linklist_destroy(&l);

    return 0;
}
