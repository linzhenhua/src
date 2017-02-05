/*
 * =====================================================================================
 *
 *       Filename:  mouse_labyrinth2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月24日 09时19分21秒
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

void visit(int i, int j);

int startI = 1, startJ = 1;   //入口
int endI = 7, endJ = 7;  //出口

int maze[9][9] = 
                {
                    {2,2,2,2,2,2,2,2,2},
                    {2,0,0,0,0,0,0,0,2},
                    {2,0,2,2,0,2,2,0,2},
                    {2,0,2,0,0,2,0,0,2},
                    {2,0,2,0,2,0,2,0,2},
                    {2,0,0,0,0,0,2,0,2},
                    {2,2,0,2,2,0,2,2,2},
                    {2,0,0,0,0,0,0,0,2},
                    {2,2,2,2,2,2,2,2,2}
                };

void visit(int i, int j)
{
    int n, m;
    maze[i][j] = 1;

    if(i == endI && j == endJ)   //递归结束条件
    {
        printf("显示路径\n");
        for(n = 0; n < 9; n++)
        {
            for(m = 0; m < 9; m++)
            {
                if(maze[n][m] == 2)
                {
                    printf("█");
                }
                else if(maze[n][m] == 1)
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

    if(maze[i-1][j] == 0)  //上
        visit(i-1, j);
    if(maze[i][j-1] == 0)  //左
        visit(i, j-1);
    if(maze[i+1][j] == 0)  //下
        visit(i+1, j);
    if(maze[i][j+1] == 0)  //右
        visit(i, j+1);

    maze[i][j] = 0;
}

int main(int argc, char **argv)
{
    int i, j;
    
    printf("迷宫为:\n");
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(maze[i][j] == 2)
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

    visit(startI, startJ);

    return 0;
}
