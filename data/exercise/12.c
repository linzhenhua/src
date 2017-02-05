#include<stdio.h> 
#include <string.h>
 
int main(int argc, char *argv[]) 
{ 
    //char arr[5] ={'a','b','c','d','e'};
    char passwd[10]; 
    int flag = 0; 
    //printf("%d\n", argc);
    memset(passwd,0,sizeof(passwd)); 
 
    strcpy(passwd, argv[1]); 
    //printf("%d\n", argc);
    //printf("%x\t%x\n", &arr[0], &arr[1]);
    printf("%x\t%x\n", &passwd, &flag);

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
    return 0; 
} 
