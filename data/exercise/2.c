/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月31日 22时31分13秒
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

void getmemory(char **add)
{
    *add = (char *)malloc(100);

    strcpy(*add, "eeeeee");
}

int main(int argc, char *argv[])
{
    char *str = NULL;

    getmemory(&str);

    printf("%s\n", str);

    free(str);

    return 0;
}
