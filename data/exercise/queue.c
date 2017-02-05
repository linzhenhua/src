/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月18日 17时26分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

#ifndef UINT
#define UINT unsigned int
#endif

typedef int Status;
typedef int ElementType;

typedef struct
{
    ElementType *data;
    int front;
    int rear;
    int queueSize;
}queue;

Status QueueInit(queue *Q, UINT initSize);  //初始换队列
Status Enqueue(queue *Q, ElementType *X);   //入队列
Status Dequeue(queue *Q, ElementType *X);  //出队列
Status QueueShow(queue *Q);   //遍历队列
Status QueueHead(queue *Q, ElementType *X);  //取队头元素（但是不出列）
int QueueLength(queue *Q);  //返回队列长度
Status QueueIsEmpty(queue *Q);   //判断队列是否为空
void QueueDestory(queue *Q);   //销毁队列
//============================================================================================
Status QueueInit(queue *Q, UINT initSize)
{
    initSize++;
    Q->data = (ElementType *)malloc(initSize * sizeof(ElementType));
    if(NULL == Q->data)
        return ERROR;

    Q->front = Q->rear = 0;
    Q->queueSize = initSize;

    return OK;
}
//=============================================================================================
Status Enqueue(queue *Q, ElementType *X)
{
    if( (Q->rear + 1) % Q->queueSize == Q->front )
        return ERROR;

    Q->data[Q->rear] = *X;
    Q->rear = (Q->rear + 1) % Q->queueSize;

    return OK;
}
//=============================================================================================
Status Dequeue(queue *Q, ElementType *X)
{
    if(Q->front == Q->rear)
        return ERROR;

    *X = Q->data[Q->front];

    Q->front = (Q->front + 1) % Q->queueSize;

    return OK;
}
//=============================================================================================
Status QueueShow(queue *Q)
{
    ElementType tmp = Q->front;

    if(Q->front == Q->rear)
        return ERROR;

    while(tmp != Q->rear)
    {
        printf("%d->", Q->data[tmp]);
        tmp = (tmp + 1) % Q->queueSize;
    }
    puts("NULL");

    return OK;
}
//==============================================================================================
Status QueueHead(queue *Q, ElementType *X)
{
    if(Q->front == Q->rear)
        return ERROR;

    *X = Q->data[Q->front];

    return OK;
}
//==============================================================================================
int QueueLength(queue *Q)
{
    return (Q->rear - Q->front + Q->queueSize) % Q->queueSize;
}
//==============================================================================================
Status QueueIsEmpty(queue *Q)
{
    return Q->front == Q->rear;
}
//==============================================================================================
void QueueDestory(queue *Q)
{
    free(Q->data);
    Q->front = Q->rear = Q->queueSize = 0;
}
//==============================================================================================
int main(int argc, char **argv)
{
    queue Q;
    int num;
    int len;

    QueueInit(&Q, 32);
    printf("请输入要入队列的元素:,按0结束\n");
    scanf("%d", &num);
    while(num != 0)
    {
        Enqueue(&Q, &num);
        scanf("%d", &num);
    }
    len = QueueLength(&Q);
    printf("队列长度为%d\n", len);
    QueueShow(&Q);

    Dequeue(&Q, &num);
    QueueShow(&Q);

    return 0;
}
