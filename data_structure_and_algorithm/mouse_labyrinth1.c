/*
 * =====================================================================================
 *
 *       Filename:  mouse_labyrinth.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月22日 22时16分20秒
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

int visit(int i, int j);   //声明

int maze[7][7] =     //迷宫
               {
                   {2,2,2,2,2,2,2},
                   {2,0,0,0,0,0,2},
                   {2,0,2,0,2,0,2},
                   {2,0,0,2,0,2,2},
                   {2,2,0,2,0,2,2},
                   {2,0,0,0,0,0,2},
                   {2,2,2,2,2,2,2}
               };

int startI = 1, startJ = 1;   //开始位置
int endI = 5, endJ = 5;   //结束位置
int success = 0;   //标志

int visit(int i, int j)   //递归求解
{
    maze[i][j] = 1;

    if(i == endI && j == endJ)
    {
        success = 1;
    }

    if(success != 1 && maze[i][j-1] == 0 )
    {
        visit(i, j-1);
    }
    if(success != 1 && maze[i-1][j] == 0 )
    {
        visit(i-1, j);
    }
    if(success != 1 && maze[i][j+1] == 0 )
    {
        visit(i, j+1);
    }
    if(success != 1 && maze[i+1][j] == 0 )
    {
        visit(i+1, j);
    }
    
    if(success != 1)
    {
        maze[i][j] = 0;
    }

    return success;
}

int main(int argc, char **argv)
{
    int i, j;

    printf("迷宫显示为:\n");
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(2 == maze[i][j])
            {
                printf("█");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    if(0 == visit(startI, startJ))
    {
        printf("没有找出口\n");
    }
    else
    {
        printf("显示路径:\n");

        for(i = 0; i < 7; i++)
        {
            for(j = 0; j < 7; j++)
            {
                if(maze[i][j] == 2)
                {
                    printf("█");
                }
                else if(maze[i][j] == 1)
                {
                    printf("◇");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}
