/*
 * =====================================================================================
 *
 *       Filename:  process.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月17日 17时20分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <pthread.h>

int main(int argc, char **argv)
{
    printf("hello world from process ID %d\n", getpid());

    return 0;
}
