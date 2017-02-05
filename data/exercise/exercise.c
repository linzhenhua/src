/******************************************************************************
*    > File Name: exercise.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月20日 星期五 18时58分11秒
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

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef struct linkNode
{
    char *argument;         //参数
    int position;           //位置
    char *option;           //附加选项
    struct linkNode *next;  //指向下一个
}text;

typedef struct
{
	text *head;    //链表头指针
	text *rear;    //链表尾指针
	int length;    //链表长度
}linklist;

/*****************************************************************************/
/*链表初始化*/
/*****************************************************************************/
Status Linklist_init( linklist *L )
{
     L->head = (text*)malloc( sizeof(text) );
	 if( NULL == L->head )
		 return ERROR;

	 L->rear = L->head;
	 L->rear->next = NULL;
	 L->length = 1;

     return OK;
}

/*****************************************************************************/
/*向链表加入元素*/
/*****************************************************************************/
Status Linklist_add(linklist *L, char *X, char *Y)
{
	text *s;

    if(*X == '-')
    {
	    s = (text *)malloc(sizeof(text));
	    if( NULL == s )
		    return ERROR;

	    s->argument = X;
        s->position = ++L->length;
        s->option = Y;
	    s->next = NULL;

	    L->rear->next = s;
	    L->rear = s;
        //printf("add %s OK\n", X);   //test OK
    }

	return OK;
}

/*****************************************************************************/
/*遍历链表*/
/*****************************************************************************/
Status Linklist_show( linklist *L)
{
	text *s = L->head->next;
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    //char *ptr = alphabet;
    //int flag = 0;
    //int i;

    while(*alphabet)
    {
	    while( s != NULL )//判断字符链表结束了没有
	    {
            while( *++s->argument )
            {
                if(*alphabet  == *s->argument)
                {
                    printf("参数:%c, 存在, 位置:%d, 附加选项:%s\n", *alphabet, s->position, s->option);
                    alphabet++;
                    continue;
                }
            }/*end of while(++s->argument)*/
            s = s->next;
        }/*end of while( s != NULL)*/
        printf("参数:%c, 不存在, 位置:-1, 附加选项:NULL\n", *alphabet);
        alphabet++;
        s = L->head->next;
    }/*end of while(*alphabet)*/

	return OK;
}

/*****************************************************************************/
/* argc :参数个数
 * argv : 参数列表比如说: -a "h H", 那么argv[1]就是-a，argv[2]就是“h H”
 */
/*****************************************************************************/
int main(int argc, char *argv[])
{
    int i;
    linklist L;

    Linklist_init(&L);    //初始化链表

    for(i = 1; i< argc; ++i)
    {
        Linklist_add(&L, argv[i], argv[i+1]);
    }

    Linklist_show(&L);

    return 0;
}
