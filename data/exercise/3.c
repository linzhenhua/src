/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月02日 21时26分29秒
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

#define LIMIT 8 //重量限制
#define N 5     //物品种类
#define MIN 1   //最小重量

typedef struct 
{
    char name[20];
    int size;
    int price;
}object;

int main(int argc, char *argv[])
{
    object arr[] = 
                  {
                      {"李子", 4, 4500},
                      {"苹果", 5, 5700},
                      {"橘子", 2, 2250},
                      {"草莓", 1, 1100},
                      {"甜瓜", 6, 6700}
                  };
    int i, j;
    int p;
    int newvalue;
    int value[LIMIT+1] = {0};  //存放当前最佳所得的总价
    int item[LIMIT+1] = {0};   //放到背包中的最后一个水果

    for(i = 0; i < N; i++)  //物品种类
    {
        for(j = arr[i].size; j <= LIMIT; j++)  // 重量限制
        {
            p = j - arr[i].size;
            newvalue = value[p] + arr[i].price;
            
            if(newvalue > value[j])
            {
                value[j] = newvalue;
                item[j] = i;
            }
        }
    }

    printf("物品\t价格\n");
    for(i = LIMIT; i >= MIN; i -= arr[item[i]].size)
    {
        printf("%s\t%d\n", arr[item[i]].name, arr[item[i]].price);
    }
    printf("合计\t%d\n", value[LIMIT]);

    return 0;
}
