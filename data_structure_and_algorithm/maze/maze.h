#pragma once
#ifndef MAZE_H
#define MAZE_H

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define STACKINITSIZE 100
#define STACKEXTENDSIZE 10

typedef int Status;
typedef int ElementType;

typedef struct
{
    ElementType *base;
    ElementType *top;
    int stackSize;
}stack;

Status initStack(stack *S);                 //初始化栈
Status stackPop(stack *S, ElementType *X);  //弹栈
Status stackPush(stack *S, ElementType *X); //压栈
void stackDestroy(stack *S);                //销毁栈

#endif
