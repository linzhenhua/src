/*
 * =====================================================================================
 *
 *       Filename:  exp_17.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月20日 08时42分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//判断任意一个正整数是否为素数(素数就是只能被他自身和1整除)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int num;  //待输入的正整数
    int flag = 1; //标志位,初始化为1，当一个数是素数时，flag == 0 
    int i;  //循环变量

    printf("请输入一个正整数\n");
    scanf("%d", &num);

    for(i = 2; flag != 0 && i <= sqrt(num); i++)
    {
        if(num % i == 0)
        {
            flag = 0;
        }
    }
    if(flag == 0)
    {
        printf("%d不是素数\n", num);
    }
    else
    {
        printf("%d是素数\n", num);
    }

    return 0;
}
