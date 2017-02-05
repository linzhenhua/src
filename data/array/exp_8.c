/*
 * =====================================================================================
 *
 *       Filename:  exp_8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月13日 22时36分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//输出1到999能被3整除且至少有一位是5的整数
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;
    FILE *fp;

    fp = fopen("exp_8.txt", "w");
    if(NULL == fp)
    {
        perror("exp_8.txt");
        exit(-1);
    }

    while(i <= 999)
    {
        if(i %3 == 0 && ( i%10==5 || (i%100)/10==5 || i/100==5 ) )
        {
            fprintf(fp, "能被3整除且至少有一位是5的数为%d\n", i);
        }
        i++;
    }
    fclose(fp);

    return 0;
}
