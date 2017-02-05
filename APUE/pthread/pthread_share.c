/*
 * =====================================================================================
 *
 *       Filename:  pthread_share.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 08时52分52秒
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
#include <unistd.h>
#include <pthread.h>

//int a = 1;

void *create(void *arg)
{
    int *x;
    x = (int *)arg;
    ++(*x);
    printf("new pthread...\n");
    printf("a = %d\n", *x);
    
    return (void *)0;
}

int main(int argc, char **argv)
{
    pthread_t pid;
    int ret;

    int a = 5;

    printf("in main 1 a = %d\n", a);

    ret = pthread_create(&pid, NULL, create, (void *)&a);
    if(ret != 0)
    {
        printf("create pthread error\n");
        return -1;
    }
    sleep(1);
    printf("in main 2 a = %d\n", a);
    printf("new thread is create....\n");

    return 0;
}
