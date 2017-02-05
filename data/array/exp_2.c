/*
 * =====================================================================================
 *
 *       Filename:  exp_2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 02时58分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *求1到n的和，n为自然数，n有程序员输入
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;  //循环变量
    int sum = 0;//求和
    int n; //范围

    printf("请输入范围n的值：\n");
    scanf("%d", &n);
    while(i <= n)
    {
        sum +=i;
        i++;
    }

    printf("1到%d的和为%d\n",n, sum);

    return 0;
}







