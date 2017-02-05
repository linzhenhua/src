/*
 * =====================================================================================
 *
 *       Filename:  exp_19.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月20日 10时00分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求1+22+333+4444+55555+.....共9个数之和
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n, m , i, sum;
    
    sum = 0;
    m = 1;
    i = 1;
    n = 1;
    while(i<=9)
    {
        sum += n;
        m = m*10+1;
        i++;
        n = m*i;
    }
    printf("%d\n", sum);

    return 0;
}
