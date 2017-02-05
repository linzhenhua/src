/*
 * =====================================================================================
 *
 *       Filename:  exp_20.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月21日 08时42分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求n+nn+nnn+nnnn....共10项之和，n<=9,n由用户输入
//warning:一定要注意num,sum的范围,防止溢出,用long long 保准没事
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long long num, sum;
    int i, tmp;
    sum = 0;
    printf("请输入一个数,num<=9:\n");
    scanf("%lld", &num);
    tmp = num;
    for(i = 0; i < 10; i++)
    {
        sum = sum + num;
        num = num * 10 + tmp;
    }
    printf("%lld\n", sum );

    return 0;
}
