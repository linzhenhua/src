/*
 * =====================================================================================
 *
 *       Filename:  fifo_write.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月07日 10时13分21秒
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
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_SERVER "/tmp/myfifo"

int main(int argc, char **argv)
{
    int fd;          //打开文件描述符
    char buf_w[100]; //写缓冲
    int nwrite;      //写描述符

    /*打开管道*/
    fd = open(FIFO_SERVER, O_WRONLY|O_NONBLOCK, 0);
    if(-1 == fd)
    {
        perror("open");
        return -1;
    }

    if(argc == 1)
    {
        printf("Please send something\n");
        return -1;
    }

    strcpy(buf_w, argv[1]);

    /*向管道写入数据*/
    if((nwrite = write(fd, buf_w, 100)) == -1)
    {
        if(errno == EAGAIN)
        {
            printf("The FIFO has not been read yet. Please try later\n");
        }
    }
    else
    {
        printf("write %s to the FIFO\n", buf_w);
    }

    return 0;
}

