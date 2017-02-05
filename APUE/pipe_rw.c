/*
 * =====================================================================================
 *
 *       Filename:  pipe_rw.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月07日 08时20分31秒
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
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pipe_fd[2];   //管道的文件描述符
    char buf_r[100];  //读缓冲
    pid_t pid;        //进程ID

    memset(buf_r, 0, sizeof(buf_r));   //将数组buf_r清零

    if( pipe(pipe_fd) < 0 )    //创建管道
    {
        printf("pipe create error\n");
        return -1;
    }

    if( (pid = fork()) == 0)   //创建进程
    {
        close(pipe_fd[1]);
        sleep(2);
        if( read(pipe_fd[0], buf_r, sizeof(buf_r)) < 0 )
        {
            printf("read error\n");
            return -1;
        }
        else
        {
            printf("read from the pipe is %s\n", buf_r);
            close(pipe_fd[0]);
        }
    }
    else
    {
        close(pipe_fd[0]);
        if( write(pipe_fd[1], " hello ", 7) < 0)
        {
            printf("write error\n");
            return -1;
        }
        if( write(pipe_fd[1], " pipe ", 6) < 0)
        {
            printf("write error\n");
            return -1;
        }
        close(pipe_fd[1]);
        sleep(3);
        waitpid(pid, NULL, 0);
    }

    return 0;
}
