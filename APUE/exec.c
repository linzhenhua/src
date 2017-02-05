/*
 * =====================================================================================
 *
 *       Filename:  execl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 09时35分07秒
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
#include <unistd.h>

int main(void)
{
    char *argv[] = {"ls", "-al", "/etc/passwd", (char *)0};

    execv("/bin/ls", argv);

    return 0;
}
