static	int	bigendian;

#include "arpdeceive.h"

/*命令行中所对应的长选项*/
struct	option	longopts[]=
{
	{"sha", required_argument, NULL, 'h'},
	{"sip", required_argument, NULL, 's'},
	{"dip", required_argument, NULL, 'd'},
	{"exclusive", required_argument, NULL, 'e'},
	{"interface", required_argument, NULL, 'i'},
	{"ifindex",required_argument,NULL,'x'},	
	{"count",required_argument,NULL,'c'},
	{"flag",0,NULL,'f'},
	{"broadcast",0,NULL,'b'},
	{0, 0, 0, 0}
};

static	int maclen=6;/*物理地址长度暂设定为6,以太网物理地址长度*/

void send_arprequest(unsigned char hlen, u_int16_t arp_hardware_type, u_int32_t sip,u_int32_t dip, char *sha, 
						int ifindex,int flag,int count,char *devname,int bcstflag){
		int sockfd;
		struct sockaddr_ll shaddr,dhaddr;
		struct sockaddr_in sin;
		struct sockaddr haddr;
		struct arphdr *arpheader;
		char dha[IFI_HADDR]={0xff,0xff,0xff,0xff,0xff,0xff,'\0'},*tmp;
	
		memset(&sin,0,sizeof(struct sockaddr_in));
		sin.sin_family=AF_INET;
		sin.sin_addr.s_addr=dip;
		if(!getMAC_fromARP((struct sockaddr *)&sin,&haddr,devname,flag,count))
			return;
		sockfd=Socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
	
		memset(&shaddr,0,sizeof(struct sockaddr_ll));
		shaddr.sll_family=AF_PACKET;
		shaddr.sll_protocol=htons(ETH_P_ARP);
		shaddr.sll_ifindex=ifindex;
		shaddr.sll_hatype=arp_hardware_type;
		shaddr.sll_halen=hlen;
		memcpy(shaddr.sll_addr,sha,hlen);
	
		Bind(sockfd,(struct sockaddr *)&shaddr,sizeof(struct sockaddr_ll));
	
		memset(&dhaddr,0,sizeof(struct sockaddr_ll));
		dhaddr.sll_family=AF_PACKET;
		dhaddr.sll_protocol=htons(ETH_P_ARP);
		dhaddr.sll_ifindex=ifindex;
		dhaddr.sll_hatype=arp_hardware_type;
		dhaddr.sll_halen=hlen;
		if(bcstflag){
			dhaddr.sll_pkttype=PACKET_BROADCAST;
			memcpy(dhaddr.sll_addr,dha,hlen);
		}
		else
			memcpy(dhaddr.sll_addr,haddr.sa_data,hlen);
		
		arpheader=(struct arphdr *)Malloc(sizeof(struct arphdr)+2*(hlen+4));
		arpheader->ar_hrd=htons(arp_hardware_type);
		arpheader->ar_pro=htons(ETH_P_IP);
		arpheader->ar_hln=hlen;
		arpheader->ar_pln=4;
		arpheader->ar_op=htons(ARPOP_REQUEST);
	//#ifdef DEBUG
	//	print(sip);
	//	print(dip);
	//#endif
		memcpy(arpheader+1, sha, hlen);
		memcpy((char *)(arpheader+1)+hlen, (char *)&sip, 4);
		memset((char *)(arpheader+1)+hlen+4, 0, hlen);
		memcpy((char *)(arpheader+1)+2*hlen+4, (char *)&dip, 4);
	//#ifdef DEBUG
	//	print((u_int32_t *)((char *)(arpheader+1)+hlen));
	//#endif
		sendto(sockfd, arpheader, sizeof(struct arphdr)+2*(hlen+4), 0, 
				(struct sockaddr_ll *)&dhaddr, sizeof(struct sockaddr_ll));
		Close(sockfd);
}

int	main(int argc,char **argv)
{	
	char   helpinfo[]={"arprequest	[-s hostip][-s hostip1,hostip2][-s hostip/netmask] specify the arp request's source ip address or the address range by it's corresponding netmask\n
		[-d hostip][-d hostip1,hostip2][-d hostip/netmask] specify the arp request's dst ip address or the address range by it's corresponding netmask\n
		[--sha phyisicalladdress] specify the arp request's source hardware address\n
		[-e hostip][-e hostip1,hostip2][-e hostip/netmask] specify the exclusive ip address or the address range by it's corresponding netmask\n
		[-i interface] specify the net interface which is sent arp request with\n
		[-c count] specify the sending arp request's times if failing to get the mac from arp cache ,default 2\n		
		[-f] call the command arping to sending the arp response if failing to get the mac from arp cache\n 
		[-b] sending the arp response datagram with the broadcast destination physical address\n" };				
	
	struct	in_addr	 snetmask,shoststart,shostend,dnetmask,dhoststart,dhostend,enetmask,ehoststart,ehostend,saddr,netmask;
	struct	in_addr	tmpdaddrstart,tmpdaddrend;
	char 	c,shaddr[IFI_HADDR],ifi_name[IFI_NAME],haddr[IFI_HADDR];
	int		hlen,ifindex,shaddrflag=0,count=1,flag=0,bcstflag=0;

	*shaddr=*ifi_name='\0';
	snetmask.s_addr=0;
	shoststart.s_addr=0;
	shostend.s_addr=0;
	dnetmask.s_addr=0;
	dhoststart.s_addr=0;
	dhostend.s_addr=0;
	enetmask.s_addr=0;
	ehoststart.s_addr=0;
	ehostend.s_addr=0;
	isbigendian();/*检验系统是bigendian还是littleendian*/
	while((c=getopt_long(argc,argv,":s:d:e:h:i:c:fb",longopts,NULL))!=-1)
	{
		unsigned int nsaddrs = 0;
		struct in_addr *saddrs = NULL;
		u_int32_t incre,startip;

		switch(c)
		{
			case 's':
				host_check(optarg, &shoststart.s_addr, &shostend.s_addr);
				if(shoststart.s_addr&&!shostend.s_addr)
					shostend.s_addr=shoststart.s_addr;
				if(!shoststart.s_addr)
				{
					parse_hostnetworkmask(optarg, &saddrs, &snetmask, &nsaddrs);
					if(!snetmask.s_addr){
						shoststart=*saddrs;
						shostend=*saddrs;
						break;
					}
					cmpipaddr(saddrs->s_addr,snetmask.s_addr,&startip,&incre);
					shoststart.s_addr=startip;
					swap(&shoststart.s_addr);/*为了下面的hostend的计算，将二进制主机地址倒置*/
					shostend.s_addr=shoststart.s_addr+incre;
					swap(&shostend.s_addr);	
					swap(&shoststart.s_addr);/*将二进制主机地址倒置*/
				}
				break;
			case 'd':
				host_check(optarg, &dhoststart.s_addr, &dhostend.s_addr);
				if(dhoststart.s_addr&&!dhostend.s_addr)
					dhostend.s_addr=dhoststart.s_addr;
				if(!dhoststart.s_addr)
				{
					parse_hostnetworkmask(optarg, &saddrs, &dnetmask, &nsaddrs);
					if(!dnetmask.s_addr){
						dhoststart=*saddrs;
						dhostend=*saddrs;
						break;
					}
					cmpipaddr(saddrs->s_addr,dnetmask.s_addr,&startip,&incre);
					dhoststart.s_addr=startip;
					swap(&dhoststart.s_addr);/*为了下面的hostend的计算，将二进制主机地址倒置*/
					dhostend.s_addr=dhoststart.s_addr+incre;
					swap(&dhostend.s_addr);	
					swap(&dhoststart.s_addr);/*将二进制主机地址倒置*/
				}
				break;
			case 'e':
				host_check(optarg, &ehoststart.s_addr, &ehostend.s_addr);
				if(ehoststart.s_addr&&!ehostend.s_addr)
					ehostend.s_addr=ehoststart.s_addr;
				if(!ehoststart.s_addr)
				{
					parse_hostnetworkmask(optarg, &saddrs, &enetmask, &nsaddrs);
					if(!enetmask.s_addr){
						ehoststart=*saddrs;
						ehostend=*saddrs;
						break;
					}
					cmpipaddr(saddrs->s_addr,enetmask.s_addr,&startip,&incre);
					ehoststart.s_addr=startip;
					swap(&ehoststart.s_addr);/*为了下面的hostend的计算，将二进制主机地址倒置*/
					ehostend.s_addr=ehoststart.s_addr+incre;
					swap(&ehostend.s_addr);	
					swap(&ehoststart.s_addr);/*将二进制主机地址倒置*/
				}
				break;
			case 'h':
				if(getMAC(optarg,shaddr,maclen)<0)
					err_quit("the mac address is wrong!");
				shaddrflag=1;
				break;	
			case 'i':
				strcpy(ifi_name,optarg);
				break;
			case 'c':
				count=atoi(optarg);
				if(count<0)
					count=1;
				if(count>6)/*最大的ARP发送请求的个数为6*/
					count=6;
				break;
			case 'f':
				flag=1;
				break;
			case 'b':
				bcstflag=1;
				break;
			case ':':
				/*缺少选项参数*/
				fprintf(stderr,"%s:option '-%c' requires an argument\n",argv[0],optopt);
				exit(1);
			case '?':
			default:
				/*无效选项*/
				fprintf(stderr,"%s:option '-%c' is invalid\n",argv[0],optopt);
				exit(1);
		}
	}
	
	if(argc==1)
	{
		fprintf(stderr,"%s\n",helpinfo);/*输出帮助信息*/
		exit(0);
	}
	
	if(optind<argc)
		err_quit("It needs no operator in the command line");
		
	if(!dhoststart.s_addr)
		err_quit("you must specify the destination ip address!");
	if(*ifi_name=='\0')
		err_quit("you must specify the interface!");

	saddr=get_interface_info(ifi_name, haddr, &hlen,&netmask,&ifindex);
	if(!saddr.s_addr)
		err_quit("can't find the information about net interface %s!",ifi_name);

	if(!shoststart.s_addr){
		u_int32_t incre,startip;
		
		cmpipaddr(saddr.s_addr,netmask.s_addr,&startip,&incre);
		shoststart.s_addr=startip;
		swap(&shoststart.s_addr);/*为了下面的hostend的计算，将二进制主机地址倒置*/
		shostend.s_addr=shoststart.s_addr+incre;
		swap(&shostend.s_addr);	
		swap(&shoststart.s_addr);/*将二进制主机地址倒置*/
	}
	if(!shaddrflag)
		memcpy(shaddr,haddr,hlen);
#ifdef DEBUG
	fprintf(stdout,"netmask=%s\n",inet_ntoa(netmask));
	fprintf(stdout,"shoststart=%s\n",inet_ntoa(shoststart));
	fprintf(stdout,"shostend=%s\n",inet_ntoa(shostend));
	fprintf(stdout,"dhoststart=%s\n",inet_ntoa(dhoststart));
	fprintf(stdout,"dhostend=%s\n",inet_ntoa(dhostend));
	fprintf(stdout,"ehoststart=%s\n",inet_ntoa(ehoststart));
	fprintf(stdout,"ehostend=%s\n",inet_ntoa(ehostend));
#endif
	swap(&ehostend.s_addr);	
	swap(&ehoststart.s_addr);
	tmpdaddrstart=dhoststart;
	tmpdaddrend=dhostend;
	for(swap(&shoststart.s_addr),swap(&shostend.s_addr);
		shoststart.s_addr<=shostend.s_addr;shoststart.s_addr++){
			if(in_exclusive(shoststart.s_addr, ehoststart.s_addr, ehostend.s_addr))
				continue;
			dhoststart=tmpdaddrstart,dhostend=tmpdaddrend;
			for(swap(&dhoststart.s_addr),swap(&dhostend.s_addr);
			dhoststart.s_addr<=dhostend.s_addr;dhoststart.s_addr++){
							u_int32_t sip,dip;
							
							if(in_exclusive(dhoststart.s_addr, ehoststart.s_addr, ehostend.s_addr))
								continue;
							sip=shoststart.s_addr;
							dip=dhoststart.s_addr;
							swap(&dip);
							swap(&sip);
/*
#ifdef DEBUG
	fprintf(stdout,"sip=%s\n",inet_ntoa((struct in_addr){sip}));
	fprintf(stdout,"dip=%s\n",inet_ntoa((struct in_addr){dip}));
#endif
*/
							send_arprequest(hlen, ARPHRD_ETHER, sip, dip, shaddr,ifindex,flag,
											count,ifi_name,bcstflag);
			}/*end for*/
	}/*end for*/
}

