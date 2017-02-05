/*
 * =====================================================================================
 *
 *       Filename:  main11.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时24分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *就是利用移位操作，例如：a = 5, b = (a<<2)+a，就是将5*2^2+5，b就是25了。。
 */
#include <stdio.h>
#include <stdlib.h>

#define PrintInt(expr) printf("%s: %d\n", #expr,(expr));

int FiveTimes(int a)
{
    int t;

    t = (a<<2) +a;
    return t;
}

int main(int argc, char **argv)
{
    int a = 1, b = 2, c = 3;

    PrintInt(FiveTimes(a));
    PrintInt(FiveTimes(b));
    PrintInt(FiveTimes(c));

    return 0;
}

