/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 21时41分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *str = "ABC";

    while(*str != '\0')
    {
        printf("%c\n", *str);
        str++;
    }

    return 0;    
}
