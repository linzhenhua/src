/*
 * =====================================================================================
 *
 *       Filename:  exp_10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月14日 02时51分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//输出1到999之间用5除余3并且用7除余4的所有数
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 1;
    FILE *fp;

    fp = fopen("exp_10.txt", "w");
    if(NULL == fp)
    {
        perror("exp_10.txt");
        exit(-1);
    }

    while(i <= 999)
    {
        if(i%5==3 && i%7==4)
        {
            fprintf(fp, "能用5除余3且用7除余4的数为%d\n", i);
        }
        i++;
    }
    fclose(fp);

    return 0;
}
