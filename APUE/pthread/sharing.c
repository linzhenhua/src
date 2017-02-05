/*
 * =====================================================================================
 *
 *       Filename:  sharing.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 16时17分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define N 2

void *thread(void *vargp);

char **ptr;

int main(int argc, char **argv)
{
    int i;
    pthread_t pid;
    char *msgs[] = {"hello from foo","hello from bar"};

    ptr = msgs;

    for(i = 0; i < N; i++)
    {
        pthread_create(&pid, NULL, thread, (void *)i);
        sleep(2);
    }
    
    pthread_exit(NULL);

    return 0;
}
void *thread(void *vargp)
{
    int myid = (int )vargp;
    static int cnt = 0;
    //sleep(2);
    printf("[%d]:%s (cnt=%d)\n", myid, ptr[myid], ++cnt);

    return NULL;
}
