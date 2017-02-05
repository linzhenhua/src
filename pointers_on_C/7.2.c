/*
 * =====================================================================================
 *
 *       Filename:  7.2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月05日 10时59分17秒
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

int gcd(int M, int N);
int iterator_gcd(int M, int N);

int gcd(int M, int N)
{
    int R;

    R = M % N;
    if(R == 0)
        return N;
    if(R > 0)
        return gcd(N, R);
}

int iterator_gcd(int M, int N)
{
    int R;

    while((R = M % N) != 0)
    {
        M = N;
        N = R;
    }
    printf("result2=%d\n", N);

    return 0;
}

int main(int argc, char **argv)
{
    int result;
    int M;
    int N;

    printf("please iuput M and N(M,N)\n");
    scanf("%d,%d", &M, &N);

    result = gcd(M,N);
    iterator_gcd(M,N);

    printf("result1=%d\n", result);

    return 0;
}
