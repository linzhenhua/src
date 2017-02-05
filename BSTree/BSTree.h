/******************************************************************************
*    > File Name: BSTree.h
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月25日 星期五 21时22分42秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#pragma once
#ifndef BSTREE_H
#define BSTREE_H

/*宏定义*/
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define UINT unsigned int
#define BOOL int

//二叉查找树的声明
typedef struct BSTNode
{
    int data;               //关键字
    struct BSTNode *left;   //左子树
    struct BSTNode *right;  //右子树
}BSTNode;

/*队列的声明*/
typedef int status;
typedef BSTNode elementType;

typedef struct
{
    elementType *data;         //动态分配队列的存储空间
    int front;                 //队头位置标识
    int rear;                  //队尾位置标识
    int size;                  //队列大小
}queue;

status initQueue(queue *Q, UINT initSize);      //初始化队列
status enQueue(queue *Q, elementType *X);       //入队列
status deQueue(queue *Q, elementType *X);       //出队列
BOOL isEmptyQueue(queue *Q);                    //判断队列是否为空
status queueShow(queue *Q);                     //遍历队列
void destroyQueue(queue *Q);                    //销毁队列

BSTNode *insert(BSTNode *T, int X);             //向二叉查找树插入元素
void inSearchTreeShow(BSTNode *T);              //中序遍历二叉查找树
void preSearchTreeShow(BSTNode *T);             //前序遍历二叉查找树
void postSearchTreeShow(BSTNode *T);            //后序遍历二叉查找树
void levelSearchTreeShow(BSTNode *T);           //层序遍历二叉查找树
void destroyTree(BSTNode *T);                   //销毁二叉查找树

#endif
