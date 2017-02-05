/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 08时35分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFSIZE 4096

void udpc_requ(int sockfd, const struct sockaddr_in *addr, int len)
{
    char buffer[BUFSIZE];

    while(1)
    {
        /*从键盘读入数据，写到服务端*/
        printf("please input something:");
        fgets(buffer, BUFSIZE, stdin);
        sendto(sockfd, buffer, sizeof(buffer), 0, addr, len);
        bzero(buffer, BUFSIZE);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in addr;

    if(argc != 2)
    {
        printf("usage:./a.out IPaddress\n");
        return -1;
    }
    /*建立socket描述符*/
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("create socket error\n");
        return -1;
    }
    /*填写服务端资料*/
    bzero(&addr, sizeof(addr));   //将服务端地址清0
    addr.sin_family = AF_INET;    //设置地址族
    addr.sin_port = htons(PORT);  //设置端口
    if( inet_aton(argv[1], &addr.sin_addr) == 0 )
    {
        printf("IP error\n");
        return -1;
    }

    udpc_requ(sockfd, &addr, sizeof(addr));
    close(sockfd);

    return 0;
}
