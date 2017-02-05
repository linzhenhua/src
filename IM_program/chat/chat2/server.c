/*************************************************
 * server.c                                      *
 * Function:                                     *
 *   receive message from client and print it    *
 *   send message to client                      *
 *************************************************/

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <errno.h> 
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAXSIZE 1024

int sockfd;
struct sockaddr_in saddr,caddr;
socklen_t len=sizeof(caddr);

/* Receive function */
void *recv_func(void *arg)
{
	char recv_text[MAXSIZE];
	while(1)
	{	/* To Receive message from client and get the address infomation */
		if(recvfrom(sockfd,recv_text,sizeof(recv_text),0,(struct sockaddr*)&caddr,&len)<0)  
		{
			perror("server recv error");
			exit(1);
		}
		printf("%s: %s \n",inet_ntoa(*(struct in_addr*)&caddr.sin_addr),recv_text);
	}
}

/* Send function,send message to client */
void send_func()
{
	char send_text[MAXSIZE];

	while(1)
	{
		bzero(send_text,MAXSIZE);
		fgets(send_text,MAXSIZE,stdin);

		/* If there is no text,continue */
		if(strlen(send_text)==1)
			continue;
		/* Send message */	
		if(sendto(sockfd,send_text,strlen(send_text),0,(struct sockaddr*)&caddr,len)<0)
		{
			perror("S send error");
			exit(1);
		}
		
	}
}

int main(int argc,char **argv)
{
	int res;
	pthread_t recv_thread;
	pthread_attr_t thread_attr;

	/* Set status of thread */
	res=pthread_attr_init(&thread_attr);
	if(res!=0)
	{
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}

	/* Create a socket */
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socket Error");
		exit(1);
	}

	bzero(&saddr,sizeof(struct sockaddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(PORT);

	if(bind(sockfd,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in))==-1)
	{
		perror("Bind Error");
		exit(1);
	}

	/* Set the status of thread,don't wait for return of the subthread */
	res=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
	if(res!=0)
	{
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}

	/* Create a sub thread,call recv_func() */
	res=pthread_create(&recv_thread,&thread_attr,recv_func,NULL); 
	if(res!=0)
	{
		perror("Thread create error");
		exit(EXIT_FAILURE);
	}

	/* Callback the attribute of thread */
	(void)pthread_attr_destroy(&thread_attr);

	/* Call send_func */
	send_func();
	return 0;
}
