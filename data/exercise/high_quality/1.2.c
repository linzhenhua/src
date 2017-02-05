/******************************************************************************
*    > File Name: 1.2.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年01月17日 星期五 10时52分42秒
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

int main(int argc, char **argv)
{
    float flag = 0.0;
    const float ZERO = 0.00001;

    if(flag <= ZERO && flag >= -ZERO)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    return 0;
}
