#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

Status initStack(stack *S)
{
    S->top = S->base = (ElementType *)malloc(STACKINITSIZE * sizeof(ElementType));
    if(NULL == S->top)
        return ERROR;

    S->stackSize = STACKINITSIZE;

    return OK;
}

Status stackPop(stack *S, ElementType *X)
{
    if(S->base == S->top)
        return ERROR;

    *X = --*S->top;

    return OK;
}

Status stackPush(stack *S, ElementType *X)
{
    if(S->top - S->base >= S->stackSize)
    {
        S->base = (ElementType *)realloc(S->base, (S->stackSize + STACKEXTENDSIZE) * sizeof(ElementType));
        if(NULL == S->base)
            return  ERROR;

        S->top = S->base + S->stackSize;
        S->stackSize += STACKEXTENDSIZE; 
    }

    *S->top++ = *X;

    return OK;
}

void stackDestroy(stack *S)
{
    free(S->base);
    S->base = S->top = NULL;
    S->stackSize = 0;
}
