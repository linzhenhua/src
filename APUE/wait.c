/*
 * =====================================================================================
 *
 *       Filename:  wait.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 10时15分14秒
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
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t pc, pr;

    pc = fork();
    if( pc < 0 )
    {
        fprintf(stdout, "fork error\n");
        exit(-1);
    }

    if(0 == pc)
    {
        fprintf(stdout, "this is child process with pid of %d\n", getpid());
        sleep(5);
    }
    else if(pc > 0)
    {
        pr = wait(NULL);
        fprintf(stdout, "i catched a child process with pid of %d\n", pr);
    }

    return 0;
}

