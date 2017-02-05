/*
 * =====================================================================================
 *
 *       Filename:  ping.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月19日 09时59分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include "ping.h"

#define BUFSIZE 1500
#define DATALEN 56

struct _proto
{
    struct sockaddr *sasend;       //sockaddr{} for send, form getaddrinfo   //通用套接口地址结构
    struct sockaddr *sarecv;       //sockaddr{} for receiving
    socklen_t salen;               //length of sockaddr{}s
    int icmpproto;                 //IPPROTO_XXX value for ICMP
};

/*全局变量*/
pid_t pid;          //进程ID
int sockfd;         //套接字
struct _proto proto = {NULL, NULL, 0, IPPROTO_ICMP};

int main(int argc, char **argv)
{
    struct addrinfo *ai;        
    char *host;
    char *ip_address;

    /*本程序只支持一种输入方式: ./ping <hostname>*/
    if(argc != 2)
    {
        printf("usage: ./ping <hostname>\n");
        exit(1);
    }

    host = argv[1];    /*获取服务器的IP地址*/

    /*将pid的高二位全置为0，ICMP的ID只有16位*/
    pid = getpid() & 0xffff;

    /*设置定时器，每秒钟向服务器发送一次请求*/
    signal(SIGALRM, sig_alrm);

    /*获取服务器的信息(addrinfo结构)*/
    ai = host_serv(host, NULL, 0, 0);
    ip_address = sock_ntop_host(ai->ai_addr, ai->ai_addrlen);

    printf("PING %s (%s): %d data bytes\n", ai->ai_canonname ? ai->ai_canonname : ip_address, ip_address, DATALEN);

    /*如果返回的协议族不是AF_INET(IPv4)，则退出*/
    if( ai->ai_family != AF_INET )
    {
        printf("unknow address family\n");
        exit(1);
    }

    /*设置proto结构题*/
    proto.sasend = ai->ai_addr;
    proto.sarecv = calloc(1, ai->ai_addrlen);    //分配1个内存大小为ai->ai_addrlen
    if(NULL == proto.sarecv)
    {
        perror("calloc");
        exit(1);
    }
    proto.salen = ai->ai_addrlen;

    readloop();

    return 0;
}

void readloop(void)
{
    int size;
    char recvbuf[BUFSIZE];
    char controlbuf[BUFSIZE];
    struct msghdr msg;
    struct iovec iov;
    ssize_t n;
    struct timeval tval;

    /*创建一个IPv4的原始套接字*/
    if( (sockfd = socket(proto.sasend->sa_family, SOCK_RAW, proto.icmpproto)) == -1 )
    {
        perror("socket");
        exit(1);
    }

    /*放弃管理权限*/
    /*这个程序中，只用创建原始套接字时需要管理员权限*/
    setuid(getuid());

    /*设置socket的接收缓冲区*/
    size = 60 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));  //套接口选项

    /*发出第一个请求*/
    sig_alrm(SIGALRM);

    /*为recvmsg调用设置msghdr结构*/
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);
    msg.msg_name = proto.sarecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;

    /*开始死循环，不断读取和处理从服务器中返回的信息*/
    for(;;)
    {
        msg.msg_namelen = proto.salen;
        msg.msg_controllen = sizeof(controlbuf);
        
        if( (n = recvmsg(sockfd, &msg, 0)) == -1 )
        {
            if(errno == EINTR)
                continue;
            else
            {
                perror("recvmsg");
                exit(1);
            }
        }

        /*分析返回内容，产生输出*/
        gettimeofday(&tval, NULL);
        proc_msg(recvbuf, n, &msg, &tval);
    }/*end of for(;;)*/

}

void proc_msg(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
    int hlen1, icmplen;
    double rtt;
    struct ip *ip;
    struct icmp *icmp;
    struct timeval *tvsend;

    /*将服务器返回的字符串强转为ip结构*/
    ip = (struct ip *)ptr;

    /*得到IP表头的长度*/
    hlen1 = ip->ip_hl<<2;

    /*如果不是ICMP的应答，则返回*/
    if(ip->ip_p != IPPROTO_ICMP)
        return;

    icmp = (struct icmp *)(ptr + hlen1);
    /*长度不足，不是合法应答*/
    if( (icmplen = len-hlen1) < 8 )
        return;

    /*不是回显应答，返回*/
    if( icmp->icmp_type != ICMP_ECHOREPLY )
        return;

    /*不是我们发出的请求的应答，返回*/
    if( icmp->icmp_id != pid )
        return;

    /*长度不足，非法应答*/
    if( icmplen < 16 )
        return;

    /*计算网络延时*/
    tvsend = (struct timeval *)icmp->icmp_data;
    tv_sub(tvrecv, tvsend);
    rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

    /*输出信息*/
    printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
            icmplen, sock_ntop_host(proto.sarecv, proto.salen),
            icmp->icmp_seq, ip->ip_ttl, rtt);
}

void send_msg(void)
{
    int len;
    int res;
    struct icmp *icmp;
    char sendbuf[BUFSIZE];
    static int nsnet = 0;

    /*根据ICMPv4协议来设置发送信息*/
    icmp = (struct icmp *)sendbuf;

    /*ICMP回显请求*/
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;

    /*ICMP标识符字段为本进程的PID*/
    icmp->icmp_id = pid;

    /*ICMP序列号字段为不断递增的全局变量nsent*/
    icmp->icmp_seq = nsnet++;

    /*ICMP数据字段为当前时间截，空白部分填充0xa5*/
    memset(icmp->icmp_data, 0xa5, DATALEN);
    gettimeofday((struct timeval *)icmp->icmp_data, NULL);

    /*计算并填充校验和*/
    len = 8 + DATALEN;
    icmp->icmp_cksum = 0;
    icmp->icmp_cksum = in_cksum((u_short *)icmp, len);

    /*发送数据*/
    if( (res = sendto(sockfd, sendbuf, len, 0, proto.sasend, proto.salen)) == -1)
    {
        perror("sendto");
        exit(1);
    }
        
}

void sig_alrm(int signo)
{
    send_msg();
    alarm(1);
}

void tv_sub(struct timeval *out, struct timeval *in)
{
    /*将两个时间相减，并把结果存入第一个参数中(out -= in)*/
    if( (out->tv_usec -= in->tv_usec) < 0 )
    {
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}

struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype)
{
    int n;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = family;
    hints.ai_socktype = socktype;

    if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    {
        perror("getaddrinfo");
        exit(1);
    }

    return res;
}

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    static char str[128];
    struct sockaddr_in *sin = (struct sockaddr_in *)sa;

    /*本程序只支持IPv4协议*/
    if( sa->sa_family != AF_INET )
    {
        printf("sock_ntop_host: the type must be AF_INET\n");
        exit(1);
    }

    if( inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL )
    {
        perror("inet_ntop");
        exit(1);
    }

    return str;
}

/*《UNIX网络编程》书上的源码*/
uint16_t in_cksum(uint16_t *addr, int len)
{
    int nleft = len;
    uint32_t sum = 0;
    uint16_t *w = addr;
    uint16_t answer = 0;

    /*
    * Our algorithm is simple, using a 32 bit accumulator (sum), we add
    * sequential 16 bit words to it, and at the end, fold back all the
    * carry bits from the top 16 bits into the lower 16 bits.
    */
    while (nleft > 1)
    {
        sum += *w++;
        nleft -= 2;
    }

    /* 4mop up an odd byte, if necessary */
    if (nleft == 1)
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w ;
        sum += answer;
    }

    /* 4add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
    sum += (sum >> 16); /* add carry */
    answer = ~sum; /* truncate to 16 bits */
    return(answer);
}

