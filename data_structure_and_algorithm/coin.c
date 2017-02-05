/*
 * =====================================================================================
 *
 *       Filename:  coin.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月29日 21时23分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
/*
现有八枚银币a b c d e f g h，已知其中一枚是假币，
其重量不同于真币，但不知是较轻或较重，
如何使用天平以最少的比较次数，决定出哪枚是假币，
并得知假币比真币较轻或较重。 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int coin[8] = {10, 10, 10, 10, 10, 10, 8, 10};
    char ch[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int i;
    //int temp;

    if(coin[0] == coin[1])
    {
        for(i = 2; i < 8; ++i)
        {
            if(coin[0] != coin[i])
            {
                if(coin[i] > coin[0])
                {
                    printf("假银币为%c, 比较重\n", ch[i]);
                }
                else
                {
                    printf("假银币为%c, 比较轻\n", ch[i]);
                }
            }
        }/*for(i = 2; i < 8; ++i)*/
    }
    else if(coin[0] == coin[2])
    {
        if(coin[1] > coin[0])
        {
            printf("假银币为%c, 比较重\n", ch[1]);
        }
        else
        {
            printf("假银币为%c, 比较轻\n", ch[1]);
        }
    }
    else
    {
        if(coin[0] > coin[2])
        {
            printf("假银币为%c, 比较重\n", ch[0]);
        }
        else
        {
            printf("假银币为%c, 比较轻\n", ch[0]);
        }
    }

    return 0;
}
