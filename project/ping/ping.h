/*
 * =====================================================================================
 *
 *       Filename:  ping.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月19日 09时46分28秒
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
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>

/*处理服务端返回的ICMP回显信息*/
void proc_msg(char *, ssize_t, struct msghdr *, struct timeval *);

/*发送ICMP回显请求*/
void send_msg(void);

/*循环发送,接收消息*/
void readloop(void);

/*定时器入门函数，每隔一秒发送ICMP请求*/
void sig_alrm(int);

/*计算两个时间之间的间隔*/
void tv_sub(struct timeval *, struct timeval *);

/*获得服务器的地址等信息*/
struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype);

/*根据服务器信息，得到服务器的IP地址*/
char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

/*计算校验和*/
uint16_t in_cksum(uint16_t *addr, int len);
