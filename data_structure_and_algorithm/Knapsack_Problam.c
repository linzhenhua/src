/*
 * =====================================================================================
 *
 *       Filename:  Knapsack_Problam.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月02日 10时20分42秒
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

#define LIMIT 8  //重量限制
#define N 5      //物品种类
#define MIN 1    //最小重量

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

    int value[LIMIT+1] = {0};  //存放最佳所得到的总价，+1是因为数组的0不用
    int item[LIMIT+1] = {0};  //存放最后一个放置背包的水果
    int newvalue; //新的价值
    int s;  //
    int i, j; //

    for(i = 0; i < N; i++)  //物品种类
    {
        for(j = arr[i].size; j <= LIMIT; j++)  //重量限制
        {
            s = j - arr[i].size;
            newvalue = value[s] + arr[i].price;
            
            if(newvalue > value[j])   //找到阶段最佳解
            {
                value[j] = newvalue;
                item[j] = i;
            }
        }
    }

    printf("物品\t价格\n");
    for(i = LIMIT; i >= MIN; i = i - arr[item[i]].size)
    {
        printf("%s\t%d\n", arr[item[i]].name, arr[item[i]].price);
    }

    printf("合计\t%d\n", value[LIMIT]);

    return 0;
}
