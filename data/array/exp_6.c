/*
 * =====================================================================================
 *
 *       Filename:  exp_6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 20时55分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//编程求2/3-3/4+4/5-5/6+6/7-......共50项之和
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int k = 1; // 符号位
    int i = 1; // 第几项
    float sum = 0; //总和
    float n; //第i项的和
    int member = 2;
    int denominator = 3; //分子和分母
    FILE *fp;

    fp = fopen("exp_6.txt", "w");
    if(NULL == fp)
    {
        perror("exp_6.txt");
        exit(-1);
    }

    while(i <= 50)
    {
        n = 1.0*k*member/denominator;
        sum += n;
        fprintf(fp,"第%d项的和为%f\n", i, sum);
        k = -k;
        member++;
        denominator++;
        i++;
    }
    fclose(fp);
    printf("50项之和为%f\n", sum);

    return 0;
}
