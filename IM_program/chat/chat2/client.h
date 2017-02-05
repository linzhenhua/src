/***********************************
 * client.h                        *
 * the header files and functions  *
 ***********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888
#define MAXSIZE 1024

int build_socket(const char *);
void send_text(void);
void send_func(const char *);
void *recv_func(void *);
void show_remote_text(char rcvd_mess[]);
void clean_send_text(void);
void show_err(char *err);
