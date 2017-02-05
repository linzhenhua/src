/*
 * =====================================================================================
 *
 *       Filename:  insertSort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 20时35分57秒
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

#define N 6

void insertSort(int *arr, int n);

int main(int argc, char **argv)
{
    int arr[N] = {34, 8, 64, 51, 32, 21};
    int i;

    printf("排序前:\n");
    for(i = 0; i < N; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    insertSort(arr, N);

    printf("排序后:\n");
    for(i = 0; i < N; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

void insertSort(int *arr, int n)
{
    int i, j;
    int tmp;

    for(i = 1; i < n; i++)
    {
        tmp = arr[i];
        for(j = i; j > 0 && arr[j-1] > tmp; j--)
        {
            arr[j] = arr[j-1];
        }
        arr[j] = tmp;
    }
}
