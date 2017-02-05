/*
 * =====================================================================================
 *
 *       Filename:  7.3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月05日 14时50分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int ascii_to_integer(char *string);

int ascii_to_integer(char *string)
{
    int value = 0;
    int sum = 0;

    while(*string != '\0')
    {
        if(*string >= '0' && *string <= '9')
        {
            value = *string - 48;
            sum = sum * 10 + value;
        }
        string++;
    }

    return sum;
}

int main(int argc, char **argv)
{
    int a;
    char array[] = "A22BDCE11";

    a = ascii_to_integer(array);

    printf("%d\n", a);

    return 0;
}
