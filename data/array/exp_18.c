/*
 * =====================================================================================
 *
 *       Filename:  exp_18.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月20日 09时44分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//查找肇事车辆
//车牌号为前两位和后两位数相同，且四位车牌号刚好是一个整数的平方，求出车牌号
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int a; //前两位车牌号
    int b; //后两位车牌号
    int i; //循环变量

    for(a = 0; a < 9; a++)
        for(b = 0; b < 9; b++)
            for(i = 1; i*i < 9999; i++)
                if( i == sqrt(100*(10*a+a)+10*b+b) )
                {
                    printf("车牌号为%d\n", 1000*a+100*a+10*b+b);
                }

    return 0;
}
