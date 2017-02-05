#include "unpifi.h"
#include "selfdefine.h"
#include <net/if_arp.h>

#ifdef DEBUG
static inline void print(u_int32_t ip){
	char *t=(char *)&ip;
	fprintf(stdout,"%d.%d.%d.%d\n",*t,*(t+1),*(t+2),*(t+3));
}
#endif

static inline void isbigendian()
{
	int	a=1;
	if(*((char *)&a)!=1)
		bigendian=1;
}

/*将二进制IP地址高低位对换*/
static inline void	swap(u_int32_t *ipaddr)
{
	/*	
		char	t;
		int	i,j=sizeof(u_int32_t)/2,k=sizeof(u_int32_t);		

		for(i=0; i<j; i++)
		{
			t=*((char *)ipaddr+i);
			*((char *)ipaddr+i)=*((char *)ipaddr+k-i-1);	
			*((char *)ipaddr+k-i-1)=t;	
		}
	*/
	if(!bigendian)
		*ipaddr=htonl(*ipaddr);
	return;
}

/*
	对输入的主机地址字符串，例如-h 192.168.1.1,192.168.1.254进行地址范围
	正确性检验，并且将两个地址保存在hoststart与hostend中
*/
static inline void	host_check(char *hosts, u_int32_t *hoststart, u_int32_t *hostend)
{
	int		i,len,multihosts_flag=0;

	*hoststart=*hostend=0;/*为了防止命令行重复输入同一个选项，每当遇到
							该选项而调用该函数时都应清零*/
	len=strlen(hosts);
	
	for(i=0; i<len; i++)
	/*注意：这里有一种特殊情况-p 345,(逗号后面没数字)这时mutlports_flag=1,
	   *portend=0,*portstart1=0*/
	{
		if(hosts[i]==',')
		{
			multihosts_flag=1;
			hosts[i]='\0';
			inet_aton(hosts,(struct in_addr *)hoststart);
			hosts+=(i+1);
			len=len-i-1;
			i=-1;
			continue;
		}
		if(*(hosts+i+1)=='\0')
		{
			if(multihosts_flag)
				inet_aton(hosts,(struct in_addr *)hostend);
			else
				inet_aton(hosts,(struct in_addr *)hoststart);
		}
	}/*end for*/

	if(multihosts_flag&&(*hostend==*hoststart))	/*例如-p 192.168.1.1,192.168.1.1当成单一
											   IP地址192.168.1.1，而不是地址范围*/
		*hostend=0;
	
	swap(hoststart);
	swap(hostend);
	if(multihosts_flag&&(*hostend)&&(*hostend<*hoststart))	
		/*输入的第二个IP地址必须大于第一个,必须保证*portend!=0,
		因为会出现上述-h 192.168.1.1,	*/
		err_quit("The second host ip address must be bigger that the first");	
	swap(hoststart);
	swap(hostend);
}


/*
	给定ip地址及其掩码，计算出ip地址范围，这里没有ip地址及其
	掩码的错误检验机制。计算出的ip地址范围不包含网络地址与
	广播地址，所以startip应为网络地址加1，startip+incre+1为其网络广播地址。
*/
static inline void	cmpipaddr(u_int32_t ipaddr, u_int32_t netmask, u_int32_t *startip, u_int32_t *incre)
{
	u_int32_t	i=0,j;

	swap(&ipaddr);
	swap(&netmask);

	j=netmask;
	if(netmask==IN_ADDR_BROADCAST)
	{
		*startip=ipaddr;
		*incre=0;
		swap(&ipaddr);
		swap(startip);
		return;
	}	
	
	while((netmask&1)==0)
	{	
		netmask>>=1;
		i++;
	}
	netmask=j;
	*startip=(ipaddr&netmask);
	*incre=(1<<i)-2;

	swap(&ipaddr);
	swap(&netmask);
	swap(startip);
}

static inline struct in_addr get_interface_info(char *ifname,char *haddr,int *hlen,struct in_addr *netmask,int *ifindex){
	struct ifi_info	*ifi, *ifihead;
	struct sockaddr	*sa;
	u_char			*ptr;
	int				i, family, doaliases;

	for (ifihead = ifi = Get_ifi_info(AF_INET, 0);
		 ifi != NULL; ifi = ifi->ifi_next) {
#ifdef DEBUG
		fprintf(stdout,"interface=%s\n",ifi->ifi_name);
		fprintf(stdout,"mtu=%d\n",ifi->ifi_mtu);
		fprintf(stdout,"hardware type=%u\n",ifi->ifi_hatype);
		fprintf(stdout,"hardware address=");
		for(i=0;i<ifi->ifi_hlen;i++)
			fprintf(stdout,"%x:",*(ifi->ifi_haddr+i));
		fprintf(stdout,"\n");
		fprintf(stdout,"header len=%u\n",ifi->ifi_hlen);
		if(ifi->ifi_addr)
			fprintf(stdout,"ip address=%s\n",inet_ntoa(((struct sockaddr_in *)(ifi->ifi_addr))->sin_addr));	
		if(ifi->ifi_netmask)
			fprintf(stdout,"netmask=%s\n",inet_ntoa(((struct sockaddr_in *)(ifi->ifi_netmask))->sin_addr));
		if(ifi->ifi_brdaddr)
			fprintf(stdout,"broad address=%s\n",inet_ntoa(((struct sockaddr_in *)(ifi->ifi_brdaddr))->sin_addr));
		if(ifi->ifi_dstaddr)
			fprintf(stdout,"dst address=%s\n",inet_ntoa(((struct sockaddr_in *)(ifi->ifi_dstaddr))->sin_addr));
		fprintf(stdout,"interface index=%d\n",ifi->ifi_index);	
		fprintf(stdout,"\n");
#endif
		if(strcmp(ifname,ifi->ifi_name))
			continue;
		if ( (i = ifi->ifi_hlen) > 0) {
			*hlen=ifi->ifi_hlen;
			memcpy(haddr,ifi->ifi_haddr,ifi->ifi_hlen);
			*netmask=((struct sockaddr_in *)(ifi->ifi_netmask))->sin_addr;
			*ifindex=ifi->ifi_index;
			return(((struct sockaddr_in *)(ifi->ifi_addr))->sin_addr);
		}
	}
	free_ifi_info(ifihead);
	return((struct in_addr){0});
}
static inline int in_exclusive(u_int32_t host, u_int32_t ehoststart, u_int32_t ehostend){
	return(host>=ehoststart&&host<=ehostend);
}
