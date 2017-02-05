/*
 * =====================================================================================
 *
 *       Filename:  pipe.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 15时20分46秒
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
    int pipe_fd[2];

    if(pipe(pipe_fd) < 0)
    {
        fprintf(stdout, "create pipe error\n");
        return -1;
    }
    else
    {
        fprintf(stdout, "create pipe success\n");
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
