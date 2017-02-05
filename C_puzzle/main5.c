/*
 * =====================================================================================
 *
 *       Filename:  main5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 15时34分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *我们以为在switch语句中会将b初始化，其实并不然，事实上是在switch语句中直接将b的初始化直接跳过
 * */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int a = 1;

    switch(a)
    {
        int b = 20;

        case 1:
            printf("b:%d\n", b);
            break;

        default:
            printf("b:%d\n", b);
            break;
    }

    return 0;
}













