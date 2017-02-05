/*
 * =====================================================================================
 *
 *       Filename:  8-9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月25日 21时53分24秒
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
    int i;
    char **ptr;
    extern char **environ;

    for(i = 0; i < argc; i++)
    {
        printf("argv[%d]:%s\n", i, argv[i]);
    }
    for(ptr = environ; *ptr != 0; ptr++)
    {
        printf("%s\n", *ptr);
    }

    return 0;
}
