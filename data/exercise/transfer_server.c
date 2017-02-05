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
#include <pthread.h>

#define PORT 6000
#define BUFSIZE 4096

void clientToServer(const int *sockfd);

int main(int argc, char **argv)
{
    int sockfd;                     //套接字
    struct sockaddr_in server_addr; //服务器端地址
    struct sockaddr_in client_addr; //客户端地址
    int connfd;                     //accept返回值
    int num;                        //判断用来接收文件还是传输文件
    int tid;                        //线程ID
    char name[10];                  //是下载还是上传
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
        scanf("%d", &num);

        if(1 == num)
        {
            printf("选择了传输文件\n");
            if( 0 != pthread_create(&tid, NULL, serverToClient, (void *)&connfd) )
            {
                perror("pthread_create");
                break;
            }
        }
        else if(2 == num)
        {
            printf("选择了接收文件\n");
            if( 0 != pthread_create(&tid, NULL, clientToServer, (void *)&connfd) )
            {
                perror("pthread_create");
                break;
            }
        }

        memset(name, '\0', sizeof(name));
        if(read(connfd, name, sizeof(name)) == -1)    //客户端传输文件到服务端
        {
            perror("read");
            break;
        }
        if( strncmp(name, "yes", 3) == 0)
        {
            printf("客户端要传输数据\n");   //是上传
            printf("正在接收来自%s的文件.....\n", inet_ntoa(client_addr.sin_addr));
            clientToServer(&connfd);
            break;
        }
        else
        {
            printf("不能识别的字符\n");
            break;
        }
    }/*end of while(1)*/

    close(sockfd);

    return 0;
}

/*
 * 将服务端的文件传输到客户端
 * 参数:主线程accept()函数的返回值
 *
 */
void *serverToClient(void *sockfd)
{
    char name[100];                 //要传输的文件的名
    char buffer[BUFSIZE];           //缓冲
    FILE *fp;                       //文件描述符
    int read_ret;                   //fread的返回值

    printf("请输入要传输文件的名字:");

    memset(name, '\0', sizeof(name));
    fgets(name, sizeof(name), stdin);

    write(*sockfd, name, sizeof(name));    //发送给客户端要传输的文件的名字
    name[strlen(name)-1] = '\0';           //将fgets返回的'\n'换成'\0'

    if( (fp = fopen(name, "r")) == NULL )
    {
        perror("fopen");
        pthread_exit();
    }
    printf("正在传输.......\n");
    memset(buffer, '\0', sizeof(buffer));
    /*不断读取并发送数据*/
    while( (read_ret = fread(buffer, sizeof(char), BUFSIZE, fp)) > 0 )
    {
        if(send(*sockfd, buffer, read_ret, 0) == -1)
        {
            perror("send");
            pthread_exit();
        }
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);

    return (void *)0;
}

void clientToServer(const int *sockfd)
{
    int flag = 0;           //发送成功或者失败的标志
    int fwrite_ret;         //fwrite返回值
    int recv_ret;           //recv函数返回值
    char buffer[BUFSIZE];   //缓存
    char name[100];         //下载的文件名
    FILE *fp;               //文件描述符

    memset(name, '\0', sizeof(name));
    read(*sockfd, name, sizeof(name));        //读取上传的文件名
    printf("客户端要上传的数据是%s", name);

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
            exit(-1);
        }
        /*向打开的文件写入数据*/
        fwrite_ret = fwrite(buffer, sizeof(char), recv_ret, fp);
        if(fwrite_ret > recv_ret)
        {
            printf("file write failed\n");
            exit(-1);
        }
        memset(buffer, '\0', sizeof(buffer));
    }

    if(flag != 0)
    {
        printf("文件传送完毕\n");
    }
    else
    {
        printf("文件传送失败\n");
    }
    fclose(fp);
    rename("data", name);

    return ;
}

