/*
 * =====================================================================================
 *
 *       Filename:  file_cp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月02日 09时53分53秒
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

#define BUFSIZE 4096

int main(int argc, char **argv)
{
    int from_fd, to_fd;  //文件描述符
    char buf[BUFSIZE];  //缓冲区
    int read_byte, write_byte;  //读到的字节数
    char *ptr;

    if(argc != 3)  //最少需要3个参数
    {
        fprintf(stdout, "usage:./a.out readname writename\n");
        exit(-1);
    }
    else
    {   /*打开源文件*/
        if((from_fd = open(argv[1], O_RDONLY)) == -1)
        {
            fprintf(stdout, "open %s error\n", argv[1]);
            exit(-1);
        }
        /*创建目的文件*/
        if((to_fd = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
        {
            fprintf(stdout, "open %s error\n", argv[2]);
            exit(-1);
        }
        /*开始拷贝文件*/
        while(read_byte = read(from_fd, buf, BUFSIZE))
        {
            /*一个致命的错误发生了*/
            if(read_byte == -1)
                break;
            else if(read_byte > 0)
            {
                ptr = buf;
                while(write_byte = write(to_fd, ptr, read_byte))
                {
                    /*一个致命的错误发生了*/
                    if(write_byte == -1)
                        break;
                    /*写完所有读的字节*/
                    else if(write_byte == read_byte)
                        break;
                    /*只写了一部分，继续写*/
                    else if(write_byte > 0)
                    {
                        ptr += write_byte;
                        read_byte -= write_byte;
                    }
                }/*end while(write_byte = write(to_fd, ptr, read_byte))*/
                /*写的时候发生的致命错误*/
                if(write_byte == -1)
                    break;
            }/*end else if(read_byte > 0)*/
        }/*while(read_byte = read(from_fd, buf, BUFSIZE))*/
    }

    close(from_fd);
    close(to_fd);
    
    return 0;
}
