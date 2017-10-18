#include <stdio.h>
#include <stdlib.h>

#include "bcd2hex.h"

int main()
{
    char ch = 'a';
    char arr[10] = {0};

    EbcToAsc(&ch, arr, 1);

    printf("%s\n", arr);

    char arr1[3] = "61";
    char ch1;

    AscToEbc(arr1, 2);
    printf("%s\n", arr1);

    return 0;
}
