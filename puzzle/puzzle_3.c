/*
 * =====================================================================================
 *
 *       Filename:  puzzle_3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 03时58分22秒
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

enum{false, true};
int main(int argc, char **argv)
    {
        int i;
        i = 1;
        do
        {
        printf("%d\n", i);
        i++;

        if(i < 15)
            continue;
        }while(false);

        return 0;
    }














