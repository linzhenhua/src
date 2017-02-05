/*
 * =====================================================================================
 *
 *       Filename:  exp_32.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 10时28分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//   a
//  aca
// aceca
//acegeca
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j, k;
    char ch = 'a';
    int num;

    for(i = 1; i <= 4; i += 1)
    {
        for(k = 1; k <= 10-i; k++)    //打印空格
        {
            printf(" ");
        }
        num = i;
        ch = 'a' - 2;
        for(j = 1; j <= 2*i-1; j += 1)
        {
            if(j <= num)
            {
                ch = ch + 2;
                printf("%c", ch);
            }
            if(j > num)
            {
                ch = ch -2;
                printf("%c", ch);
            }
        }
        printf("\n");
    }

    return 0;
}
