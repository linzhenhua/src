/************************************************
 * cl_sock.c                                    *
 * function:                                    *
 *    create a socket                           *
 *    create a new thread,for receive function  *
 *    send message                              *
 ************************************************/
#include "client.h"

int sockfd;
struct sockaddr_in saddr;

int build_socket(const char *serv_ip)
{
	int res;
	pthread_t recv_thread;
	pthread_attr_t thread_attr;

	/* set status of thread */
	res=pthread_attr_init(&thread_attr);
	if(res!=0)
	{
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,0); /* create a socket */
	if(sockfd==-1)
	{
		perror("Socket Error");
		exit(1);
	}

	bzero(&saddr,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	res=inet_pton(AF_INET,serv_ip,&saddr.sin_addr);
	if(res==0){ /* the serv_ip is invalid */
		return 1;
	}
	else if(res==-1){
		return -1;
	}

	/* set the stats of thread:means do not wait for the return value of subthread */
	res=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
	if(res!=0)
	{
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}

	/* Create a thread,to process the receive function. */
	res=pthread_create(&recv_thread,&thread_attr,&recv_func,NULL);
	if(res!=0)
	{
		perror("Thread create error");
		exit(EXIT_FAILURE);
	}

	/* callback the attribute */
	(void)pthread_attr_destroy(&thread_attr);
	return 0;
}

/* send function */
void send_func(const char *text)
{
	int n;
	socklen_t len=sizeof(saddr);

	n=sendto(sockfd,text,MAXSIZE,0,(const struct sockaddr*)&saddr,len);
	if(n<0)
	{
		perror("S send error");
		exit(1);
	}
}

/* a new thread,to receive message */
void *recv_func(void *arg)
{
	char rcvd_mess[MAXSIZE];
	while(1)
	{
		bzero(rcvd_mess,MAXSIZE);
		if(recvfrom(sockfd,rcvd_mess,MAXSIZE,0,NULL,NULL)<0)  /*阻塞直到收到客户端发的消息*/
		{
			perror("server recv error");
			exit(1);
		}
		show_remote_text(rcvd_mess);
	}
}
