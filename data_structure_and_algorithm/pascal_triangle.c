/*
 * =====================================================================================
 *
 *       Filename:  pascal_triangle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月21日 10时12分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12   //有多少行(就是12+1)

int combi(int n, int r);  //
int paint();   //

int combi(int n, int r)
{
    int i;
    long p = 1;

    for(i = 1; i <= r; i++)
    {
        p = p*(n-i+1)/i;
    }

    return p;
}

int paint()
{
    int i, n, r;

    for(n = 0; n <= N; n++)
    {
        for(r = 0; r <= n; r++)
        {
            if(0 == r)   //打印空格
            {
                for(i = 0; i <= (N-n); i++)
                {
                    printf("   ");
                }
            }
            else
            {
                printf("   ");
            }  //打印空格结束
            printf("%3d", combi(n,r));
        }
        printf("\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    paint();

    return 0;
}
