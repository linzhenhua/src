/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月12日 09时56分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: 林振华
 *        Company:
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <resolv.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd;                 //套接字
    int len;                    //发送和接收字节长度
    struct sockaddr_in dest;    //服务端地址
    char buffer[MAXBUF+1];      //缓冲
    fd_set rfds;                //句柄集合
    struct timeval tv;          //等待时间
    int retval;                 //select返回值
    int maxfd = -1;             //最大描述符

    if(argc != 3)
    {
        printf("参数格式错误!正确用法如下:\n\t\t%s IP地址 端口\n\t比如:\t%s 127.0.0.1 7838\n此程序用来从某个IP地址服务器某个端口接收最多MAXBUF个字节的消息\n", 
                argv[0], argv[0]);
        exit(0);
    }

    /*创建套接字*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        perror("socket");
        exit(0);
    }

    /*初始化服务端(对方)的地址和端口信息*/
    bzero(&dest, sizeof(dest));  
    dest.sin_family = AF_INET;
    dest.sin_port = htons( atoi(argv[2]) );
    if( inet_aton(argv[1], (struct in_addr *)&dest.sin_addr.s_addr) == 0 )
    {
        perror("inet_aton");
        exit(0);
    }

    /*连接服务器端*/
    if(connect(sockfd, (struct sockaddr *)&dest,  sizeof(dest)) == -1)
    {
        perror("connect");
        exit(0);
    }

    printf("\n客户端准备就绪,可以开始聊天了..直接输入消息回车即可发信息给对方\n");
    
    while(1)
    {
        /*把集合清空*/
        FD_ZERO(&rfds);

        /*把标准句柄0加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;

        /*把当前连接句柄sockfd加入到集合中*/
        FD_SET(sockfd, &rfds);
        if(sockfd > maxfd)
        {
            maxfd = sockfd;
        }

        /*设置最大等待时间*/
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        /*开始等待*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if( retval == -1 )
        {
            printf("将退出,select出错! %s", strerror(errno));
            break;
        }
        else if(retval == 0)
        {
            continue;
        }
        else
        {
            if(FD_ISSET(sockfd, &rfds))
            {
                /*连接的sockfd上有消息到来则接收对方发过来的消息并显示*/
                memset(buffer, '\0', MAXBUF+1);

                /*接收对方发过来的消息,最多接收MAXBUF个字节*/
                len = read(sockfd, buffer, MAXBUF+1);
                if(len >= 0)
                {
                    if(strncmp(buffer, "quit", 4) == 0)
                    {
                        printf("对方退出了,聊天终止\n");
                        break;
                    }
                    printf("接收消息成功:'%s',共%d个字节的数据\n", buffer, len);
                }
                else if(len < 0)
                {
                    printf("接收消息失败!错误代码是%d,错误信息是'%s'\n", errno, strerror(errno));
                }
            }/*end of if(FD_ISSET(sockfd, &rfds))*/

            if(FD_ISSET(0, &rfds))
            {
                /*用户按键了,则读取用户输入的内容发送出去*/
                memset(buffer, '\0', MAXBUF+1);
                fgets(buffer, MAXBUF, stdin);  //输入消息
                /*
                if(strncmp(buffer, "quit", 4) == 0)
                {
                    printf("自己请求终止聊天\n");
                    break;
                }
                */
                /*发送消息给服务器端*/
                len = write(sockfd, buffer, strlen(buffer)-1);
                if(len < 0)
                {
                    printf("消息’%s‘,发送失败!错误代码是%d,错误信息是'%s'\n", buffer, errno, strerror(errno));
                    break;
                }
                else
                {
                    printf("消息:%s\t发送成功,共发送了%d个字节!\n", buffer, len);
                }
                if(strncmp(buffer, "quit", 4) == 0)
                {
                    printf("自己请求终止聊天!\n");
                    break;
                }
            }/*end of if(FD_ISSET(0, &rfds))*/
        }
    }/*end of while(1)*/

    /*关闭连接*/
    close(sockfd);

    return 0;
}
