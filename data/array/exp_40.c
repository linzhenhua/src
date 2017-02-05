/*
 * =====================================================================================
 *
 *       Filename:  exp_40.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月28日 10时32分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//用筛法求素数
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

int main(int argc, char *argv[])
{
    int i,j;
    int arr[SIZE+1];
    FILE *fp;

    fp = fopen("exp_40.txt","w");
    if(NULL == fp)
    {
        perror("exp_40.txt");
    }

    for(i = 0; i <= 100000; i++)
    {
        arr[i] = i;
    }

    for(i = 2; i <= 100000; i++)
    {
        if(arr[i] != 0)
        {
            fprintf(fp, "%d是素数\n", arr[i]);
        
            for(j = 1; i*j <= 100000; j++)
            {
                arr[i*j]= 0;
            }
        }
    }
    fclose(fp);

    return 0;
}
