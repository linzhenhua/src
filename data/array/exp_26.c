/*
 * =====================================================================================
 *
 *       Filename:  exp_26.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 10时50分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//12345
//12345
//12345
//12346
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 1; j <= 5; j++)
            printf("%d", j);
        printf("\n");
    }

    return 0;
}
