/*
 * =====================================================================================
 *
 *       Filename:  exp_34.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月25日 08时27分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//求1000以内的守形数
//守形数：若某数的平方，其低位与该数本身相同，则该数为守形数，5^2=25,25^2=625
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;  //循环
    int product;  //积
    FILE *fp;

    fp = fopen("exp_34.txt","w");
    if(NULL == fp)
    {
        printf("打开文件失败\n");
        exit(-1);
    }

    for(i = 0; i <= 1000; i++)
    {
        product = i*i;
        
        if(i < 10 && product % 10 == i)
        {
            fprintf(fp, "%d是守形数\n", i);
        }
        else if(i < 100 && product % 100 == i)
        {
            fprintf(fp, "%d是守形数\n", i);
        }
        else if(i < 1000 && product % 1000 == i)
        {
            fprintf(fp, "%d是守形数\n", i);
        }
    }
    fclose(fp);

    return 0;
}
