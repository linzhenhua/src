#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*
 *=============================================================================
 *对权重进行统计，就是对输入的字符出现次数统计,将节点按权值从小到大放入队列
 *=============================================================================
*/
Status selectWeight(linkQueue *Q, char *inputString)
{
    int *probability;    //用来统计字符串出现的次数
    int i, j;  //循环变量
    huffmanNode *tmp;  //具有树结构的临时变量

    probability = (int *)malloc(sizeof(int)*256 );   //分配内存
    if(NULL == probability)
        return ERROR;

    memset(probability, 0, sizeof(int)*256);   //将problilty的元素重置为0

    for(i = 0; inputString[i] != '\0'; i++)   //统计输入字符串的字符出现的次数
    {  //比如说:I在字符串中出现了，那么probability[I]++,就在相应的ACSII上I的位置+1
        probability[(unsigned char)inputString[i]]++;
    }

    for(j = 0; j < 256; j++)           //对出现的字符分配内存
    {
        if(probability[j] != 0)
        {
            tmp = (huffmanNode *)malloc(sizeof(huffmanNode));
            if(NULL == tmp)
            return ERROR;

            tmp->symbol = (char)j;     //将字符j放到tmp->symbol
            tmp->weight = probability[j];  //权重为probability[j]
            tmp->left = NULL;
            tmp->right = NULL;

            orderEnQueue(Q, tmp);  //入队

            free(tmp);   //释放内存
            tmp = NULL;
        }
    }

    free(probability);   //释放内存
    probability = NULL;

    return OK;
}

/*
 *=============================================================================
 *创建huffman树
 *=============================================================================
*/
huffmanNode* createHuffmanTree(linkQueue *Q)
{
    huffmanNode *left, *right, *current;
    huffmanNode *huffmantree;

    while(Q->queueSize != 1)   //不等于1是因为在队列要存放一个树根，到时候函数返回
    {
        left = deQueue(Q);
        right = deQueue(Q);

        current = (huffmanNode *)malloc(sizeof(huffmanNode));
        if(NULL == current)
            exit(-1);

        current->weight = left->weight + right->weight;  //新节点的权重等于左右子树权重相加
        current->left = left;
        current->right = right;
        strcpy(current->code, "");    //warning:用strcpy对数组进行初始化,输出的编码记得先初始化，不然后面的编码就会有乱码

        orderEnQueue(Q, current);

        free(current);
        current = NULL;
    }

    huffmantree = deQueue(Q);  //这时候队列就只有一个节点了，返回给huffman树

    return huffmantree;
}

/*
 *=============================================================================
 *huffman编码
 *=============================================================================
*/
Status huffmanCode(huffmanNode *root, char *stringToCode, char *inputString)
{
    int i = 0, j;   //专用循环变量
    huffmanNode *current = NULL;
    linkQueue Q;
    storeCode *array;   //用于存放huffman树编码的

    array = (storeCode *)malloc(sizeof(storeCode)*256);    //分配内存
    if(NULL == array)
    return ERROR;

    queueInit(&Q);  //初始化huffman树队列

    enQueue(&Q, root);   //把树根入队

    while(isEmpty(&Q))    //判断队列是否为空
    {
        current = deQueue(&Q);

        if(current->left == NULL && current->right == NULL)   //如果树的左子树和右子树都为空，就说明到了树的叶子了
        {
            printf("符号:%c,权重:%d,编码:%s\n", current->symbol,current->weight, current->code);
            array[i].symbol = current->symbol;  //将输出的字符放到数组里面
            array[i].weight = current->weight;  //将输出的权重放到数组里面
            array[i].code = current->code;      //将输出的编码放到数组里面,后面要用的
            i++;
        }
        if(current->left != NULL)
        {
            strcpy(current->left->code, current->code);   //把父节点的编码复制到子节点，这样才可以把父节点的编码继承下去
            strcat(current->left->code, "0");   //因为节点在左边，所以把'0'放到节点上

            enQueue(&Q, current->left);
        }
        if(current->right != NULL)
        {
            strcpy(current->right->code, current->code);  //把父节点的编码复制到子节点，这样才可以把父节点的编码继承下去
            strcat(current->right->code, "1");   //因为节点在右边，所以把'1'放到节点上

            enQueue(&Q, current->right);
        }
    }

    for(i = 0, j = 0; ; i++)
    {
        if(array[i].symbol == inputString[j])
        {
            strcat(stringToCode, array[i].code);   //将编好的码用strcat连接起来
            if(strlen(stringToCode) >= MAXSIZE)     //防止stringToCode不够大
            {
                stringToCode = realloc(stringToCode, (MAXSIZE + EXTENDSIZE)*sizeof(char));
                if(NULL == stringToCode)
                return  ERROR;
            }

            i = -1;   //-1是因为for那里会i++,变成0
            j++;
            if(inputString[j] == '\0')  //到了输入字符串的尾就要结束了,不然进行下去就会有乱码的
            {
                break;
            }
        }
    }
    free(array);
    array = NULL;

    for(i = 0; stringToCode[i] != '\0'; i++)   //输出huffman编码
    {
        printf("%c", stringToCode[i]);
    }
    puts("");

    return OK;
}

/*
 *=============================================================================
 *huffman解码
 *原理：当遇到0时向左走，遇到1时向右走，直到遇到叶子节点就读出相应的符号
 *=============================================================================
*/
Status huffmandeCode(huffmanNode *T, char *stringToDecode)
{
    int i;   //循环变量
    huffmanNode *tmp;  //临时变量

    tmp = T;

    for(i = 0; stringToDecode[i] != '\0'; i++)
    {
        if(stringToDecode[i] == '0')  //向左走
        {
            tmp = tmp->left;
        }
        if(stringToDecode[i] == '1')  //向右走
        {
            tmp = tmp->right;
        }
        if(NULL == tmp->left && NULL == tmp->right)  //到了叶子节点，输出相应的字符
        {
            printf("%c", tmp->symbol);
            tmp = T;
        }
        if(stringToDecode[i] != '0' || stringToDecode[i] != '1')  //防止编码错误
        {
            continue;
        }
    }
    if(NULL == tmp->left && NULL == tmp->right)   //到了叶子节点并且输出完字符后就要回到树根再继续
    {
        printf("%c", tmp->symbol);
        tmp = T;
    }

    return OK;
}

/*
 *=============================================================================
 *递归遍历huffman树(test用的)
 *=============================================================================
*/
Status huffmanShow(huffmanNode *T)
{
    if(T != NULL)
    {
        huffmanShow(T->left);   //遍历左子树
        printf("%c\t", T->symbol);  //打印权重
        huffmanShow(T->right);  //遍历右子树
    }

    return OK;
}
