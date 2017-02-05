/*
 * =====================================================================================
 *
 *       Filename:  3-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月28日 09时32分12秒
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

int main(int argc, char **argv)
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        printf("cannot seek\n");
    }
    else
    {
        printf("seek ok\n");
    }

    return 0;
}
