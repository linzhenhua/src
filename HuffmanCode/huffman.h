#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#define UINT unsigned int
#define MAXSIZE  100
#define EXTENDSIZE 4

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef int Status;
/*
 *=============================================================================
 *huffman���ڵ�
 *=============================================================================
*/
typedef struct _huffmanNode
{
    UINT weight;   //Ȩ��
    char symbol;        //����
    char code[8];   //����
    struct _huffmanNode *left;  //������
    struct _huffmanNode *right; //������
}huffmanNode;   //���ڵ�ľ�������
/*
 *=============================================================================
 *�����У����ڴ��huffman���ڵ�
 *=============================================================================
*/
typedef huffmanNode ElementType;

typedef struct _queueNode
{
    ElementType data;  //�������ڵ��Ԫ��
    struct _queueNode *next;
}queueNode;   //���нڵ�ľ�������

typedef struct
{
    queueNode *front;   //��ͷ
    queueNode *rear;    //��β
    int queueSize;      //��ǰ���еĴ�С
}linkQueue;  //������
/*
 *============================================================================
 *����ڵ����ڴ��huffman������
 *============================================================================
*/
typedef struct
{
    char symbol;   //��ŷ���
    UINT weight;   //Ȩ��
    char *code;    //����
}storeCode;
/*===========================================================================*/
Status selectWeight(linkQueue *Q, char *inputString);//��Ȩ�ؽ���ͳ�ƣ����Ƕ�������ַ����ִ���ͳ��,���ڵ㰴Ȩֵ��С����������
huffmanNode* createHuffmanTree(linkQueue *Q);   //����haffman��
Status huffmanCode(huffmanNode *root, char *stringToCode, char *inputString);  //huffman����
Status huffmandeCode(huffmanNode *T, char *stringToDecode);    //huffman����
Status huffmanShow(huffmanNode *T);  //�ݹ����huffman��

Status queueInit(linkQueue *Q);   //��ʼ������
Status enQueue(linkQueue *Q, ElementType *X);  //���
huffmanNode* deQueue(linkQueue *Q);  //����
Status isEmpty(linkQueue *Q);  //�ж϶����Ƿ�Ϊ��
Status queueShow( linkQueue *Q );   //��������
void queueDestroy(linkQueue *Q);  //���ٶ���
Status orderEnQueue(linkQueue *Q, ElementType *X);   //��С�����������

#endif
