/*
 * =====================================================================================
 *
 *       Filename:  change.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月05日 20时50分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10

int money[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10};  //面值大小
int num[MAXN] = {0};  //记录有多少张指定币值组成

int exchange(int n);

int exchange(int n)
{
    int i;

    for(i = 0; i < MAXN; i++)
    {
        if(n > money[i])  //找到比n小的最大面值
            break;
    }

    while(n > 0 && i < MAXN)
    {
        if(n > money[i])  //看有多少这样的面值
        {
            n -= money[i];
            num[i]++;  //在相应的面值的位置+1
        }
        else if(n < 10 && n >= 5)  //0.1元到0.05元之间要四舍五入
        {
            num[MAXN-1]++;
            break;
        }
        else
        {
            i++;  //向小面值移动
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    float m;
    int i;

    printf("请输入找零的金额:");
    scanf("%f", &m);

    exchange((int)(m*100));

    printf("%.2f元零钱的组成\n", m);
    for(i = 0; i < MAXN; i++)
    {
        if(num[i] > 0)
        {
            printf("%6.2f: %d张\n", money[i]/100.0, num[i]);
        }
    }

    return 0;
}
