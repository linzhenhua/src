/*
 * =====================================================================================
 *
 *       Filename:  shmem.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 15时36分56秒
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
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PERM S_IRUSR|S_IWUSR

int main(int argc, char **argv)
{
    int shmid;
    char *p_addr, *c_addr;

    if(argc != 2)
    {
        printf("usage:./a.out string\n");
        return -1;
    }

    /*创建共享内存*/
    if((shmid = shmget(IPC_PRIVATE, 1024, PERM)) == -1)
    {
        printf("create share memory error\n");
        return -1;
    }

    /*创建子进程*/
    if(fork())  // 父进程写
    {
        p_addr = shmat(shmid, 0, 0);   //映射
        memset(p_addr, '\0', 1024);
        strncpy(p_addr, argv[1], 1024);
        wait(NULL);   //释放资源,不必关心终止状态
        return 0;
    }
    else   //子进程
    {
        sleep(1);
        c_addr = shmat(shmid, 0, 0);
        printf("client get %s\n", c_addr);
        return 0;
    }

    return 0;
}
