/*
 * =====================================================================================
 *
 *       Filename:  file_create.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月02日 08时12分05秒
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
#include <fcntl.h>

void file_cteate(char *filename);

int main(int argc, char **argv)
{
    int i;

    if(argc < 2)
    {
        printf("usage:./a.out filename\n");
        return -1;
    }
    else
    {
        for(i = 1; i < argc; ++i)
        {
            file_cteate(argv[i]);
        }
    }

    return 0;
}

void file_cteate(char *filename)
{
    if(creat(filename, S_IRUSR | S_IWUSR | S_IXUSR) < 0)
    {
        printf("create file error\n");
        exit(-1);
    }
    else
    {
        printf("create ok\n");
    }
}
