/*
 * =====================================================================================
 *
 *       Filename:  exp_29.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 08时14分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//1
//13
//135
//1357
//133579
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;

    for(i = 1; i <= 9; i += 2)
    {
        for(j = 1; j <= i; j += 2)
        {
            printf("%d ", j);
        }
        printf("\n");
    }
    return 0;
}
