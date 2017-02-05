/*
 * =====================================================================================
 *
 *       Filename:  6.3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月04日 14时38分34秒
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

void reverse_string(char *string);
void inplace_swap(int *a, int *b);
void reverse_array(int *arr, int count);

void reverse_string(char *string)
{
    char temp;
    char *last_char;

    for(last_char = string; *last_char != '\0'; last_char++)
        ;
    last_char--;

    while(string < last_char)
    {
        temp = *string;
        *string++ = *last_char;
        *last_char-- = temp;
    }

}

void inplace_swap(int *a, int *b)
{
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

void reverse_array(int *arr, int count)
{
    int first;
    int last;

    for(first = 0, last = count; first < last; first++, last--)
    {
        inplace_swap(&arr[first], &arr[last]);
    }
}

int main(int argc, char **argv)
{
    char string[] = "ABCDEFG";
    int num[] = {1,2,3,4,5,6,7};
    int i;

    printf("原字符串为%s\n", string);
    printf("原来的数字为\n");
    for(i = 0; i < 7; i++)
    {
        printf("%d", num[i]);
    }
    puts("");

    reverse_string(string);

    reverse_array(num, 6);
    
    printf("变化后的字符串为%s\n", string);
    printf("变化后的数字为\n");
    for(i = 0; i < 7; i++)
    {
        printf("%d", num[i]);
    }
    puts("");
    return 0;
}
