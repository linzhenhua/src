/*
 * =====================================================================================
 *
 *       Filename:  7.1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月05日 10时36分13秒
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

int hermite(int n, int x);

int hermite(int n, int x)
{
    if(n <= 0)
        return 1;
    if(n == 1)
        return 2*x;
    if(n >= 2)
        return (2*x*hermite(n-1, x) - 2*(n-1)*hermite(n-2, x));
}

int main(int argc, char **argv)
{
    int result;
    int n;
    int x;

    printf("please input n and x(n,x)\n");
    scanf("%d,%d", &n, &x);

    result = hermite(n, x);

    printf("result=%d\n", result);

    return 0;
}
