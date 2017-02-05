/*
 * =====================================================================================
 *
 *       Filename:  insert_sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 20时41分53秒
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

#define N 6

void insertSort(int *arr, int n);

int main(int argc, char **argv)
{
    int i;
    int arr[N] = {34, 8, 64, 51, 32, 21};

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

/*插入排序*/
void insertSort(int *arr, int n)
{
    int j, p;
    int tmp;

    for(p = 1; p < n; p++)
    {
        tmp = arr[p];
        for(j = p; j > 0 && arr[j-1] > tmp; j--)
        {
            arr[j] = arr[j-1];
        }
        arr[j] = tmp;
    }
}
