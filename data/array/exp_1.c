/*
 * =====================================================================================
 *
 *       Filename:  exp_1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 02时51分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求整数1到100的和。
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    int sum = 0;

    for(i = 1; i <= 100; i++)
    {
        sum += i;
    }

    printf("%d\n", sum);

    return 0;
}





