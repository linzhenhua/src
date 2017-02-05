/*
 * =====================================================================================
 *
 *       Filename:  exp_14.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月16日 08时16分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//输入任意个数，求出最大值，最小值以及平均值
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    float sum, ave, max, min, num;
    int count = 0;
    sum = 0;

    printf("请输入任意个数，按0结束：\n");
    scanf("%f", &num);
    max = min = num;
    while( num != 0 )
    {
        sum += num; 
        if(max <= num)
        {
            max = num;
        }
        if(min >= num)
        {
            min = num;
        }
        ++count;
        scanf("%f", &num);
    }
    ave = sum/count;

    printf("一共输入了%d个数\n最大值为%f\n最小值为%f\n",count, max, min);
    printf("平均值为%.2f\n", ave);

    return 0;
}
