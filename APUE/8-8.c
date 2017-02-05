/*
 * =====================================================================================
 *
 *       Filename:  8-8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月25日 21时22分06秒
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
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = {"USER=unknow", "PATH=/tmp", NULL};

int main(int argc, char *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        if( execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0 )
        {
            printf("execle error\n");
            exit(-1);
        }
    }

    if(waitpid(pid, NULL, 0) < 0)
    {
        printf("wait error\n");
        exit(-1);
    }

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        if( execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0 )
        {
            printf("execlp error\n");
            exit(-1);
        }
    }

    return 0;
}
