/******************************************************************************
*    > File Name: getLocalMask.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月14日 星期四 10时22分03秒
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
    char mask[8];
    
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
    memset(mask, '\0', sizeof(mask));
    /*获取ip地址*/
    if( ioctl(sockfd, SIOCGIFNETMASK, &req) == -1 )
    {
        perror("ioctl");
        close(sockfd);
        exit(-1);
    }
    sin = (struct sockaddr_in *)&req.ifr_netmask;
    strcpy(mask, inet_ntoa(sin->sin_addr));
    printf("local mask: %s\n", mask);

    close(sockfd);

    return 0;
}
