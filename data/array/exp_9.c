/*
 * =====================================================================================
 *
 *       Filename:  exp_9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月14日 02时36分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//输出1到999能被3整除，或者至少有一位是5的所有整数
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;
    FILE *fp;

    fp = fopen("exp_9.txt","w");
    if(NULL == fp)
    {
        perror("exp_9.txt");
        exit(-1);
    }

    while(i <= 999)
    {
        if(i %3 ==0 || (i%10==5 || (i%100)/10==5 || i/100==5) )
        {
            fprintf(fp, "能被3整除或者至少有一位是5的数为%d\n", i);
        }
        i++;
    }
    fclose(fp);

    return 0;
}
