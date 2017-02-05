/*
 * =====================================================================================
 *
 *       Filename:  exp_41.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月28日 15时07分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求100以内所有正整数的质因子(既是素数又是因数)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int i, j;
    int n;
    int k = 1;
    int prime[30];  //素数
    int flag = 1;   //判断素数标记位

    memset(prime, 0, sizeof(prime));   //将数组元素赋值0

    for(i = 2; i <= 100; i++)
    {
        for(j = 2; flag != 0 && j <= sqrt(i); j++)
        {
            if(i % j == 0)
            {
                flag = 0;
            }
        }

        if(flag == 1)
        {
            prime[k] = i;
            k++;
        }
        flag = 1;  //记得重置flag == 1，很重要
    }
    n = 1;
    while(n <= 100)
    {
        printf("%d=", n);
        i = 1;
        k = n;
        while(k != 1)
        {
            while( (k%prime[i]) ==0 && (k != 1))
            {
                printf("%d*", prime[i]);
                k = k/prime[i];
            }
            i++;
        }
        printf("\n");
        n++;
    }


    return 0;
}
