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
void serverToClient(const int *sockfd);

int main(int argc, char **argv)
{
    int sockfd;                          //套接字
    struct sockaddr_in server_addr;      //服务器端地址
    char ch;                             //判断是否传输还是接收文件

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

    printf("传输文件还是接收文件？(按‘1’传输文件,按‘2’接收文件)");
    ch = getchar();

    if('1' == ch)
    {
        printf("选择了传输文件\n");
        printf("现在传输文件到服务端\n");

        clientToServer(&sockfd);

    }
    else if('2' == ch)
    {
        printf("选择了接收文件\n");
        printf("正在接收来自服务端的文件.......\n");

        serverToClient(&sockfd);
    }

    close(sockfd);

    return 0;
}

/*
 *客户端发送文件
 *参数:主函数accept()函数的返回值
 */
void clientToServer(const int *sockfd)
{
    char path[100];         //传输文件名字
    char buffer[BUFSIZE];   //缓存
    FILE *fp;               //文件描述符
    int read_ret;           //fread返回值

    getchar();     //用来捕获终端输入的'\n'缓存,以免干扰下面的输入
    printf("请输入要传输文件的名字:");
    memset(path, '\0', sizeof(path));
    fgets(path, sizeof(path), stdin);   //fgets默认在字符串后面加上换行符的

    /*说明一下,为什么不用用gets,因为gets不安全,而用fgets要去掉最后面的换行符*/
    path[strlen(path)-1] = '\0';            //去掉换行符,比如:C99.pdf\n\0,就是要去掉\n这个'\n'
    
    write(*sockfd, path, sizeof(path));     //发送给服务端要传输的数据名字
    
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

/*
 *客户端接收文件
 参数:主函数accept()函数的返回值
 * 
 */
void serverToClient(const int *sockfd)
{
    char name[100];             //要接收的文件名
    char buffer[BUFSIZE];       //缓冲
    FILE *fp;                   //文件描述符
    int recv_ret;               //recv的返回值
    int fwrite_ret;             //fwrite的返回值
    int flag;                   //接收成功或者失败的标志位

    memset(name, '\0', sizeof(name));
    read(*sockfd, name, sizeof(name));       //读取传输来的文件名
    printf("服务端要传输的文件是%s\n", name);

    if( (fp = fopen("data", "w")) == NULL)
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
