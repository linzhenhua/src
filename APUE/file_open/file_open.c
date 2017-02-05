/*
 * =====================================================================================
 *
 *       Filename:  file_open.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月02日 09时01分21秒
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
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    int i;

    if(argc < 2)
    {
        printf("usage:./a.out filename\n");
    }
    else
    {
        for(i = 1; i < argc; ++i)
        {
            if( (fd = open(argv[i], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR)) < 0)
            {
                printf("open error\n");
                exit(-1);
            }
            else
            {
                printf("open %d ok\n", fd);
            }
        }
    }
    close(fd);

    return 0;
}
