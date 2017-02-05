/*
 * =====================================================================================
 *
 *       Filename:  exp_21.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月21日 10时16分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求x-x^3/3!+x^5/5!-x^7/&!+....，直到所求项的绝对值小于10^-6次方，不可以用pow()来算
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    float sum; //和
    float numerator;   //分子
    float denominator;  //分母
    float tmp, tmp1, tmp2; //临时替代
    int coefficient;  //系数
    int i;  //跑龙套专用循环变量
    
    sum = 0;  //要初始化为1
    tmp2 = 1;  //
    denominator = 1; //要初始化为1
    coefficient = 1; //

    printf("请输入一个数:\n");
    scanf("%f", &numerator);

    while( fabs(tmp2) > 0.000001 )   //判断所求项绝对值是否小于10^6次方
    {
        tmp = 1;
        for(i = 1; i <= denominator; i++)   //求分母
        {
            tmp *= i;
        }
        tmp1 = 1;
        for(i = 1; i <= denominator; i++)   //求分子
        {
            tmp1 *= numerator;
        }
        tmp2 = coefficient * tmp1 / tmp;
        sum = sum + tmp2;   //总和
        denominator += 2;
        coefficient = -coefficient;
    }
    printf("%f\n", sum);

    return 0;
}
