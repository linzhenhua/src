#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*
 *============================================================================
 *初始化huffman树队列
 *============================================================================
*/
Status queueInit(linkQueue *Q)
{
    Q->front = (queueNode *)malloc(sizeof(queueNode));
    if(NULL == Q->front)
    return ERROR;

    Q->rear = Q->front;
    Q->rear->next = NULL;
    Q->queueSize = 0;

    return OK;
}
/*
 *============================================================================
 *入队列
 *============================================================================
*/
Status enQueue(linkQueue *Q, ElementType *X)
{
    queueNode *tmp;

    tmp = (queueNode *)malloc(sizeof(queueNode));
    if(NULL == tmp)
    return ERROR;

    tmp->data = *X;
    tmp->next = NULL;
    Q->rear->next = tmp;
    Q->rear = tmp;
    Q->queueSize++;

    return OK;
}
/*
 *============================================================================
 *出队列
 *============================================================================
*/
huffmanNode* deQueue(linkQueue *Q)
{
    queueNode *tmp;
    huffmanNode *val;

    if(Q->front == Q->rear)
    {
        printf("队列为空，出队失败\n");
        exit(-1);
    }

    val = (huffmanNode *)malloc(sizeof(huffmanNode));
    if(NULL == val)
        exit(-1);

    tmp = Q->front->next;
    *val = tmp->data;
    Q->front->next = tmp->next;
    if(Q->rear == tmp)   //如果只有一个元素
        Q->rear = Q->front;   //重置尾指针
    Q->queueSize--;
    free(tmp);
    tmp = NULL;

    return val;
}

/*
 *============================================================================
 *判断队列是否为空
 *============================================================================
*/
Status isEmpty(linkQueue *Q)
{
    if(Q->front == Q->rear)
    return FALSE;
    else
    return TRUE;
}

/*
 *============================================================================
 *遍历队列
 *============================================================================
*/
Status queueShow( linkQueue *Q )
{
    queueNode *p;

	if( Q->front == Q->rear )
		return ERROR;

	p = Q->front->next;
	while( p != NULL)
	{
		printf("%c", p->data.symbol );
		p = p->next ;
	}
	puts("");

	return OK;
}

/*
 *============================================================================
 *销毁队列
 *============================================================================
*/
void queueDestroy(linkQueue *Q)
{
    queueNode *tmp;

    tmp = Q->front->next;
    Q->front->next = NULL;
    while(tmp != NULL)
    {
        Q->rear = tmp->next;
        free(tmp);
        tmp = NULL;
        tmp = Q->rear;
    }
    Q->queueSize = 0;
}
/*
 *============================================================================
 *由小到大排序的入队列(画图出来很好理解的)
 *============================================================================
*/
Status orderEnQueue(linkQueue *Q, ElementType *X)
{
    queueNode *tmp;
    queueNode *iterator;

    tmp = (queueNode *)malloc(sizeof(queueNode));  //分配内存
    if(NULL == tmp)
    return ERROR;

    tmp->data = *X;
    if(NULL == Q->front->next || 0 == Q->queueSize)   //第一个元素入队列，直接插入就可以了
    {
        tmp->next = NULL;
        Q->rear->next = tmp;
        Q->rear = tmp;
        Q->queueSize++;
    }
    else
    {
        if(tmp->data.weight <= Q->front->next->data.weight)   //已经有了第一个元素的情况,在头节点front和front后一个
        {                                                     ////元素直接插入tmp
            tmp->next = Q->front->next;     //这两句千万记得
            Q->front->next = tmp;           //不要搞反了,会死循环的!!!!!!!!!!
            Q->queueSize++;
        }
        else
        {
            iterator = Q->front->next;
            while(iterator->next != NULL)
            {
                if(tmp->data.weight <= iterator->next->data.weight)  //比较中间的元素的权重大小
                {
                    tmp->next = iterator->next;
                    iterator->next = tmp;
                    Q->queueSize++;

                    return OK;
                }
                iterator = iterator->next;
            }
            if(NULL == iterator->next)  //在队尾直接插入
            {
                iterator->next = tmp;
                tmp->next = NULL;
                Q->rear = tmp;
                Q->queueSize++;
            }
        }
    }

    return OK;
}
