/*
 * =====================================================================================
 *
 *       Filename:  exp_12.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月14日 22时32分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *===============================================================================
 *利用蒙特卡罗算法求解(未完成)
 *设f（x）=x^2是[0，1]上的连续函数，且0≤f（x）≤1，需要计算积分值I=∫f（x）dx，
 *并计算积分I的面积G。利用随机投点法来做此题。
 *================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int i, n;
    double s, x, y;
    i = 1;

    srand( (unsigned)time(NULL) );

    while(i <= 10000)
    {   
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        if( (y-x*x) < 0 )
        {
            n++;
        }
        i++;
    }
    s = 1.0*n/10000;

    printf("%lf\n", s);

    return 0;

}
