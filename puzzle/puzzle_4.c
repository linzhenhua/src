/*
 * =====================================================================================
 *
 *       Filename:  puzzle_4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 04时44分46秒
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

#define f(a, b) a##b
#define g(a) #a
#define h(a) g(a)

int main(int argc, char **argv)
{
    printf("%s\n", h(f(1,2)) );
    printf("%s\n", g(f(1,3)) );

    return 0;
}













