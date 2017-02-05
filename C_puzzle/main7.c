/*
 * =====================================================================================
 *
 *       Filename:  main7.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 16时44分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 * 在C语言中凡是以0开头的数字都是八进制
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZEOF(arr) ( sizeof(arr)/sizeof(arr[0]) )
#define PirntInt(expr) printf("%d\n",  (expr))
int main(int argc, char **argv)
{
    int pot[] = {0001,0010,0100,1000};
    int i;

    for(i = 0; i <SIZEOF(pot); i++)
        PirntInt(pot[i]);

    return 0;
}


















