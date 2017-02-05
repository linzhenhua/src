/*
 * =====================================================================================
 *
 *       Filename:  pthread_int.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 08时24分04秒
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

void *create(void *arg)
{
    int *num;

    num = (int *)arg;

    printf("create parameter is %d\n", *num);

    return (void *)0;
}

int main(int argc, char **argv)
{
    pthread_t pid;
    int ret;
    int num = 4;
    //int *attr = &num;

    ret = pthread_create(&pid, NULL, create, (void *)&num);
    if(ret != 0)
    {
        printf("create pthread error!\n");
        return -1;
    }
    sleep(1);
    printf("pthread_create is create....\n");

    return 0;
}
