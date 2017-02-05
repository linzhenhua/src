/*
 * =====================================================================================
 *
 *       Filename:  getpid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 22时00分25秒
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

int main(int argc, char *argv[])
{
    pid_t pid;
    
    pid = getpid();

    printf("%d\n", pid);

    return 0;
}
