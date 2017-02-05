/*
 * =====================================================================================
 *
 *       Filename:  exp_28.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 08时04分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印
//a
//ab
//abc
//abcd
//abcde
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    char ch = 'a';

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j <= i; j++)
        {
            printf("%c", ch);
            ch = ch + 1;
        }
        printf("\n");
        ch = 'a';
    }
    
    return 0; 
}
