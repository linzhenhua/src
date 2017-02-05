/*
 * =====================================================================================
 *
 *       Filename:  6.2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月03日 10时19分38秒
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
#include <string.h>

char *del_substr(char *src, const char *sub);

int main(int argc, char **argv)
{
    char string[] = "ABCDEFG";  //定义一个字符串
    char *sub = "CDE";
    char *ch;

    printf("原来的字符串是%s\n", string);

    ch = del_substr(string, sub);

    printf("变化后的字符串是%s\n", string);

    return 0;
}

char *del_substr(char *src, const char *sub)
{
    int len;
    char *ch;
    char *temp;

    temp = src;

    if (src == NULL || sub == NULL)
        return NULL;     

    len = strlen(sub);
                         
    if((ch = strstr(temp, sub)) != NULL)
    {
        strcpy(temp, ch + len);                                               
    }
     return temp;
}
