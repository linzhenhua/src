/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 09时07分53秒
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
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFSIZE 4096

void udps_respon(int sockfd, const struct sockaddr_in addr) // 进行读写操作
{
    //struct sockaddr_in addr;
    socklen_t addrlen;
    int n;
    char msg[BUFSIZE];

    addrlen = sizeof(addr);
    while(1)
    {
        /*从网络读取数据，并显示出来*/
        bzero(msg, sizeof(msg));
        if( (n = recvfrom(sockfd, msg, BUFSIZE, 0, (struct sockaddr *)&addr, &addrlen)) == -1 )
        {
            printf("recvfrom error\n");
            return;
        }
        msg[n] = '\0';
        printf("server have received %s\n", msg);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in addr;

    /*创建套接字*/
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        printf("create socket error\n");
        return -1;
    }
    /*服务端填充资料*/
    bzero(&addr, sizeof(addr));                 //清0
    addr.sin_family = AF_INET;                  //设置地址族
    addr.sin_port = htons(PORT);                //设置端口
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   //设置IP

    /*捆绑sockfd描述符*/
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("bind error\n");
        return -1;
    }

    udps_respon(sockfd, addr); // 进行读写操作
    close(sockfd);

    return 0;
}
