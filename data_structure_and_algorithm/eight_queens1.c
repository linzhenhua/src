/*
 * =====================================================================================
 *
 *       Filename:  eight_queens.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月10日 09时16分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
 //在8X8格的国际象棋上摆放八个皇后，使其不能互相攻击，即任意两个皇后都不能处于同一行、
 //同一列或同一斜线上，问有多少种摆法。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BOOL int

int count = 0;

void eightQueen(int row, int column, int (*chess)[8] ); //row:从第几行开始,column:有多少列
BOOL check(int row, int k, int (*chess)[8] );   //检查是否有皇后
void print(int (*chess)[8]); //打印棋盘

void print(int (*chess)[8])
{
    int i, j;
    FILE *fp;

    fp = fopen("eigth_queens1.txt","a");
    if(NULL == fp)
    {
        printf("open file error\n");
        exit(-1);
    }

    fprintf(fp, "第%d种方法\n", count+1);
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            fprintf(fp, "%d  ", chess[i][j]);
        }
        fprintf(fp , "\n");
    }
    fprintf(fp, "\n");
    count++;
}
BOOL check(int row, int k, int (*chess)[8] )
{
    int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
    int i, j;

    for(i = 0; i < 8; i++)  //判断列方向是否有皇后
    {
        if( *(*(chess+i)+k) != 0 )
        {
            flag1 = 1;
            break;
        }
    }

    for(i = row, j = k; i >= 0 && j >= 0; i--, j--)  //左上角
    {
        if( *(*(chess+i)+j) != 0)
        {
            flag2 = 1;
            break;
        }
    }

    for(i = row, j = k; i >= 0 && j < 8; i--, j++)  //右上角
    {
        if(*(*(chess+i)+j) != 0)
        {
            flag3 = 1;
            break;
        }
    }

    for(i = row, j = k; i < 8 && j >= 0; i++, j--)  // 左下角
    {
        if(*(*(chess+i)+j) != 0)
        {
            flag4 = 1;
            break;
        }
    }
    
    for(i = row, j = k; i < 8 && j < 8; i++, j++)
    {
        if(*(*(chess+i)+j) != 0)
        {
            flag5 = 1;
            break;
        }
    }

    if(flag1 || flag2 || flag3 || flag4 || flag5)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}
void eightQueen(int row, int column, int (*chess)[8] ) //row:从第几行开始,column:有多少列
{
    int i, j, k;
    int queen[8][8];

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            *(*(queen+i)+j) = *(*(chess+i)+j);
        }
    }

    if(8 == row)
    {
        print(queen);
    }
    else
    {
        for(k = 0; k < column; k++)
        {
            if(check(row, k, chess))
            {
                for(i = 0; i < 8; i++)
                {
                    *(*(queen+row)+i) = 0;
                }
                *(*(queen+row)+k) = 1;
                eightQueen(row+1, column, queen);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j;
    int chess[8][8];

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            chess[i][j] = 0;
        }
    }

    eightQueen(0, 8, chess);
    printf("一共用%d种解决方案\n", count);

    return 0;
}
