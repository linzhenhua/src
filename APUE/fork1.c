/*
 * =====================================================================================
 *
 *       Filename:  fork1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 09时09分37秒
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
    int count = 0;
    pid_t id;

    id = fork();

    count++;
    fprintf(stdout, "count = %d\n", count);

    return 0;
}
