/*
 * =====================================================================================
 *
 *       Filename:  6-10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月05日 19时43分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    time_t *t;

    t = (time_t *)malloc(sizeof(time_t)*10);

    time(t);

    printf("time is: %ld\n",*t);

    return 0;
}
