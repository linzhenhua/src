/*
 * =====================================================================================
 *
 *       Filename:  msg.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 19时18分03秒
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
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

struct msg_buf
{
    int mtype;
    char mtext[512];
};

int main(int argc, char **argv)
{
    key_t key;
    int msgid;
    int ret;
    struct msg_buf msgbuf;

    key = ftok("/tmp/2", 'a');
    printf("key = %d\n", key);

    msgid = msgget(key, IPC_CREAT|0666);
    if(msgid == -1)
    {
        printf("creat error\n");
        return -1;
    }

    msgbuf.mtype = getpid();
    strcpy(msgbuf.mtext, "text msg");

    ret = msgsnd(msgid, &msgbuf, sizeof(msgbuf.mtext), IPC_NOWAIT);
    if(-1 == ret)
    {
        printf("send message error\n");
        return -1;
    }

    memset(&msgbuf, 0, sizeof(msgbuf));
    ret = msgrcv(msgid, &msgbuf, sizeof(msgbuf.mtext), getpid(), IPC_NOWAIT);
    if(-1 == ret)
    {
        printf("recv message error\n");
        return -1;
    }
    printf("recv msg = %s\n", msgbuf.mtext);

    return 0;
}
