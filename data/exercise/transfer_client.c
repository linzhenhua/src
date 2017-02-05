/*
 * =====================================================================================
 *
 *       Filename:  transfer_client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月13日 09时48分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 4096
#define PORT 6000

void clientToServer(const int *sockfd);

int main(int argc, char **argv)
{
    int sockfd;                          //套接字
    struct sockaddr_in server_addr;      //服务器端地址
    char name[10];                      //记录传输用的
    
    if(argc != 2)
    {
        printf("usage:a.out <IPaddress>\n");
        exit(-1);
    }

    /*创建套接字*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        perror("socket");
        exit(-1);
    }
    else
    {
        printf("socket OK\n");
    }

    /*填写基本资料*/
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
    {
        printf("inet_pton");
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
        printf("connect OK\n");
    }

    printf("\t-----要传输文件到服务端请输入'yes'-----\n");
    memset(name, '\0', sizeof(name));
    fgets(name, sizeof(name), stdin);
    write(sockfd, name, sizeof(name));     //发送给服务器端要传输文件
    if( strncmp(name, "yes", 3) == 0)
    {
        printf("现在传输文件:\n");
        clientToServer(&sockfd);
    }
    else
    {
        printf("输入有误,程序终止\n");
        exit(-1);
    }
    close(sockfd);

    return 0;
}

void clientToServer(const int *sockfd)
{
    char path[100];         //上传文件名字
    char buffer[BUFSIZE];   //缓存
    FILE *fp;               //文件描述符
    int read_ret;           //fread返回值

    printf("请输入你要传输文件的名字:");
    memset(path, '\0', sizeof(path));
    fgets(path, sizeof(path), stdin);   //fgets默认在字符串后面加上换行符的

    write(*sockfd, path, sizeof(path));     //发送给服务端要传输的数据名字

    /*说明一下,为什么不用用gets,因为gets不安全,而用fgets要去掉最后面的换行符*/
    path[strlen(path)-1] = '\0';   //去掉换行符,比如:C99.pdf\n\0,就是要去掉\n这个'\n'
    if( (fp = fopen(path, "r")) == NULL )
    {
        perror("fopen");
        exit(-1);
    }
    printf("正在传输......\n");
    memset(buffer, '\0', sizeof(buffer));
    /*不断读取并发送数据*/
    while( (read_ret = fread(buffer, sizeof(char), BUFSIZE, fp)) > 0 )
    {
        if(send(*sockfd, buffer, read_ret, 0) == -1)
        {
            perror("send");
            exit(-1);
        }
        memset(buffer, '\0', sizeof(buffer));
    }

    fclose(fp);

    printf("传输完毕\n");

    return;
}

