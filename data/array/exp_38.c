/*
 * =====================================================================================
 *
 *       Filename:  exp_38.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月26日 10时21分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//扔色子:
//一个骰子或称色(shai)子,是一个正方体，
//共有六个面，每个面上分别标有1、2、3、4、5、6这6个数字。
//在大富翁、麻将、飞行棋等电脑游戏中都会出现它的身影。
//本题用计算机模拟掷骰子游戏，
//并统计1000次掷骰子中分别出现数字1、2、3、4、5、6的次数。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int arr[7];
    int i;
    int x;

    memset(arr, 0, sizeof(arr));
    srand((unsigned)time(NULL));   //利用系统时钟产生随机种子
    for(i = 0; i < 1000; i++)
    {
        x = rand()%6+1;
        ++arr[x];
    }

    for(i = 1; i <= 6; i++)
    {
        printf("%d出现的次数为%d\n", i, arr[i]);
    }

    return 0;
}
