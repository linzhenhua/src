/*
 * =====================================================================================
 *
 *       Filename:  puzzle_1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 10时43分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *因为sizeof返回值为unsigned int，其他的值将会强制转换。。
 */
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]) )

int main(int argc, char **argv)
{
    int array[] = {23,34,12,17,204,99,16};
    int i;

    for(i = -1; i <= (TOTAL_ELEMENTS-2); i++)
        printf("%d\n", array[i+1]);

    return 0;
}







