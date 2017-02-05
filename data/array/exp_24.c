/*
 * =====================================================================================
 *
 *       Filename:  exp_24.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 10时40分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印图形
//*****
//*****
//*****
//*****
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 5; j++)
            printf("*");
        printf("\n");
    }

    return 0;
}
