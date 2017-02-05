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

/*���ݸ���Э���ַaddr��ARP������л�ö�Ӧ��mac��ַ��ŵ�haddr��ȥ
   @devname:ָ������ӿ��豸����
   @flag:flag=1ʱ�����ARP�������δ�ҵ���Ӧ�������,��ִ��arping����������arp����
            flag=0ʱ�����ARP�������δ�ҵ���Ӧ�������,���˳�
   @count:�����ARP�������δ�ҵ���Ӧ�������,ִ��arping����������arp����Ĵ���
   ����ɹ��ҵ�����1,ʧ�ܷ���0*/
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
//�������ַ��ʮ�������ַ�����ʽ��ӡ��macstr��ȥ
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
