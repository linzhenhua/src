/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月12日 09时56分38秒
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
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd;                     //套接字
    int new_fd;                     //accept返回值
    socklen_t len;                  //地址长度
    struct sockaddr_in my_addr;     //自己的地址
    struct sockaddr_in their_addr;  //对方地址
    unsigned int myport;            //端口号
    unsigned int lisnum;            //监听数
    char buffer[MAXBUF+1];          //缓冲
    fd_set rfds;                    //句柄
    struct timeval tv;              //等待时间
    int retval;                     //select返回值
    int maxfd = -1;                 //最大描述符

    if(argc != 3)
    {
        printf("请按照格式输入:usage:a.out 端口号 监听数\n");
        exit(0);
    }
    myport = atoi(argv[1]);
    lisnum = atoi(argv[2]);

    /*设置套接字*/
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        perror("socket");
        exit(0);
    }
    else
    {
        printf("socket OK\n");
    }

    /*设置地址*/
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*绑定套接字*/
    if( bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1 )
    {
        perror("bind");
        exit(0);
    }
    else
    {
        printf("bind OK\n");
        printf("服务端IP:%s,端口号:%d,监听数:%d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port), lisnum);
    }

    /*开始监听*/
    if(listen(sockfd, lisnum) == -1)
    {
        perror("listen");
        exit(0);
    }
    else
    {
        printf("listen...\n");
    }

    while(1)
    {
        printf("\n----等待新的连接到来开始新一轮聊天----\n");

        len = sizeof(struct sockaddr);
        if( (new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &len)) == -1 )
        {
            perror("accept");
            exit(0);
        }
        else
        {
            printf("server: get connection from %s, port: %d,socket: %d\n",
                    inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);
        }

        /*开始处理每个新连接上的数据收发*/
        printf("\n服务端准备就绪,可以开始聊天..直接输入消息回车即可发送信息给对方\n");
        
        for(;;)
        {
            /*把集合清空*/
            FD_ZERO(&rfds);
            
            /*把标准输入句柄0加入到集合中*/
            FD_SET(0, &rfds);
            maxfd = 0;

            /*把当前连接句柄new_fd加入到集合中*/
            FD_SET(new_fd, &rfds);
            if(new_fd > maxfd)
                maxfd = new_fd;

            /*设置最大等待时间*/
            tv.tv_sec = 1;
            tv.tv_usec = 0;

            /*开始等待*/
            retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
            if(retval == -1)
            {
                printf("将退出,select出错!%s\n", strerror(errno));
                break;
            }
            else if(retval == 0)
            {
                continue;
            }
            else
            {
                if(FD_ISSET(new_fd, &rfds))
                {
                    /*当前连接的socket上有消息到来则接收对方发过来的消息并显示*/
                    memset(buffer, '\0', MAXBUF+1);
                    
                    /*接收客户端的消息*/
                    len = read(new_fd, buffer, MAXBUF);
                    if(len >= 0)
                    {
                        if(strncmp(buffer, "quit", 4) == 0)
                        {
                            printf("对方退出了,聊天终止\n");
                            break;
                        }
                        printf("接收消息成功:'%s', 共%d个字节的数据\n", buffer, len);
                    }
                    else
                    {
                        printf("接收消息失败!错误代码是%d,错误信息是'%s'\n", errno, strerror(errno));
                        break;
                    }
                }/*end of if(FD_ISSET(new_fd, &rfds))*/

                if(FD_ISSET(0, &rfds))
                {
                    /*用户按键了,则读取用户输入的内容发送出去*/
                    memset(buffer, '\0', MAXBUF+1);
                    fgets(buffer, MAXBUF, stdin);

                    len = write(new_fd, buffer, strlen(buffer)-1);
                    if(len == -1)
                    {
                        printf("消息’%s‘发送失败!错误代码是%d, 错误信息是'%s'\n", buffer, errno, strerror(errno));
                        break;
                    }
                    else
                    {
                        if(strncmp(buffer, "quit", 4) == 0)
                        {
                            printf("自己请求终止聊天!\n");
                            break;
                        }
                        printf("消息:%s\t发送成功,共发送%d个字节!\n", buffer, len);
                    }
                }/*end of if(FD_ISSET(0, &rfds))*/
            }
        }/*for(;;)*/
        close(new_fd);
        
        /*处理每个新连接上的数据收发结束*/
        printf("还要和其他连接聊天吗?(no->退出)\n");
        fflush(stdout);
        memset(buffer, '\0', MAXBUF);
        fgets(buffer, MAXBUF, stdin);
        if(strncmp(buffer, "no", 2) == 0)
        {
            printf("终止聊天!\n");
            break;
        }
    }/*end of while(1)*/
    close(sockfd);

    return 0;
}
