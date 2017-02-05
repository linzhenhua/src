/*
 * =====================================================================================
 *
 *       Filename:  recursion1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月05日 09时42分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//用递归方法计算n的阶乘 n == 10
#include <stdio.h>
#include <stdlib.h>

int a = 0;

int recursion(int n);

int recursion(int n)
{
    a++;
    if(n <= 0)
        return 1;
    else
        return n*recursion(n-1);
}

int main(int argc, char **argv)
{
    int n = 10;
    int sum;

    sum = recursion(n);

    printf("sum=%d\ta=%d\n", sum, a);

    return 0;
}
