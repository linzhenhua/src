/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 08时43分04秒
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

int main(int argc, char **argv)
{
    pid_t id;

    id = fork();
    if(id < 0)
    {
        fprintf(stdout, "fork error\n");
        exit(-1);
    }

    if(id == 0)
        fprintf(stdout, "child process ,ID is %d\n", getpid());
    else
        fprintf(stdout, "parent process ,ID is %d\n", getpid());

    return 0;
}
