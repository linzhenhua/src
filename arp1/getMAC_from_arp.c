#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if_arp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <error.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*根据给定协议地址addr从ARP缓冲表中获得对应的mac地址存放到haddr中去
   @devname:指定网络接口设备名字
   @flag:flag=1时如果从ARP缓冲表中未找到对应的入口项,则执行arping命令来发送arp请求
            flag=0时如果从ARP缓冲表中未找到对应的入口项,则退出
   @count:如果从ARP缓冲表中未找到对应的入口项,执行arping命令来发送arp请求的次数
   如果成功找到返回1,失败返回0*/
int getMAC_fromARP(struct sockaddr *addr, struct sockaddr *haddr, char *devname,int flag,int count)
{
	int sockfd;
	struct arpreq arpreq;
	
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0){
		fprintf(stderr,"%d:socket error!",error);
		return 0;
	}
	memset(&arpreq,0,sizeof(struct arpreq));
	arpreq.arp_pa=*addr;
	strcpy(arpreq.arp_dev,devname);
	ioctl(sockfd,SIOCGARP,&arpreq);

	if(!arpreq.arp_flags&&flag){
		int pid;
		
		close(sockfd);
		pid=fork();
		if(!pid){
			switch(addr->sa_family){
				char *address;
				char c[100];

				case AF_INET:
					address=inet_ntoa(((struct sockaddr_in *)addr)->sin_addr);
					sprintf(c,"%d",count);
					if(execle("/sbin/arping","arping","-c",c,address,"-I",devname,NULL,NULL)<0){
						err_sys("/sbin/arping -c %s %s error",c,address);
					}
					break;
				case AF_INET6:
					fprintf(stderr,"IPv6 not support in the command arping!\n");
					exit(1);
				default:
					fprintf(stderr,"not support protocol in the command arping!\n");
					exit(1);
			}
		}
		while(waitpid(pid,NULL,0)>=0);		
		return(getMAC_fromARP(addr,haddr,devname,0,count));
	}
	close(sockfd);
	if(!arpreq.arp_flags)
		return 0;
	memcpy((char *)haddr,(char *)&arpreq.arp_ha,sizeof(struct sockaddr));
	return 1;
}


/*
//将物理地址以十六进制字符串形式打印到macstr中去
void printMAC(char *macstr, unsigned char *mac, int haddrlen)
{
	char *tmp;
	int i;

	tmp=macstr;
	for(i=0;i<haddrlen-1;i++){
		sprintf(tmp,"%x:",mac[i]);
		tmp+=strlen(tmp);
	}
	sprintf(tmp,"%x",mac[i]);
}

int
main()
{
	char str[100];
	struct sockaddr_in sin;
	struct sockaddr haddr;
	unsigned char mac[6];

	sin.sin_family=AF_INET;
	scanf("%s",str);
	inet_aton(str, &sin.sin_addr);
	if(getMAC_fromARP((struct sockaddr *)&sin,&haddr,"eth0",1,2)==0)
		return;
	printMAC(str,haddr.sa_data,6);
	fprintf(stdout,"%s\n",str);
}
*/
