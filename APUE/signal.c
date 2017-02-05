/*
 * =====================================================================================
 *
 *       Filename:  signal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 08时10分42秒
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
#include <signal.h>
#include <unistd.h>

void my_signal(int sign_no)
{
    if(sign_no == SIGINT)
    {
        printf("I have get SIGINT\n");
    }
    else if(sign_no == SIGQUIT)
    {
        printf("I have get SIGQUIT\n");
    }
}

int main(int argc, char **argv)
{
    printf("Waiting for signal SIGINT or SIGQUIT\n");

    /*注册信号处理函数*/
    signal(SIGINT, my_signal);
    signal(SIGQUIT, my_signal);

    pause();

    return 0;
}
