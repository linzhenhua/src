/*
 * =====================================================================================
 *
 *       Filename:  8-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 08时29分28秒
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
    pid_t pid, ppid;

    pid = getpid();   //进程ID
    ppid = getppid();  //父进程ID

    fprintf(stdout, "进程ID: %d\n", pid);
    fprintf(stdout, "父进程ID: %d\n", ppid);

    return 0;
}
