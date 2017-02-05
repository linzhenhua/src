/*
 * =====================================================================================
 *
 *       Filename:  7-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月20日 19时56分31秒
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

static void my_exit1(void)
{
    printf("first exit handler\n");
}

static void my_exit2(void)
{
    printf("second exit handler\n");
}

int main(int argc, char *argv[])
{
    if(atexit(my_exit2) != 0)
        printf("can't register my_exit2");
    if(atexit(my_exit1) != 0)
        printf("can't register my_exit1");
    if(atexit(my_exit1) != 0)
        printf("can't register my_exit1");

    printf("main is done\n");

    return 0;
}
