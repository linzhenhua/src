/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 16时15分26秒
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT  6000   //端口

int main(int argc, char **argv)
{
    int sockfd;   //套接字
    int new_fd;   //accept返回值
    struct sockaddr_in server_addr;   //服务端
    struct sockaddr_in client_addr;   //客户端
    socklen_t client_addr_size;  //客户端地址大小
    int nbytes;   //read返回值
    char buffer[4096];  //缓存

    /*服务端建立sockfd描述符*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("create socket error\n");
        return -1;
    }

    /*服务端填充server_addr结构*/
    bzero(&server_addr, sizeof(server_addr));  //将服务端清0
    server_addr.sin_family = AF_INET;  //设置地址族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY表示可以接受任何IP
    server_addr.sin_port = htons(PORT);  //设置端口号

    /*捆绑sockfd描述符到IP地址*/
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        printf("bind error\n");
        return -1;
    }

    /*监听,设置允许链接的最大客户端数*/
    if(listen(sockfd, 5) == -1)
    {
        printf("listen error\n");
        return -1;
    }

    while(1)
    {
        /*服务端阻塞,直到客户端程序建立连接*/
        client_addr_size = sizeof(client_addr);
        if((new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_size)) == -1)
        {
            printf("accept error\n");
            return -1;
        }
        else
        {
            printf("accept OK\n");
        }

        if((nbytes = read(new_fd, buffer, 4096)) == -1)
        {
            printf("read error\n");
            return -1;
        }
        buffer[nbytes] = '\0';
        printf("server received %s\n", buffer);
        close(new_fd);
    }
    close(sockfd);

    return 0;
}

