#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*
 *============================================================================
 *��ʼ��huffman������
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
 *�����
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
 *������
 *============================================================================
*/
huffmanNode* deQueue(linkQueue *Q)
{
    queueNode *tmp;
    huffmanNode *val;

    if(Q->front == Q->rear)
    {
        printf("����Ϊ�գ�����ʧ��\n");
        exit(-1);
    }

    val = (huffmanNode *)malloc(sizeof(huffmanNode));
    if(NULL == val)
        exit(-1);

    tmp = Q->front->next;
    *val = tmp->data;
    Q->front->next = tmp->next;
    if(Q->rear == tmp)   //���ֻ��һ��Ԫ��
        Q->rear = Q->front;   //����βָ��
    Q->queueSize--;
    free(tmp);
    tmp = NULL;

    return val;
}

/*
 *============================================================================
 *�ж϶����Ƿ�Ϊ��
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
 *��������
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
 *���ٶ���
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
 *��С��������������(��ͼ�����ܺ�����)
 *============================================================================
*/
Status orderEnQueue(linkQueue *Q, ElementType *X)
{
    queueNode *tmp;
    queueNode *iterator;

    tmp = (queueNode *)malloc(sizeof(queueNode));  //�����ڴ�
    if(NULL == tmp)
    return ERROR;

    tmp->data = *X;
    if(NULL == Q->front->next || 0 == Q->queueSize)   //��һ��Ԫ������У�ֱ�Ӳ���Ϳ�����
    {
        tmp->next = NULL;
        Q->rear->next = tmp;
        Q->rear = tmp;
        Q->queueSize++;
    }
    else
    {
        if(tmp->data.weight <= Q->front->next->data.weight)   //�Ѿ����˵�һ��Ԫ�ص����,��ͷ�ڵ�front��front��һ��
        {                                                     ////Ԫ��ֱ�Ӳ���tmp
            tmp->next = Q->front->next;     //������ǧ��ǵ�
            Q->front->next = tmp;           //��Ҫ�㷴��,����ѭ����!!!!!!!!!!
            Q->queueSize++;
        }
        else
        {
            iterator = Q->front->next;
            while(iterator->next != NULL)
            {
                if(tmp->data.weight <= iterator->next->data.weight)  //�Ƚ��м��Ԫ�ص�Ȩ�ش�С
                {
                    tmp->next = iterator->next;
                    iterator->next = tmp;
                    Q->queueSize++;

                    return OK;
                }
                iterator = iterator->next;
            }
            if(NULL == iterator->next)  //�ڶ�βֱ�Ӳ���
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
