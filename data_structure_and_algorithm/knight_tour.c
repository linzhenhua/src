/*
 * =====================================================================================
 *
 *       Filename:  knight_tour.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月24日 15时16分43秒
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

int board[8][8] = { {0} };  /*定义棋盘为全局变量，初始化为0*/

int travel(int x, int y);  /*声明travel函数*/

int main(int argc, char *argv[])
{
    int startX, startY; //开始位置
    int i, j;

    printf("请输入开始位置:\n");
    scanf("%d,%d", &startX, &startY);
    printf("由(%d,%d)位置开始周游..\n", startX, startY);

    if(travel(startX, startY))
    {
        printf("周游成功\n");
    }
    else
    {
        printf("周游失败\n");
    }
    /*打印棋盘*/
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}/*main() end*/

int travel(int x, int y)
{
    int i, j;

    /*对应骑士可走的八个方向*/
    int kmove1[] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int kmove2[] = {-2, -2, -1, 1, 2, 2, 1, -1};

    /*测试下一步的出路*/
    int nexti[8] = {0};
    int nextj[8] = {0};

    /*记录出路的个数*/
    int exists[8] = {0};
    int tmpi, tmpj;
    int l, k;
    int m;
    int count;
    int min;
    int tmp;

    i = x;
    j = y;

    board[i][j] = 1;

    for(m = 2; m <= 64; m++)
    {
        for(l = 0; l < 8; l++)  //为什么？？
        {
            exists[l] = 0;
        }

        l = 0;
        /*试探八个方向的出路*/
        for(k = 0; k < 8; k++)
        {
            tmpi = i + kmove1[k];
            tmpj = j + kmove2[k];
            /*如果到了边界，不可走*/
            if(tmpi < 0 || tmpj < 0 || tmpi > 7 || tmpj > 7)
            {
                continue;
            }
            /*如果可以走，就记录下来*/
            if(board[tmpi][tmpj] == 0)
            {
                nexti[l] = tmpi;
                nextj[l] = tmpj;
                /*可走的方向+1*/
                l++;
            }
        }
        count = l;

        if(count == 0)
        {
            return 0;
        }
        else if(count == 1)
        {
            min = 0;
        }
        else
        {   /*查找下一步的下一步(步数最少)*/
            for(l = 0; l < count; l++)
            {
                for(k = 0; k < 8; k++)
                {
                    tmpi = nexti[l] + kmove1[k];
                    tmpj = nextj[l] + kmove2[k];

                    if(tmpi < 0 || tmpj < 0 || tmpi > 7 || tmpj >7)
                    {
                        continue;
                    }
                    if(board[tmpi][tmpj] == 0)
                    {
                        exists[l]++;
                    }
                }
            }
            /*寻找出路最小的方向*/
            tmp = exists[0];
            min = 0;
            for(l = 1; l < count; l++)
            {
                if(tmp > exists[l])
                {
                    tmp = exists[l];
                    min = l;
                }
            }
        }/*else end*/
        /*走最小出路的方向*/
        i = nexti[min];
        j = nextj[min];
        board[i][j] = m;
    }/*for(m = 0; m <= 64; m++) end*/

    return 1;
}/*travel() end*/
