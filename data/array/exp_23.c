/*
 * =====================================================================================
 *
 *       Filename:  exp_23.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月22日 08时50分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
//求10万以内的素数
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int flag = 1; //标记，当flag==1时，是素数，否则不是素数
    int i, j;  //循环变量
    FILE *fp;

    fp = fopen("exp_23.txt","w");
    if(NULL == fp)
    {
        printf("打开文件失败\n");
        exit(-1);
    }

    for(i = 2; i <= 100000; i++)  //1不是素数
    {
        for(j = 2; flag != 0 && j <= sqrt(i); j++)  
        {
            if(i % j == 0 )
            {
                flag = 0;
            }
        }
        if(flag == 1)
        {
            fprintf(fp, "%d是素数\n", i);
        }
        flag = 1;    //记得重置flag==1，很重要
    }
    fclose(fp);
    
    return 0;
}
