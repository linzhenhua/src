/*
 * =====================================================================================
 *
 *       Filename:  pthread_join.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 10时06分19秒
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
#include <unistd.h>
#include <pthread.h>

void *thread()
{
    int i;

    for(i = 0; i < 3; i++)
    {
        sleep(1);
        printf("This in the thread: %d\n", i);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t pid;
    int i;
    int ret;

    ret = pthread_create(&pid, NULL, thread, NULL);
    if(ret != 0)
    {
        printf("create pthread error\n");
        return -1;
    }
    pthread_join(pid, NULL);
    printf("123\n");
    for(i = 0; i < 3; ++i)
    {
        printf("this in the main:%d\n", i);
    }

    return 0;
}
