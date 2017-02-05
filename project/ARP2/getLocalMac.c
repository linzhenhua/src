/******************************************************************************
*    > File Name: getLocalIpMac.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月06日 星期三 10时23分08秒
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
#include <sys/param.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <net/if.h>

int main(int argc ,char *argv[])
{
    int sockfd;

    char mac[12];
    
    struct ifreq req;

    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }

    /*获取mac地址*/
    memset(mac, '\0', sizeof(mac));
    memset(&req, '\0', sizeof(req));
    strcpy(req.ifr_name, "eth0");

    if( ioctl(sockfd, SIOCGIFHWADDR, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
            (unsigned char)req.ifr_hwaddr.sa_data[0],
            (unsigned char)req.ifr_hwaddr.sa_data[1],
            (unsigned char)req.ifr_hwaddr.sa_data[2],
            (unsigned char)req.ifr_hwaddr.sa_data[3],
            (unsigned char)req.ifr_hwaddr.sa_data[4],
            (unsigned char)req.ifr_hwaddr.sa_data[5]);
    
    printf("local mac: %s\n", mac);

    close(sockfd);

    return 0;
}
