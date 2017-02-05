/*
 * =====================================================================================
 *
 *       Filename:  shell_sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 19时30分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 13

void shellsort(int *arr, int n);

int main(int argc, char **argv)
{
    int arr[N] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
    int i;

    printf("排序前\n");
    for(i = 0; i < N; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    shellsort(arr, N);

    printf("排序后\n");
    for(i = 0; i < N; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

void shellsort(int *arr, int n)
{
    int i, j, increment;
    int tmp;

    for(increment = n/2; increment > 0; increment /= 2)   //增量
    {
        for(i = increment; i < n; i++)   //
        {
            tmp = arr[i];
            for(j = i; j >= increment; j -= increment)   //
            {
                if(tmp > arr[j - increment])
                {
                    arr[j] = arr[j - increment];
                }
                else
                {
                    break;
                }
            }
            arr[j] = tmp;
        }/*end of for(i = increment; i < n; i++)*/
    }/*end of for(increment = n/2; increment > 0; increment /= 2)*/
}
