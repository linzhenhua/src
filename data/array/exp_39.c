/*
 * =====================================================================================
 *
 *       Filename:  exp_39.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月28日 08时53分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//高效洗扑克牌算法
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 54

int main(int argc, char *argv[])
{
    int pk[SIZE+1];
    int i;
    int num;
    FILE *fp;

    fp = fopen("exp_39.txt","w");
    if(NULL == fp)
    {
        printf("打开文件失败\n");
        exit(-1);
    }

    for(i = 0; i <= SIZE; i++)
        pk[i] = i;
    
    srand((unsigned)time(NULL));   //产生时间随机种子

    for(i = 54; i >= 2; i--)
    {
        num = rand()%i+1;
        fprintf(fp, "%d\n", pk[num]);
        pk[num] = pk[i];
    }
    fprintf(fp, "%d\n", pk[i]);
    fclose(fp);

    return 0;
}
