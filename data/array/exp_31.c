/*
 * =====================================================================================
 *
 *       Filename:  exp_31.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 09时01分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//     1
//    121
//   12321
//  1234321
// 123454321
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i ,j, k;
    int n;

    for(i = 1; i <= 5; i++)
    {
        n = i;
        for(k = 1; k <= 10 - i; k++)   //打印空格
        {
            printf(" ");
        }
        for(j = 1; j <= 2*i-1; j++)
        {
            if(j <= n)
            {
                printf("%d", j);
            }
            if(j > n)
            {
                printf("%d", --n);
            }
        }
        printf("\n");
    }

    return 0;
}
