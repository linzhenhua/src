/*
 * =====================================================================================
 *
 *       Filename:  exp_7.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 21时48分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//编程实现1+1/4-1/7+1/10+1/13-1/16...共20项之和
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;  //循环次数
    int k = 1; //符号
    float n; //第i项的和
    float sum = 0; //总和
    int denominator = 1; //分母
    FILE *fp;

    fp = fopen("exp_7.txt", "w");
    if(NULL == fp)
    {
        perror("exp_7.txt");
        exit(-1);
    }

    while(i <= 20)
    {
        n = 1.0*k/denominator;
        sum +=n;
        fprintf(fp, "第%d项的和为%f\n", i, sum);
        denominator +=3;
        
        i++;
        if(i % 3 == 0)
        {
            k = -k;
        }
    }
    fclose(fp);

    printf("20项的和为%f\n", sum);

    return 0;
}
