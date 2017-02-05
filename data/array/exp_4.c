/*
 * =====================================================================================
 *
 *       Filename:  exp_4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 03时30分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//编写程序实现1+3+5....+99的和的语句
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;
    int sum = 0;
    FILE *fp;

    fp = fopen("exp_4.txt", "w");
    if(NULL == fp )
    {
        perror("exp_4.txt");
        exit(-1);
    }

    while(i <= 99)
    {
        sum +=i;
        fprintf(fp,"第%d个数的和为%d\n", i, sum);        
        i = i + 2;
    }

    fclose(fp);

    printf("1+3+5+..+99的和为%d\n", sum);

    return 0;
}














