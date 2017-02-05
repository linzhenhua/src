/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月26日 03时20分21秒
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

int main(int argc, char **argv)
{
    int a = 1;
    int b = 1;
    int c = 1;

    ++a || ++b && ++c;

    printf("%d,%d,%d \n",a, b ,c );

    return 0;
}
