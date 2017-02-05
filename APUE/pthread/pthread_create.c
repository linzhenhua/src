/*
 * =====================================================================================
 *
 *       Filename:  pthread_create.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 07时54分10秒
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

void *myThread1(void);
void *myThtead2(void);

void *myThread1(void)
{
    int i;
    
    for(i = 0; i < 3; i++)
    {
        printf("This is the 1st pthread!\n");
        sleep(1);
    }
}

void *myThread2(void)
{
    int i;

    for(i = 0; i < 3; i++)
    {
        printf("This is the 2st pthread!\n");
        sleep(1);
    }
}

int main(int argc, char **argv)
{
    pthread_t pid1, pid2;
    int ret1, ret2;

    ret1 = pthread_create(&pid1, NULL, (void *)myThread1, NULL);
    if(ret1 != 0)
    {
        printf("create pthread error\n");
        return -1;
    }

    ret2 = pthread_create(&pid2, NULL, (void *)myThread2, NULL);
    if(ret2 != 0)
    {
        printf("create pthread error\n");
        return -1;
    }

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    return 0;
}
