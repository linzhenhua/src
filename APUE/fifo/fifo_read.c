/*
 * =====================================================================================
 *
 *       Filename:  fifo_read.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月07日 10时12分55秒
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
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO "/tmp/myfifo"

int main(int argc, char **argv)
{
    char buf_r[100];   //读缓冲
    int fd;            //打开文件描述符
    int nread;         //读文件描述符
    int i = 5;

    /*创建管道*/
    if(mkfifo(FIFO, O_CREAT|O_EXCL) < 0)
    {
        printf("cannot create fifoserver\n");
    }

    printf("Preparing for reading bytes...\n");

    memset(buf_r, 0, sizeof(buf_r));   //将buf_r数组清0

    /*打开管道*/
    fd = open(FIFO, O_RDONLY|O_NONBLOCK, 0);
    if(-1 == fd)
    {
        perror("open");
    }
    while(i)
    {
        memset(buf_r, 0, sizeof(buf_r));

        if( (nread = read(fd, buf_r, 100)) == -1 )
        {
            if(errno == EAGAIN)
            {
                printf("no data yet\n");
            }
            printf("read error\n");
            return -1;
        }
        printf("read is %d\n", nread);
        printf("read %s from FIFO\n", buf_r);
        sleep(1);
        i--;
    }
    unlink(FIFO);    //删除目录项

    return 0;
}
