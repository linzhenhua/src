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
 *huffman树节点
 *=============================================================================
*/
typedef struct _huffmanNode
{
    UINT weight;   //权重
    char symbol;        //符号
    char code[8];   //编码
    struct _huffmanNode *left;  //左子树
    struct _huffmanNode *right; //右子树
}huffmanNode;   //树节点的具体内容
/*
 *=============================================================================
 *链队列，用于存放huffman树节点
 *=============================================================================
*/
typedef huffmanNode ElementType;

typedef struct _queueNode
{
    ElementType data;  //具有树节点的元素
    struct _queueNode *next;
}queueNode;   //队列节点的具体内容

typedef struct
{
    queueNode *front;   //队头
    queueNode *rear;    //队尾
    int queueSize;      //当前队列的大小
}linkQueue;  //链队列
/*
 *============================================================================
 *这个节点用于存放huffman树编码
 *============================================================================
*/
typedef struct
{
    char symbol;   //存放符号
    UINT weight;   //权重
    char *code;    //编码
}storeCode;
/*===========================================================================*/
Status selectWeight(linkQueue *Q, char *inputString);//对权重进行统计，就是对输入的字符出现次数统计,将节点按权值从小到大放入队列
huffmanNode* createHuffmanTree(linkQueue *Q);   //创建haffman树
Status huffmanCode(huffmanNode *root, char *stringToCode, char *inputString);  //huffman编码
Status huffmandeCode(huffmanNode *T, char *stringToDecode);    //huffman解码
Status huffmanShow(huffmanNode *T);  //递归遍历huffman树

Status queueInit(linkQueue *Q);   //初始化队列
Status enQueue(linkQueue *Q, ElementType *X);  //入队
huffmanNode* deQueue(linkQueue *Q);  //出队
Status isEmpty(linkQueue *Q);  //判断队列是否为空
Status queueShow( linkQueue *Q );   //遍历队列
void queueDestroy(linkQueue *Q);  //销毁队列
Status orderEnQueue(linkQueue *Q, ElementType *X);   //由小到大排序入队

#endif
