/******************************************************************************
*    > File Name: 13.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月19日 星期四 18时39分24秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <system.h>

void delay_display(char *str)
{
    while(*str)
    {
        putchar(*str);
        ++str;
        usleep(100000);
    }
}

int main(int argc, char **argv)
{
    char *text = "为什么我学习了这么久，差距还是那么大的，其实再乐观的人有时候也会想不开的！";

    for(;;)
    {
        delay_display(text);
        printf("\n");
    }

    return 0;
}
