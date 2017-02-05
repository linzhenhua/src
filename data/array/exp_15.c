/*
 * =====================================================================================
 *
 *       Filename:  exp_15.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月16日 09时08分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//输入任意个数，求出最大值，最小值，平均值，用数据结构实现
#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE -1

typedef int Status;
typedef float ElementType;

typedef struct listNode
{
    ElementType data;
    struct listNode *next;
}listNode, position;

typedef struct 
{
    position *head;
    position *rear;
    int length;
}linklist;

Status LinklistInit(linklist *L);  //初始化链表
Status LinklistAdd(linklist *L, ElementType *X);  //向链表加入元素
Status LinklistShow(linklist *L);   //遍历链表
/*
 *=======================================================================================
 *初始化链表
 * ======================================================================================
 */
Status LinklistInit(linklist *L)
{
    L->head = (position *)malloc( sizeof(listNode) );
    if(NULL == L->head)
    return ERROR;

    L->rear = L->head;
    L->rear->next = NULL;
    L->length = 0;

    return OK;
}
/*
 *=======================================================================================
 *向链表加入元素
 * ======================================================================================
 */
Status LinklistAdd(linklist *L, ElementType *X)
{
    position *s;
    s = (position *)malloc( sizeof(listNode) );
    if(NULL == s)
        return ERROR;

    s->data = *X;
    s->next = NULL;
    L->rear->next = s;
    L->rear = s;
    L->length++;

    return OK;
}

/*
 *======================================================================================
 *遍历链表
 * =====================================================================================
 */
Status LinklistShow(linklist *L)
{
    position *s;
    s = L->head->next;

    while(s != NULL)
    {
        printf("%f->", s->data);
        s = s->next;
    }
    puts("NULL");

    return OK;
}
/*
 *======================================================================================
 *比较函数
 *=====================================================================================
 */
int compare(linklist *L)
{
    int count;
    float sum, ave, max, min;
    position *num;
    count = 0;
    sum = 0;
    num = L->head->next;
    max = min = num->data;
    while(num != NULL)
    {
        sum +=num->data;
        if( max <= num->data)
        {
            max = num->data;
        }
        if(min >= num->data)
        {
            min = num->data;
        }
        ++count;
        num = num->next;
    }
    ave = sum/count;

    printf("一共输入%d个数\n最大的数为%f\n最小的数为%f\n", count, max, min);
    printf("平均值为%.2f\n", ave);

    return 0;
}

/*
 *======================================================================================
 *主函数
 * =====================================================================================
 */
int main(int argc, char **argv)
{
    linklist L;
    float num;

    LinklistInit(&L);

    printf("请输入任意个数：\n");
    scanf("%f", &num);
    while(num != 0)
    {
        LinklistAdd(&L, &num);
        scanf("%f", &num);
    }
    LinklistShow(&L);

    compare(&L);

    return 0;
}
