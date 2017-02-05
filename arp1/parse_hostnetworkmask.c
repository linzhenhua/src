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

/*将输入的数字字符串转换成数字赋值给*ret，并且保证数值的
   范围在min与max之间，成功返回0否则返回-1*/
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

/*将255.255.254.0形式的掩码转换成数值形式，失败返回空值*/
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

/*命令行中指定的ip地址以域名形式表示*/
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
			(*naddr)++;/*解析得到多个ip地址*/
		addr = fw_calloc(*naddr, sizeof(struct in_addr));
		for (i = 0; i < *naddr; i++)
			inaddrcpy(&(addr[i]),
				  (struct in_addr *) host->h_addr_list[i]);
		return addr;
	}

	return (struct in_addr *) NULL;
}

/*指定某一掩码将其转换成数值，失败返回空值
*/
static struct in_addr *
parse_mask(char *mask)
{
	static struct in_addr maskaddr;
	struct in_addr *addrp;
	unsigned int bits;

	if (mask == NULL) {/*未指定掩码说明指定某一特定邋IP地址，所以这里设定为全1*/
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
		*naddrs = 1;/*命令行中指定的ip地址以非域名形式表示时，
					那么ip地址个数只有1个*/
		return addrp;
	}
	if ((addrp = host_to_addr(name, naddrs)) != NULL)
		return addrp;

	fprintf(stderr, "host/network `%s' not found", name);
	exit(1);
}

/*首先要了解一下命令行中给定的name的各种格式:
   (1)192.168.1.221/0掩码为0则直接将**addrpp赋为0(后面if(maskp->s_addr==0L) strcpy(buf,"0.0.0.0");)
   (2)192.168.1.221未指定掩码则命令行中指定某一特定的ip地址
   (3)192.168.1.221/25掩码、ip地址都指定
   (4)用域名来表示例如yahoo.com.cn/25,这时在parse_hostnetwork()->host_to_addr()->gethostbyname()
   因为通过某一域名解析获得的ip地址可能有多个所以在该函数中又引入了
   一个新的参数*naddrs用来对解析得到的多个ip地址进行计数
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
		addrp = parse_mask(NULL);/*未指定掩码*/
	inaddrcpy(maskp, addrp);/*maskp->s_addr = addrp->s_addr;*/

	/* if a null mask is given, the name is ignored, like in "any/0" */
	if (maskp->s_addr == 0L)/*例如192.168.1.221/0格式*/
		strcpy(buf, "0.0.0.0");

	addrp = *addrpp = parse_hostnetwork(buf, naddrs);
	n = *naddrs;
	for (i = 0, j = 0; i < n; i++) {
		addrp[j++].s_addr &= maskp->s_addr;/*地址与掩码相与*/
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
