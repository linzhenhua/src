#include <getopt.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static void *
fw_malloc(size_t size)
{
	void *p;

	if ((p = malloc(size)) == NULL) {
		perror("iptables: malloc failed");
		exit(1);
	}
	return p;
}

static void *
fw_calloc(size_t count, size_t size)
{
	void *p;

	if ((p = calloc(count, size)) == NULL) {
		perror("iptables: calloc failed");
		exit(1);
	}
	return p;
}

static void
inaddrcpy(struct in_addr *dst, struct in_addr *src)
{
	/* memcpy(dst, src, sizeof(struct in_addr)); */
	dst->s_addr = src->s_addr;
}

/*������������ַ���ת�������ָ�ֵ��*ret�����ұ�֤��ֵ��
   ��Χ��min��max֮�䣬�ɹ�����0���򷵻�-1*/
int
string_to_number(const char *s, unsigned int min, unsigned int max,
		 unsigned int *ret)
{
	long number;
	char *end;

	/* Handle hex, octal, etc. */
	errno = 0;
	number = strtol(s, &end, 0);
	if (*end == '\0' && end != s) {
		/* we parsed a number, let's see if we want this */
		if (errno != ERANGE && min <= number && number <= max) {
			*ret = number;
			return 0;
		}
	}
	return -1;
}

/*��255.255.254.0��ʽ������ת������ֵ��ʽ��ʧ�ܷ��ؿ�ֵ*/
struct in_addr *
dotted_to_addr(const char *dotted)
{
	static struct in_addr addr;
	unsigned char *addrp;
	char *p, *q;
	unsigned int onebyte;
	int i;
	char buf[20];

	/* copy dotted string, because we need to modify it */
	strncpy(buf, dotted, sizeof(buf) - 1);
	addrp = (unsigned char *) &(addr.s_addr);

	p = buf;
	for (i = 0; i < 3; i++) {
		if ((q = strchr(p, '.')) == NULL)
			return (struct in_addr *) NULL;

		*q = '\0';
		if (string_to_number(p, 0, 255, &onebyte) == -1)
			return (struct in_addr *) NULL;

		addrp[i] = (unsigned char) onebyte;
		p = q + 1;
	}

	/* we've checked 3 bytes, now we check the last one */
	if (string_to_number(p, 0, 255, &onebyte) == -1)
		return (struct in_addr *) NULL;

	addrp[3] = (unsigned char) onebyte;

	return &addr;
}

static struct in_addr *
network_to_addr(const char *name)
{
	struct netent *net;
	static struct in_addr addr;

	if ((net = getnetbyname(name)) != NULL) {
		if (net->n_addrtype != AF_INET)
			return (struct in_addr *) NULL;
		addr.s_addr = htonl((unsigned long) net->n_net);
		return &addr;
	}

	return (struct in_addr *) NULL;
}

/*��������ָ����ip��ַ��������ʽ��ʾ*/
static struct in_addr *
host_to_addr(const char *name, unsigned int *naddr)
{
	struct hostent *host;
	struct in_addr *addr;
	unsigned int i;

	*naddr = 0;
	if ((host = gethostbyname(name)) != NULL) {
		if (host->h_addrtype != AF_INET ||
		    host->h_length != sizeof(struct in_addr))
			return (struct in_addr *) NULL;

		while (host->h_addr_list[*naddr] != (char *) NULL)
			(*naddr)++;/*�����õ����ip��ַ*/
		addr = fw_calloc(*naddr, sizeof(struct in_addr));
		for (i = 0; i < *naddr; i++)
			inaddrcpy(&(addr[i]),
				  (struct in_addr *) host->h_addr_list[i]);
		return addr;
	}

	return (struct in_addr *) NULL;
}

/*ָ��ĳһ���뽫��ת������ֵ��ʧ�ܷ��ؿ�ֵ
*/
static struct in_addr *
parse_mask(char *mask)
{
	static struct in_addr maskaddr;
	struct in_addr *addrp;
	unsigned int bits;

	if (mask == NULL) {/*δָ������˵��ָ��ĳһ�ض���IP��ַ�����������趨Ϊȫ1*/
		/* no mask at all defaults to 32 bits */
		maskaddr.s_addr = 0xFFFFFFFF;
		return &maskaddr;
	}
	if ((addrp = dotted_to_addr(mask)) != NULL)
		/* dotted_to_addr already returns a network byte order addr */
		return addrp;
	if (string_to_number(mask, 0, 32, &bits) == -1){
		fprintf(stderr,"invalid mask `%s' specified", mask);
		exit(1);
	}
	if (bits != 0) {
		maskaddr.s_addr = htonl(0xFFFFFFFF << (32 - bits));
		return &maskaddr;
	}

	maskaddr.s_addr = 0L;
	return &maskaddr;
}

/*
 *	All functions starting with "parse" should succeed, otherwise
 *	the program fails.
 *	Most routines return pointers to static data that may change
 *	between calls to the same or other routines with a few exceptions:
 *	"host_to_addr", "parse_hostnetwork", and "parse_hostnetworkmask"
 *	return global static data.
*/

static struct in_addr *
parse_hostnetwork(const char *name, unsigned int *naddrs)
{
	struct in_addr *addrp, *addrptmp;

	if ((addrptmp = dotted_to_addr(name)) != NULL ||
	    (addrptmp = network_to_addr(name)) != NULL) {
		addrp = fw_malloc(sizeof(struct in_addr));
		inaddrcpy(addrp, addrptmp);/*addrp->s_addr=addrptmp->s_addr*/
		*naddrs = 1;/*��������ָ����ip��ַ�Է�������ʽ��ʾʱ��
					��ôip��ַ����ֻ��1��*/
		return addrp;
	}
	if ((addrp = host_to_addr(name, naddrs)) != NULL)
		return addrp;

	fprintf(stderr, "host/network `%s' not found", name);
	exit(1);
}

/*����Ҫ�˽�һ���������и�����name�ĸ��ָ�ʽ:
   (1)192.168.1.221/0����Ϊ0��ֱ�ӽ�**addrpp��Ϊ0(����if(maskp->s_addr==0L) strcpy(buf,"0.0.0.0");)
   (2)192.168.1.221δָ����������������ָ��ĳһ�ض���ip��ַ
   (3)192.168.1.221/25���롢ip��ַ��ָ��
   (4)����������ʾ����yahoo.com.cn/25,��ʱ��parse_hostnetwork()->host_to_addr()->gethostbyname()
   ��Ϊͨ��ĳһ����������õ�ip��ַ�����ж�������ڸú�������������
   һ���µĲ���*naddrs�����Խ����õ��Ķ��ip��ַ���м���
   (5)??parse_hostnetwork()->network_to_addr()->getnetbyname()
*/
void
parse_hostnetworkmask(const char *name, struct in_addr **addrpp,
		      struct in_addr *maskp, unsigned int *naddrs)
{
	struct in_addr *addrp;
	char buf[256];
	char *p;
	int i, j, k, n;

	strncpy(buf, name, sizeof(buf) - 1);
	if ((p = strrchr(buf, '/')) != NULL) {
		*p = '\0';
		addrp = parse_mask(p + 1);
	} else
		addrp = parse_mask(NULL);/*δָ������*/
	inaddrcpy(maskp, addrp);/*maskp->s_addr = addrp->s_addr;*/

	/* if a null mask is given, the name is ignored, like in "any/0" */
	if (maskp->s_addr == 0L)/*����192.168.1.221/0��ʽ*/
		strcpy(buf, "0.0.0.0");

	addrp = *addrpp = parse_hostnetwork(buf, naddrs);
	n = *naddrs;
	for (i = 0, j = 0; i < n; i++) {
		addrp[j++].s_addr &= maskp->s_addr;/*��ַ����������*/
		for (k = 0; k < j - 1; k++) {
			if (addrp[k].s_addr == addrp[j - 1].s_addr) {
				(*naddrs)--;
				j--;
				break;
			}
		}
	}
}
/*
int
main(int argc,char *argv[])
{
	char	*hostnetworkmask=NULL;
	unsigned int nsaddrs = 0;
	struct in_addr *saddrs = NULL,mask;
	int	i;

	hostnetworkmask=argv[1];
	parse_hostnetworkmask(hostnetworkmask, &saddrs, &mask, &nsaddrs);
	for(i=0;i<nsaddrs;i++)
		printf("ip address%d=%s\n",i+1,inet_ntoa(*(saddrs++)));
	printf("mask=%s\n",inet_ntoa(mask));
}
*/
