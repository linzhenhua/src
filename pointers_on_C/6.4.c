/*
 * =====================================================================================
 *
 *       Filename:  6.4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月04日 20时14分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
#define FALSE 0
#define TRUE 1

int main(int argc, char **argv)
{
    int i, j;
    int array[SIZE+1];
    int *parr;
    FILE *fp;

    fp = fopen("6.4.txt","w");
    if(NULL == fp)
    {
        perror("6.4.txt");
        exit(-1);
    }

    parr = array;
    for(i = 0; i <= SIZE; i++)
    {
        *(parr+i) = i;
    }
    
    for(i = 2; i <= SIZE; i++)
    {
        if(*(parr+i) != FALSE)
        {
            fprintf(fp, "%d是素数\n", *(parr+i));
            
            for(j = 1; i*j <= SIZE; j++)
            {
                *(parr+i*j) = FALSE;
            }
        }
    }
    fclose(fp);

    return 0;
}
