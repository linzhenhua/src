/*
 * =====================================================================================
 *
 *       Filename:  exp_35.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月26日 08时09分42秒
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

int main(int argc, char *argv[])
{
    int i, a[10];

    for(i = 0; i < 10; i++)
    {
        a[i] = 9-i;
        printf("a[%d]=%d %p\n", i, a[i], &a[i]);
    }

    return 0;
}
