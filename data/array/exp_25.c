/*
 * =====================================================================================
 *
 *       Filename:  exp_25.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 10时45分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//11111
//22222
//33333
//44444
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;

    for(i = 1; i <= 5; i++)
    {
        for(j = 0; j < 5; j++)
            printf("%d", i);
        printf("\n");
    }

    return 0;
}
