/*
 * =====================================================================================
 *
 *       Filename:  exp_30.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 08时22分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//打印乘法口诀表
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    int result;
    FILE *fp;

    fp = fopen("exp_30.txt","w");
    if(NULL == fp)
    {
        printf("打开文件失败\n");
        exit(-1);
    }

    for(i = 1; i <= 9; i++)
    {
        for(j = 1; j <= 9; j++)
        {
            result = i * j;
            fprintf(fp,"%d*%d=%d\t", i, j, result);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}
