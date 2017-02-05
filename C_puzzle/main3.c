/*
 * =====================================================================================
 *
 *       Filename:  main3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月09日 22时11分26秒
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

int main(void)
{
    float a = 12.5;
    
    printf("%d\n", a);
    printf("%d\n", (int)a);
    printf("%d\n", *(int*)&a);

    return 0;

}







