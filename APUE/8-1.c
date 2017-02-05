/*
 * =====================================================================================
 *
 *       Filename:  8-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 20时02分47秒
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

char buf[] = "a write to stdout\n";
int glob = 6;

int main(int argc, char *argv[])
{
    int var;
    pid_t pid;

    var = 88;

    if( write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1 )
    {
        printf("wrinte error\n");
        exit(-1);
    }
    printf("before fork\n");

    if( ( pid = fork() ) < 0 )
    {
        printf("fork error\n");
    }
    else
        if(pid == 0)
        {
            glob++;
            var++;
        }
        else
        {
            sleep(2);
        }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

    return 0;
}
