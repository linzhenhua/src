/******************************************************************************
*    > File Name: overflow_test.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年04月30日 星期三 22时58分16秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int main(int argc, char *argv[]) 
{ 
    int flag = 0; 
    char passwd[10]; 
 
    memset(passwd,0,sizeof(passwd)); 
 
    strcpy(passwd, argv[1]); 
 
    if(0 == strcmp("LinuxGeek", passwd)) 
    { 
        flag = 1; 
    } 
 
    if(flag) 
    { 
        printf("\n Password cracked \n"); 
    } 
    else 
    { 
        printf("\n Incorrect passwd \n"); 
 
    } 
    printf("%d\n", flag);

    return 0; 
}

