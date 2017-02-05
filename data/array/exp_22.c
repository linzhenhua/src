/*
 * =====================================================================================
 *
 *       Filename:  exp_22.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 08时22分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//简单计算器
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float result, y;
    char ch;

    printf("请输入一个不带括号的算术表达式，以等号结束:\n");
    scanf("%f%c", &result, &ch);
    while(ch != '=')
    {
        scanf("%f", &y);
        switch( ch )
        {
            case '+':result += y; break;
            case '-':result -= y; break;
            case '*':result *= y; break;
            case '/':result /= y; break;
        }
        scanf("%c", &ch);
    }
    printf("%f\n", result);

    return 0;
}
