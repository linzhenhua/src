/*
 * =====================================================================================
 *
 *       Filename:  8-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月24日 21时45分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    if( (pid = fork()) < 0 )
    {
        printf("fork error\n");
    }
    else 
        if(pid == 0)
        {
            exit(7);
        }
    if( wait(&status) != pid )
    {
        printf("wait error\n");
    }
    printf("%d\n", status);

    if( (pid = fork()) < 0 )
    {
        printf("fork error\n");
    }
    else 
        if( pid == 0)
        {
            abort();
        }

    if( wait(&status) != pid )
    {
        printf("fork error\n");
    }
    printf("%d\n", status);

    if( (pid = fork()) < 0 )
    {
        printf("fork error\n");
    }
    else 
        if(pid == 0)
            status /= 0;

    if( wait(&status) != pid )
    {
        printf("wait error\n");
    }
    printf("%d\n", status);

    exit(0);
}
