/*
 * =====================================================================================
 *
 *       Filename:  exp_16.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月20日 08时29分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//不用%和/求出两个数的商和余数
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, m , n;

    printf("请输入被除数和除数\n");
    scanf("%d %d", &m, &n);

    if(m < n)
    {
        printf("商为%d,余数为%d\n", 0, m);
        exit(0);
    }
    i = 0;
    while(m >= n)
    {
        m = m - n;
        i++;
    }
    printf("商为%d,余数为%d\n", i, m);

    return 0;
}
