/*
 * =====================================================================================
 *
 *       Filename:  exchange.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 20时19分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
//用贪婪算法求找零钱
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int change(int money);

int denomination[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10};
int num[MAX] = {0};

int main(int argc, char *argv[])
{
    float money;
    int i;

    printf("请输入找零的金额\n");
    scanf("%f", &money);

    change((int)(100*money));

    printf("%f元的零钱组成为:\n", money);
    for(i = 0; i < MAX; i++)
    {
        if(num[i] > 0)
        {
            printf("%6.2f: %d张\n", (float)denomination[i]/100.0, num[i]);
        }
    }

    return 0;
}

int change(int money)
{
    int i;

    for(i = 0; i < MAX; i++)
    {
        if(money > denomination[i])  //找到比money小的最大元素
        {
            break;
        }
    }

    while(i < MAX && money > 0)
    {
        if(money >= denomination[i])
        {
            money -= denomination[i];
            num[i]++;
        }
        else if(money >= 5 && money < 10)
        {
            num[MAX-1]++;
            break;
        }
        else
        {
            i++;
        }
    }

    return 0;
}
