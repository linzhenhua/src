/*
 * =====================================================================================
 *
 *       Filename:  system.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 09时59分01秒
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

int main(int argc, char **argv)
{
    system("ls -al /etc/passwd");

    return 0;
}
