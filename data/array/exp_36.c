/*
 * =====================================================================================
 *
 *       Filename:  exp_36.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月26日 08时53分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//请编程定义一个数组并直接将其初始化为：
//int  num[10]={2，4，6，8，10，12，14，16，18，20};
//求出该数组中所有下标为奇数的数组元素之和sum
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argvp[])
{
    int i, sum = 0;
    int num[10] = {2,4,6,8,10,12,14,16,18,20};

    for(i = 1; i < 10; i +=2)
    {
        sum += num[i];
    }
    printf("sum=%d\n", sum);

    return 0;
}
