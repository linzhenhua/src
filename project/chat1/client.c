/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 16时57分20秒
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
#include <errno.h>
#include <unistd.h>
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
    struct sockaddr_in server_addr;   //服务端地址

    pthread_t pid1, pid2;   //线程id

    if(argc != 2)
    {
        fprintf(stdout, "usage:a.out <IPaddress>\n");
        exit(-1);
    }
    /*建立套接字*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }
    else
    {
        fprintf(stdout, "socket OK\n");
    }

    bzero(&server_addr, sizeof(server_addr));   //清0
    server_addr.sin_family = AF_INET;           //协议族
    server_addr.sin_port = htons(PORT);         //设置端口
    if( inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0 )   //设置IP地址
    {
        perror("inet_pton");
        exit(-1);
    }

    /*建立连接*/
    if( connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1 )
    {
        perror("connect");
        exit(-1);
    }
    else
    {
        fprintf(stdout, "connect OK\n");
    }

    /*创建线程*/
        if( pthread_create(&pid1, NULL, fun_read, (void *)&sockfd) != 0 )
        {
            perror("pthread_create");
            exit(-1);
        }
        if( pthread_create(&pid2, NULL, fun_write, (void *)&sockfd) != 0 )
        {
            perror("pthread_create");
            exit(-1);
        }

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    return 0;
}

/*读取数据线程*/
void *fun_read(void *arg)
{
    int connfd = *((int*)arg);
    char buffer[BUFSIZE];

    while(1)
    {
        memset(buffer, '\0', BUFSIZE);
        if(read(connfd, buffer, BUFSIZE) == -1)
        {
            perror("read");
            exit(-1);
        }
        fprintf(stdout, "server:%s\n", buffer);
        if(strncmp(buffer, "quit", 4) == 0)
        {
            //fprintf(stdout, "server quit\n");
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
        if(write(connfd, buffer, BUFSIZE) == -1)
        {
            perror("write");
            exit(-1);
        }
        fprintf(stdout,"\nclient write OK\n");

        if(strncmp(buffer, "quit", 4) == 0)
        {
            fprintf(stdout, "you are quit now\n");
            exit(-1);
        }
    }
  
    return (void *)0;
}
