/*
 * =====================================================================================
 *
 *       Filename:  3-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月28日 10时01分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(int argc, char **argv)
{
    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buf, n) != n)
        {
            printf("write error\n");
            return -1;
        }
    }

    if(n < 0)
    {
        printf("read error\n");
        return -1;
    }

    return 0;
}
