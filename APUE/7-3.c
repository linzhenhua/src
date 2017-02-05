/*
 * =====================================================================================
 *
 *       Filename:  7-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月19日 21时16分33秒
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

int main(int argc, char *argv[])
{
    int i;

    for(i = 0; i < argc; i++)
    {
        printf("argc[%d]:%s\n", i, argv[i]);
    }

    return 0;
}
