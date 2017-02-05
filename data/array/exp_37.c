/*
 * =====================================================================================
 *
 *       Filename:  exp_37.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月26日 09时12分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//简单投票系统
//利用程序来选举班上的班长。全班有50人，
//全班每个同学都可通过在讲台上的一台电脑的键盘上输入一个学号来投班上某同学一票。
//关键：定义数组int num[50],用数组元素的下标分别表示每位同学的学号，用数组元数的值表示该同学的得票数。
//比如假设：数组元素 num[6]的最终值是18，那就表示6号同学得了18票
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int num;
    int arr[11];

    memset(arr, 0, sizeof(arr));   //将数组的元素初始化为0；
    printf("请输入要投票的人的号码:\n");
    while(i < 10)
    {
        scanf("%d", &num);
        if(num > 0 && num <= 10)
        {
            ++arr[num];
        }
        else
        {
            printf("输入的学号有误，请重新输入\n");
            continue;
        }
        i++;
    }

    printf("得票数为:\n");
    for(i = 1; i <=10; i++)
    {
        printf("第%d个学生得票数为%d\n", i, arr[i]);
    }

    return 0;
}
