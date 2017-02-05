/******************************************************************************
*    > File Name: queue.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月25日 星期五 20时44分42秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include "BSTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*初始化队列*/
status initQueue(queue *Q, UINT initSize)
{
    initSize++;
    Q->data = (elementType *)malloc(initSize * sizeof(elementType));
    if(NULL == Q->data)
    {
        return ERROR;
    }

    Q->front = Q->rear = 0;
    Q->size = initSize;

    return OK;
}

/*入队列*/
status enQueue(queue *Q, elementType *X)
{
    if( (Q->rear + 1) % Q->size == Q->front )
    {
        return ERROR;
    }

    Q->data[Q->rear] = *X;
    Q->rear = (Q->rear + 1) % Q->size;   //指向下一个元素

    return OK;
}

/*出队列*/
status deQueue(queue *Q, elementType *X)
{
    if( Q->front == Q->rear )
    {
        return ERROR;
    }

    *X = Q->data[Q->front];
    Q->front = (Q->front + 1) % Q->size;     //指向下一个元素

    return OK;
}

/*判断队列是否为空*/
BOOL isEmptyQueue(queue *Q)
{
    return Q->front == Q->rear;
}

/*遍历队列*/
status queueShow(queue *Q)
{
    int tmp = Q->front;

    if( Q->front == Q->rear )
        return ERROR;

    while(tmp != Q->rear)
    {
        printf("%d->", Q->data[tmp].data);
        tmp = (tmp + 1) % Q->size;
    }
    printf("NULL\n");

    return OK;
}

/*销毁队列*/
void destroyQueue(queue *Q)
{
    free(Q->data);
    Q->front = Q->rear = Q->size = 0;
}
