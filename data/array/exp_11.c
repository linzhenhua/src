/*
 * =====================================================================================
 *
 *       Filename:  exp_11.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月14日 03时41分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//蒙特卡罗法求pi的值
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(int argc, char **argv)
{
    int n = 0;
    int s = 0;
    double x,y,pi;

    srand( (unsigned)time(NULL) );
    while(s <= 10000)
    {
        x = rand()%1;
        y = rand()%1;
        if( (x*x+y*y) < 1 )
        {
            n++;
        }
        s++;
    }

    pi = (4.0*n)/10000;

    printf("圆周率约等于%lf\n", pi);

    return 0;
}
