/******************************************************************************
*    > File Name: 14.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月19日 星期四 20时07分53秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <stdio.h>
#include <unistd.h>

void delay_play(char *str)
{
    while(*str)
    {
        putchar(*str++);
        usleep(10000);
    }
}

int main(void)
{
    char *text = "I am chinese";

    for(;;)
    {
        delay_play(text);
        puts("");
    }

    return 0;
}
