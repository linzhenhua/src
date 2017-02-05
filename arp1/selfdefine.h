#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include  "unistd.h"
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <pthread.h>
#include <pwd.h>
#include <arpa/inet.h>
#include <ftw.h>
#include <limits.h>
#include <errno.h>
#include <netinet/tcp.h>
#include	<pcap.h>
#include	<netinet/if_ether.h>
#include	<netinet/ip.h>
#include	<signal.h>

#define IN_ADDR_BROADCAST  0xffffffff
#define IN_ADDR_ANY	   0x00000000 
#define SA		struct sockaddr *
