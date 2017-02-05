/******************************************************************************
*    > File Name: BSTree.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月24日 星期四 20时29分21秒
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

/*主函数*/
int main(int argc, char **argv)
{
    BSTNode *T = NULL;      //初始化树
    int tmp;                //临时变量
    int n;                  //树的节点的个数
    int i;                  //循环变量

    printf("请输入要创建树的节点的个数:\n");
    scanf("%d", &n);

    for(i = 0; i < n; ++i)
    {
        scanf("%d", &tmp);
        T = insert(T, tmp);      //建立树
    }
    printf("\n");

    printf("中序遍历结果为:\n");
    inSearchTreeShow(T);
    printf("\n");

    printf("前序遍历结果为:\n");
    preSearchTreeShow(T);
    printf("\n");

    printf("后序遍历结果为:\n");
    postSearchTreeShow(T);
    printf("\n");

    printf("层序遍历结果为:\n");
    levelSearchTreeShow(T);
    printf("\n");

    destroyTree(T);    //释放树

    return 0;
}

/*插入操作*/
BSTNode *insert(BSTNode *T, int X)
{
    if(NULL == T)
    {
        T = (BSTNode *)malloc(sizeof(BSTNode));
        if(NULL == T)
        {
            exit(1);
        }
        else
        {
            T->data = X;
            T->left = T->right = NULL;
        }
    }
    else if(X < T->data)
    {
        T->left = insert(T->left, X);
    }
    else if(X > T->data)
    {
        T->right = insert(T->right, X);
    }

    return T;
}

/*中序遍历二叉查找树*/
/*左，节点，右*/
void inSearchTreeShow(BSTNode *T)
{
    if(NULL != T)
    {
        inSearchTreeShow(T->left);
        printf("%d ", T->data);
        inSearchTreeShow(T->right);
    }
}

/*前序遍历二叉查找树*/
/*节点，左，右*/
void preSearchTreeShow(BSTNode *T)
{
    if(NULL != T)
    {
        printf("%d ", T->data);
        preSearchTreeShow(T->left);
        preSearchTreeShow(T->right);
    }
}

/*后序遍历二叉查找树*/
/*左，右，节点*/
void postSearchTreeShow(BSTNode *T)
{
    if(NULL != T)
    {
        postSearchTreeShow(T->left);
        postSearchTreeShow(T->right);
        printf("%d ", T->data);
    }
}

/*层序遍历二叉查找树*/
void levelSearchTreeShow(BSTNode *T)
{
    queue Q;
    int size = 100;
    BSTNode *node = NULL;

    if( !initQueue(&Q, size) )    //初始化队列
    {
        printf("initQueue error\n");
        exit(-1);
    }

    if(NULL != T)
    {
        enQueue(&Q, T);         //入队列
    }

    while( !isEmptyQueue(&Q) )
    {
        deQueue(&Q, T);
        node = T;                   //这一步很关键，能使树不断指向下一个元素

        printf("%d ", node->data);

        if( NULL != node->left )
        {
            enQueue(&Q, node->left);
        }
        if( NULL != node ->right )
        {
            enQueue(&Q, T->right);
        }
    }

    destroyQueue(&Q);           //记得释放队列
}

/*销毁二叉查找树*/
void destroyTree(BSTNode *T)
{
    if(NULL != T)
    {
        if(NULL != T->left)
        {
            destroyTree(T->left);
        }
        if(NULL != T->right)
        {
            destroyTree(T->right);
        }
    }
    free(T);
    T = NULL;
}
