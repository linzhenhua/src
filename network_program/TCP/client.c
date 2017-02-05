/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 15时04分58秒
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6000     //端口号

int main(int argc, char **argv)
{
    int sockfd;   //套接字
    char buffer[4096];   //缓存
    struct sockaddr_in server_addr;  //服务端地址
    struct hostent *host;    //主机名

    if(argc != 2)
    {
        printf("usarg:./a.out hostname\n");
        return -1;
    }

    /*获取主机名*/
    if( (host = gethostbyname(argv[1])) == NULL )
    {
        printf("gethostname error\n");
        return -1;
    }

    /*建立socket描述符*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        printf("create socket error\n");
        return -1;
    }

    /*客户程序填充服务端的资料*/
    bzero(&server_addr, sizeof(server_addr));  //将服务端地址清0
    server_addr.sin_family = AF_INET;         //设置地址族
    server_addr.sin_port = htons(PORT);           //设置端口号
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);    //设置IP地址

    /*客户端程序发起连接请求*/
    if( connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1 )
    {
        printf("connect error\n");
        return -1;
    }
    else
    {
        printf("connect OK\n");
    }

    /*发送数据*/
    fgets(buffer, 4096, stdin);
    write(sockfd, buffer, strlen(buffer));

    close(sockfd);

    return 0;
}
