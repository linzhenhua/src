/*
 * =====================================================================================
 *
 *       Filename:  wheat.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月26日 22时09分56秒
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

int main(int argc, char **argv)
{
    int i;
    long long wheat = 0;
    long long n;

    for(i = 0; i < 64; i++)
    {
        n = 1<<i;
        wheat += n;
    }

    printf("%lld\n", wheat);

    return 0;
}
