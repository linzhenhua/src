/*
 * =====================================================================================
 *
 *       Filename:  3-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月27日 21时08分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char **argv)
{
    int fd;

    if((fd = creat("3-2.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        printf("create error\n");
        return -1;
    }

    if(write(fd, buf1, 10) != 10)
    {
        printf("buf1 write error\n");
        return -1;
    }

    if(lseek(fd, 16384, SEEK_SET) == -1)
    {
        printf("lseek error\n");
        return -1;
    }

    if(write(fd, buf2, 10) != 10)
    {
        printf("buf2 write error\n");
        return -1;
    }

    return 0;
}
