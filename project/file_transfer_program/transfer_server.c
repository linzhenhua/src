/*
 * =====================================================================================
 *
 *       Filename:  transfer_server.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月14日 14时28分16秒
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
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6000
#define BUFSIZE 4096

void clientToServer(const int *sockfd);
void serverToClient(const int *sockfd);

int main(int argc, char **argv)
{
    int sockfd;                     //套接字
    struct sockaddr_in server_addr; //服务器端地址
    struct sockaddr_in client_addr; //客户端地址
    int connfd;                     //accept返回值
    char ch;                        //判断用来接收文件还是传输文件
    socklen_t client_addr_len;      //客户端地址长度

    /*建立套接字*/
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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*绑定套接字*/
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    else
    {
        printf("bind OK\n");
    }

    /*监听*/
    if(listen(sockfd, 1) == -1)
    {
        perror("listen");
        exit(-1);
    }
    else
    {
        printf("listen....\n");
    }

    /*建立连接*/
    while(1)
    {
        client_addr_len = sizeof(client_addr);
        if( (connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1 )
        {
            perror("accept");
            break;
        }
        else
        {
            printf("accept OK,地址为:%s\n", inet_ntoa(client_addr.sin_addr));
        }

        printf("要从 %s 传输文件还是接收文件？(按‘1’传输文件,按‘2’接收文件):", inet_ntoa(client_addr.sin_addr));
        ch = getchar();

        if('1' == ch)
        {
            printf("选择了传输文件\n");
            printf("现在传输文件到 %s \n", inet_ntoa(client_addr.sin_addr));

            serverToClient(&connfd);

            break;
        }
        else if('2' == ch)
        {
            printf("选择了接收文件\n");
            printf("正在接收来自%s的文件.....\n", inet_ntoa(client_addr.sin_addr));

            clientToServer(&connfd);

            break;
        }
    }/*end of while(1)*/

    close(sockfd);

    return 0;
}

/*
 * 服务端接收文件
 * 参数:主函数accept()函数的返回值
 *
 */
void clientToServer(const int *sockfd)
{
    int flag = 0;           //发送成功或者失败的标志
    int fwrite_ret;         //fwrite返回值
    int recv_ret;           //recv函数返回值
    char buffer[BUFSIZE];   //缓存
    char name[100];         //下载的文件名
    FILE *fp;               //文件描述符

    memset(name, '\0', sizeof(name));
    read(*sockfd, name, sizeof(name));        //读取传输来的文件名
    printf("客户端要传输的文件是%s\n", name);

    if( (fp = fopen("data", "w")) == NULL )
    {
        perror("fopen");
        exit(-1);
    }
    else
    {
        memset(buffer, '\0', sizeof(buffer));
    }

    while( recv_ret = recv(*sockfd, buffer, BUFSIZE, 0) )
    {
        ++flag;
        if(recv_ret == -1)
        {
            perror("recv");
            break;
        }
        /*向打开的文件写入数据*/
        fwrite_ret = fwrite(buffer, sizeof(char), recv_ret, fp);
        if(fwrite_ret < recv_ret)
        {
            printf("file write failed\n");
            exit(-1);
        }
        memset(buffer, '\0', sizeof(buffer));
    }

    if(flag != 0)
    {
        printf("文件传输完毕\n");
    }
    else
    {
        printf("文件传输失败\n");
    }
    fclose(fp);
    rename("data", name);

    return;
}

/*
 * 服务端发送文件
 * 参数:主函数accept()函数的返回值
 *
 */
void serverToClient(const int *sockfd)
{
    char name[100];                 //要传输的文件的名
    char buffer[BUFSIZE];           //缓冲
    FILE *fp;                       //文件描述符
    int read_ret;                   //fread的返回值

    getchar();      //用来捕获终端输入的'\n'缓存,以免干扰下面的输入
    printf("请输入要传输文件的名字:");

    memset(name, '\0', sizeof(name));
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1] = '\0';

    write(*sockfd, name, sizeof(name));    //发送给客户端要传输的文件的名字

    if( (fp = fopen(name, "r")) == NULL )
    {
        perror("fopen");
        exit(-1);
    }
    printf("正在传输.......\n");
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
