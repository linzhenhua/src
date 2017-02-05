/******************************************************************************
*    > File Name: 2.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月24日 星期二 07时39分58秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void delay_display(char *ptr)
{
    while(*ptr)
    {
        putchar(*ptr++);
        fflush(stdout);
        usleep(1000000);
    }
}

int main(int argc, char **argv)
{
    char *text = "when the going gets tough, the tough get going";

    for(;;)
    {
        delay_display(text);
        puts("");
    }

    return 0;
}
