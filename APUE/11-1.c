/*
 * =====================================================================================
 *
 *       Filename:  11-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月07日 22时31分31秒
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
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define UINT unsigned int

pthread_t ntid;

void printids(char const *str)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", str, (UINT)pid, (UINT)tid, (UINT)tid);
}

void *thr_fn(void *arg)
{
    printids("new  thread");

    puts("");

    printf("%u\n", ntid);

    return ((void *)0);
}

int main(int argc, char *argv[])
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0)
    {
        printf("can'n create thread: %d\n", err);
    }

    printids("main thread");
    sleep(1);

    return 0;
}
