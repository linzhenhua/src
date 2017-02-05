#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*���������ʮ�����Ʊ�ʾ�������ַ�ַ���ת������ֵ��ʽ�������ַ
   ����0:a:0::c:d Ϊʮ�����Ƶ������ַ�ַ���
   @haddrlen:�����ַ�ĳ���
   �����ɹ�ת������0,ʧ�ܷ���-1*/
int getMAC(char *macstr, unsigned char *mac, int haddrlen)
{
	char *str,*first;
	int i,maclen,j=0;

	maclen=strlen(macstr);
	str=(char *)malloc(maclen+1);
	if(!str){
		fprintf(stderr,"malloc error:there is no free space!\n");
		exit(1);
	}
	memset(mac,0,haddrlen);
	strcpy(str,macstr);
	first=str;
	for(i=0;i<=maclen;i++){
		char tmp;
		tmp=*(str+i);
		if(!((tmp>='0'&&tmp<='9')||(tmp>='a'&&tmp<='f')||(tmp>='A'&&tmp<='F')||tmp==':'||tmp=='\0'))
			return -1;
		if(tmp==':'||tmp=='\0'){
			*(str+i)='\0';
			if(str+i-first>2)
				return -1;
			if(j>=haddrlen)
				return -1;
			sscanf(first,"%x",mac+(j++));
			first=str+i+1;
		}
	}
	return 0;
}

/*�������ַ��ʮ�������ַ�����ʽ��ӡ��macstr��ȥ*/
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

/*
int
main()
{
	char str[100];
	unsigned char mac[6];

	scanf("%s",str);
	if(getMAC(str, mac, 6)<0){
		fprintf(stderr,"The mac address is wrong!\n");
		exit(1);
	}
	printMAC(str,mac,6);
	fprintf(stdout,"%s\n",str);
}
*/
