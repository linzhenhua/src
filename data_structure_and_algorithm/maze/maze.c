/*
 * =====================================================================================
 *
 *       Filename:  maze.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月12日 18时17分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  演我
 *        Company:  C编程研讨学习班
 *
 * =====================================================================================
 */
/*
 *迷宫问题：
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze.h"

#define MAXROW 10

int main(int argc, char *argv[])
{
    int maze[MAXROW][MAXROW];
    int i, j;

    srand((unsigned)time(NULL));   //根据系统时钟产生随机种子

    for(i = 0; i < MAXROW; i++)
    {
        for(j = 0; j < MAXROW; j++)
        {
            maze[i][j] = rand()%2;      //随机产生0和1这两个数,0表示可走,1表示不可走
        }
    }

    return 0;
}

