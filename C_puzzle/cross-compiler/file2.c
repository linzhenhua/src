/*
 * =====================================================================================
 *
 *       Filename:  file2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 15时20分31秒
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
//#include <file1.c>

extern int *arr;
int main(int argc, char **argv)
{
    arr[1] = 100;

    printf("%d\n", arr[1]);

    return 0;
}





