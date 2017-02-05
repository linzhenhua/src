/*
 * =====================================================================================
 *
 *       Filename:  exp_13.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月15日 00时06分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//随机生成10个0到1的整数。。。
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int i;

    srand( (unsigned)time(NULL) );

    for(i = 0; i < 10; i++)
    {
        printf("%lf\n", (double)rand()/RAND_MAX);
    }

    return 0;
}
