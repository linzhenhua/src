/*
 * =====================================================================================
 *
 *       Filename:  exp_3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 03时14分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//goto语句
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;
    int sum = 0;

    loop: sum = sum +i;  //loop是语句标号，配合goto语句
         i = i + 1;
         if(i <= 100)
             goto loop;

         printf("橘子数为%d\n", sum);

         return 0;
}















