/*
 * =====================================================================================
 *
 *       Filename:  main10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时14分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *scanf中的%[^r]是从中做梗的东西，意思就是遇到字符r就结束了。。
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char dummy[80];

    printf("Enter a string:\n");
    scanf("%[^r]", dummy);
    printf("%s\n", dummy);

    return 0;
}

