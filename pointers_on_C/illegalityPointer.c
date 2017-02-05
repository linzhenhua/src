/*
 * =====================================================================================
 *
 *       Filename:  illegalityPointer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月02日 10时17分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//非法指针示例
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *a;

    a = (int *)malloc(sizeof(int));
    if(NULL == a)
        exit(-1);

    *a = 12;

    printf("%d\n", *a);

    free(a);
    a = NULL;

    return 0;
}
