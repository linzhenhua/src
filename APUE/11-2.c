/*
 * =====================================================================================
 *
 *       Filename:  11-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月08日 22时03分59秒
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
#include <pthread.h>
#include <time.h>

void *thr_fn1(void *arg)
{
    printf("thread 1 returnintg\n");

    return (void *)1;
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");

    pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
    int       err;
    pthread_t tid1, tid2;
    void      *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if( err != 0)
    {
        printf("can't create thread 1\n");
    }
    sleep(1);

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if( err != 0)
    {
        printf("can't create thread 2\n");
    }
    //sleep(1);

    err = pthread_join(tid1, &tret);
    if( err != 0)
    {
        printf("can't join with thread 1\n");
    }
    printf("thread 1 exit code %d\n", (int)tret);
    
    err = pthread_join(tid2, &tret);
    if( err != 0)
    {
        printf("thread 2 exit code %d\n", (int)tret);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
