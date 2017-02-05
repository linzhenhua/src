/*
 * =====================================================================================
 *
 *       Filename:  exp_5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 04时57分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 *求1-1/3+1/5-1/7+1/9...共50项之和
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;   //表示项数，共50项
    float sum = 0;  //表示第i项的和
    int m = 1;  //表示分母
    int k = 1;   //表示符号，有正和负
    float n;
    FILE *fp;

    fp = fopen("exp_5.txt", "w");
    if(NULL == fp)
    {
        perror("exp_5.txt");
        exit(-1);
    }

    while(i <= 50)
    {
        n = 1.0*k/m;
        sum += n;
        fprintf(fp,"第%d项的和为%f\n", i, sum);
        k = -k;
        m = m+2;
        i = i+1;
    }
    fclose(fp);
    printf("这50项的和为%f\n", sum);

    return 0;
}










