/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 10时55分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  林振华
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
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFSIZE 4096
#define PORT 6000

void *fun_read(void *arg);
void *fun_write(void *arg);

int main(int argc, char **argv)
{
    int sockfd;   //套接字描述符
    int connfd;   //accept描述符
    struct sockaddr_in client_addr;   //客户端地址
    socklen_t client_addr_len;   //地址长度

    pthread_t pid1, pid2;  //线程id

    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }
    else
    {
        fprintf(stdout,"socket OK\n");
    }

    bzero(&client_addr, sizeof(client_addr));  //清0
    client_addr.sin_family = AF_INET;  //协议族
    client_addr.sin_port = htons(PORT);  //设置端口号
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //接受任何IP地址
    
    /*绑定套接字*/
    if(bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    else
    {
        fprintf(stdout, "bind OK\n");
    }
    
    /*监听，设置最大的监听数*/
    if(listen(sockfd, 5) == -1)
    {
        perror("listen");
        exit(-1);
    }
    else
    {
        fprintf(stdout, "listen....\n");
    }

    while(1)
    {
        client_addr_len = sizeof(client_addr);
        /*接受连接*/
        if( (connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1 )
        {
            perror("accept");
            exit(-1);
        }  
        else
        {
            fprintf(stdout, "accept OK\n");
        }
        /*创建线程*/
        if(pthread_create(&pid1, NULL, fun_read, (void *)&connfd) != 0)
        {
            perror("pthread_create");
            exit(-1);
        }
        if(pthread_create(&pid2, NULL, fun_write, (void *)&connfd) != 0)
        {
            perror("pthread_create");;
            exit(-1);
        }
    }

    return 0;
}

/*读取数据线程*/
void *fun_read(void *arg)
{
    int connfd = *((int*)arg);
    char buffer[BUFSIZE];  //缓冲

    while(1)
    {
        memset(buffer, '\0', BUFSIZE);
        if( read(connfd, buffer, BUFSIZE) == -1 )
        {
            perror("read");
            exit(-1);
        }
        fprintf(stdout,"client:%s\n", buffer);
        if(strncmp(buffer, "quit", 4) == 0)
        {
            //fprintf(stdout, "client quit\n");
            exit(-1);
        }
    }

    return (void *)0;
}

/*写入数据线程*/
void *fun_write(void *arg)
{
    int connfd = *((int*)arg);
    char buffer[BUFSIZE];

    while(1)
    {
        memset(buffer, '\0', BUFSIZE);
        fgets(buffer, BUFSIZE, stdin);
        if( write(connfd, buffer, BUFSIZE) == -1)
        {
            perror("write");
            exit(-1);
        }
        fprintf(stdout, "server write OK\n");
        if(strncmp(buffer, "quit", 4) == 0)
        {
            fprintf(stdout, "you are quit now\n");
            exit(-1);
        }
    }

    return (void *)0;
}
