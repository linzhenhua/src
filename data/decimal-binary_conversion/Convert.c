/*
 * =====================================================================================
 *
 *       Filename:  Convert.c(数据结构版)
 *
 *    Description:  none  
 *
 *        Version:  1.0
 *        Created:  2013年07月18日 08时20分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  none
 *        Company:  C游戏编程研讨班
 *
 * =====================================================================================
 */
//将一个十进制的整数d转换为二进制,八进制,十六进制数，d可以是负数
//思路：先将十进制的数d转换成二进制，在转换成其他进制
//系统：linux,32位
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define STACKINITSIZE 100
#define STACKEXTENDSIZE 10

typedef int Status;
typedef int ElementType;
typedef char listType;
//栈定义
typedef struct
{
    ElementType *top;
    ElementType *base;
    int stackSize;
}stack;
//双向链表定义
typedef struct listNode
{
    listType data;
    struct listNode *next;
    struct listNode *front;
}listNode, position;
typedef struct     //没有表头的双向链表
{
    position *rear;
    int listSize;
}linklist;

Status LinklistInit(linklist *L);   //初始化链表
Status LinklistAdd(linklist *L, listType X);   //向链表加入元素
Status LinklistShow(linklist *L);   //倒序遍历链表

Status StackInit(stack *S);  //初始化栈
Status StackPush(stack *S, ElementType *X); //压栈
Status StackPop(stack *S, ElementType *X);  //弹栈
Status StackShow(stack *S);  //遍历栈
int StackLength(stack *S);  //返回栈当前长度
//===================================================================================================
//栈初始化
//===================================================================================================
Status StackInit(stack *S)
{
    S->top = S->base = (ElementType *)malloc( STACKINITSIZE * sizeof(ElementType) );
    if(NULL == S->top)
        return ERROR;
    S->stackSize = STACKINITSIZE;

    return OK;
}
//===================================================================================================
//压栈
//===================================================================================================
Status StackPush(stack *S, ElementType *X)
{
    if(S->top - S->base >= STACKINITSIZE )
    {
        S->base = (ElementType *)realloc(S->base, (S->stackSize + STACKEXTENDSIZE)*sizeof(ElementType) );  //如果栈空间不够，要从新分配
        if(NULL == S->base)
            return ERROR;

        S->top = S->base + S->stackSize;
        S->stackSize += STACKEXTENDSIZE;
    }

    *S->top++ = *X;

    return OK;
}
//=================================================================================================
//弹栈
//=================================================================================================
Status StackPop(stack *S, ElementType *X)
{
    if(S->top == S->base)
        return ERROR;

    *X = *--S->top;

    return OK;
}
//================================================================================================
//遍历栈
//================================================================================================
Status StackShow(stack *S)
{
    ElementType *iterator = S->base;

    if(S->base == S->top)
        return ERROR;

    while( iterator != S->top )
    {
        printf("%d", *iterator);
        ++iterator;
    }
    puts("");

    return OK;
}
//================================================================================================
//返回栈长度
//================================================================================================
int StackLength(stack *S)
{
    return (S->top - S->base);
}
//================================================================================================
//不带头节点的双向链表初始化
//================================================================================================
Status LinklistInit(linklist *L)
{
    L->rear = (position *)malloc(sizeof(listNode));
    if(NULL == L->rear)
        return ERROR;

    L->rear->next = NULL;
    L->rear->front = NULL;
    L->listSize = 0;

    return OK;
}
//================================================================================================
//向双向链表加入元素
//================================================================================================
Status LinklistAdd(linklist *L, listType X)
{
    position *s;
    
    s = (position *)malloc(sizeof(listNode));
    if(NULL == s)
        return ERROR;

    s->data = X;
    s->next = NULL;
    s->front = L->rear;
    L->rear->next = s;
    L->rear = s;
    L->listSize++;

    return OK;
}
//================================================================================================
//遍历链表
//================================================================================================
Status LinklistShow(linklist *L)
{
    position *s;

    s = L->rear;
    while(s != NULL)
    {
        printf("%c", s->data);
        s = s->front;
    }
    puts("");

    return OK;
}
//================================================================================================
//将十进制数转换为二进制，八进制，十六进制
//================================================================================================
Status Convert(int integer)
{
    int tmp;  //临时变量，用来替换integer
    int x;  //弹栈元素
    int y;  //压栈元素
    int quotient; //商
    int surplus;  //余数
    int len1, len2, len4, len6;//len1为栈长度，len2为需要补充的栈长度,len4为S4的长度,len6为S6的长度
    int sum = 0;  //用于八进制
    int sum1 = 0;  //用于十六进制
    int zero = 0;  //用来补充栈长度的
    int i, j;  //跑龙套专用循环变量
    linklist L;   //链表
    stack S1, S2, S3, S4, S5, S6;  //栈
//初始化栈
    StackInit(&S1);
    StackInit(&S2);
    StackInit(&S3);
   //八进制用的
    StackInit(&S4);   
    StackInit(&S5);
   //十六进制用的
    StackInit(&S6);
//初始化链表
    LinklistInit(&L);

    tmp = integer;
//如果输入的是负整数，要将负整数取反
    if(tmp < 0)
    {
        tmp = -tmp;
    }
//这里开始转换成二进制数
//将tmp转换成二进制
    while(tmp > 0)
    {
        quotient = tmp/2;
        surplus = tmp%2;
        StackPush(&S1, &surplus);
        tmp = quotient;
    }
    printf("转换为二进制数为：\n");
//如果是正整数的话，按照一般的输出
    if(integer >= 0)
    {
        while(S1.top != S1.base)
        {
            StackPop(&S1, &x);
            StackPush(&S4, &x);  //S4压栈，后面八进制要用到
            StackPush(&S6, &x);  //S6压栈，后面十六进制用到
            printf("%d", x);
        }
        puts("");
    }
//如果是负整数的话，要将负整数取反再加一
    else
    {
        len1 = StackLength(&S1);
        if(len1 < 32)    //放上32是因为在32位的linux系统下,负整数的二进制是取反再加一
        {
            len2 = 32 - len1;  //求出要填补多少个0
            for(i = 0; i < len2; i++)
            {
                StackPush(&S1, &zero);    //zero恒等于0
            }
        }
//取反操作，0变成1，1变成0
        while(S1.top != S1.base)
        {
            StackPop(&S1,&x);
            if(x == 0)
            {
                x = 1;
                StackPush(&S2, &x);
            }
            else
            {
                x = 0;
                StackPush(&S2, &x);
            }
        }
//加一操作，变成补码,因为负整数的二进制数就是补码
        StackPop(&S2, &x);
        if( (x ^ 1) == 0)    //x为二进制数的最后一个数，测试x是否是1，如果是1，就是将0压进S3，因为1+1 == 0
        {
            y = 0;
            StackPush(&S3, &y);
            while(S2.top != S2.base)
            {                       
                StackPop(&S2, &x);
                if(x == 1)   //再判断二进制数倒数第二个数是否是1，是就将0压进S3中,如此重复，倒数第三位....
                {
                    y = 0;
                    StackPush(&S3, &y);
                }
                else   //碰到S2有一位不是1了，说明只要将1压栈就可以了，其他的不变，直接压栈
                {
                    y = 1;
                    StackPush(&S3, &y);
                    while(S2.top != S2.base)
                    {
                        StackPop(&S2, &x);
                        StackPush(&S3, &x);
                    }
                }
            }
        }
        else   //如果二进制数最后一位不是1的话，就将1压到S3中，其他位数直接压栈
        {
            y = 1;
            StackPush(&S3, &y);
            while(S2.top != S2.base)
            {
                StackPop(&S2, &x);
                StackPush(&S3, &x);
            }
        }
           while(S3.top != S3.base)  //输出二进制数
           {
                StackPop(&S3, &x);
                StackPush(&S4, &x);  //压栈，后面八进制要用到
                StackPush(&S6, &x);  //压栈，后面十六进制要用到
                printf("%d", x);
           }
        puts("");
    }
//这里开始转换为八进制数
    printf("转换为八进制为：\n");
    len4 = StackLength(&S4);
    for(i = 0; i< len4; i += 3)    //3个二进制数为一个八进制数
    {
        for(j = 0; j < 3; j++)
        {
            StackPop(&S4, &x);
            sum = sum + x * (1 << j);

            if(S4.top == S4.base)
            {
                break;
            }
        }
        StackPush(&S5, &sum);
        sum = 0;
    }

    while(S5.top != S5.base)
    {
        StackPop(&S5, &x);
        printf("%d", x);
    }
    puts("");
//这里开始转换为十六进制
    printf("转换为十六进制为:\n");
    len6 = StackLength(&S6);
    for(i = 0; i < len6; i += 4)   //4个二进制数为一个十六进制数
    {
        for(j = 0; j < 4; j++)
        {
            StackPop(&S6, &x);
            sum1 = sum1 + x * (1 << j);
            if(S6.top == S6.base)
            {
                break;
            }
        }
//这里说明一下，没有想到更好的方法了，所以采用switch，因为十六进制中用ABCDEF这些字母，字母为char型，
//而0到9又为int型，所以很难像八进制那样转换，除非再定义一个栈(压栈元素要为char型，跟前面的栈不同，所以很麻烦)，
//没有采用，除非想到泛型算法，不考虑类型
        switch(sum1)
        {
            case 0:
                LinklistAdd(&L, '0'); break;
            case 1:
                LinklistAdd(&L, '1'); break;
            case 2:
                LinklistAdd(&L, '2'); break;
            case 3:
                LinklistAdd(&L, '3'); break;
            case 4:
                LinklistAdd(&L, '4'); break;
            case 5:
                LinklistAdd(&L, '5'); break;
            case 6:
                LinklistAdd(&L, '6'); break;
            case 7:
                LinklistAdd(&L, '7'); break;
            case 8:
                LinklistAdd(&L, '8'); break;
            case 9:
                LinklistAdd(&L, '9'); break;
            case 10:
                LinklistAdd(&L, 'A'); break;
            case 11:
                LinklistAdd(&L, 'B'); break;
            case 12:
                LinklistAdd(&L, 'C'); break;
            case 13:
                LinklistAdd(&L, 'D'); break;
            case 14:
                LinklistAdd(&L, 'E'); break;
            case 15:
                LinklistAdd(&L, 'F'); break;
        }
        sum1 = 0;
    }
    LinklistShow(&L);   //倒序遍历链表

    return OK;
}
//================================================================================================
//主函数
//================================================================================================
int main(int argc, char **argv)
{
    int integer;  //待输入的整数

    printf("请输入要转换的整数\n");
    scanf("%d", &integer);
    Convert(integer);   //十进制转换为二进制,八进制

    return 0;
}
