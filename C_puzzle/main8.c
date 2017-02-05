/*
 * =====================================================================================
 *
 *       Filename:  main8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 22时52分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *这是一个短路求值的问题，对于（条件1 && 条件2），当条件1 false时，就直接跳过条件2了，
 *对于（条件1 ||条件2），当条件1 ture时，直接跳过条件2。。。
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 6;

    if( ((++i < 7)&&(i++/6)) || (++i <= 9) )
        ;

    printf("%d\n", i);

    return 0;
}













