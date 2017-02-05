/* Our own header for the programs that need interface configuration info.
   Include this file, instead of "unp.h". */

#ifndef	__unp_ifi_h
#define	__unp_ifi_h

#include	<netinet/in.h>
#include	<stdio.h>
#include	<net/if.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include <errno.h>
#include	<sys/ioctl.h>
#include	<net/if.h>
#include <features.h>    /* for the glibc version number */
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>     /* the L2 protocols */
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>   /* The L2 protocols */
#endif

#define	IFI_NAME	16			/* same as IFNAMSIZ in <net/if.h> */
#define	IFI_HADDR	 8			/* allow for 64-bit EUI-64 in future */

struct ifi_info {
  char    ifi_name[IFI_NAME];	/* interface name, null terminated */
  short    ifi_index;            /* interface index *//*��ʱ��û���ҵ���صĵ��ú���*/
  short    ifi_mtu;              /* interface MTU */
  unsigned short  ifi_hatype;    /* Header type *//*��ʱ��û���ҵ���صĵ��ú���*/
  u_char  ifi_haddr[IFI_HADDR];	/* hardware address */
  u_short ifi_hlen;				/* #bytes in hardware address: 0, 6, 8 *//*��ʱ��û���ҵ���صĵ��ú������Ȱ�����̫������Ϊ6*/
  short   ifi_flags;			/* IFF_xxx constants from <net/if.h> */
  short   ifi_myflags;			/* our own IFI_xxx flags */
  struct sockaddr  *ifi_addr;	/* primary address */
  struct sockaddr  *ifi_brdaddr;/* broadcast address */
  struct sockaddr  *ifi_dstaddr;/* destination address */
  struct sockaddr	*ifi_netmask;/*netmask address*/
  struct ifi_info  *ifi_next;	/* next of these structures */
};

#define	IFI_ALIAS	1			/* ifi_addr is an alias */

					/* function prototypes */
struct ifi_info	*get_ifi_info(int, int);
struct ifi_info	*Get_ifi_info(int, int);
void			 free_ifi_info(struct ifi_info *);

#endif	/* __unp_ifi_h */
