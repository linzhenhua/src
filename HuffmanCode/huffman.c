#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*
 *=============================================================================
 *��Ȩ�ؽ���ͳ�ƣ����Ƕ�������ַ����ִ���ͳ��,���ڵ㰴Ȩֵ��С����������
 *=============================================================================
*/
Status selectWeight(linkQueue *Q, char *inputString)
{
    int *probability;    //����ͳ���ַ������ֵĴ���
    int i, j;  //ѭ������
    huffmanNode *tmp;  //�������ṹ����ʱ����

    probability = (int *)malloc(sizeof(int)*256 );   //�����ڴ�
    if(NULL == probability)
        return ERROR;

    memset(probability, 0, sizeof(int)*256);   //��problilty��Ԫ������Ϊ0

    for(i = 0; inputString[i] != '\0'; i++)   //ͳ�������ַ������ַ����ֵĴ���
    {  //����˵:I���ַ����г����ˣ���ôprobability[I]++,������Ӧ��ACSII��I��λ��+1
        probability[(unsigned char)inputString[i]]++;
    }

    for(j = 0; j < 256; j++)           //�Գ��ֵ��ַ������ڴ�
    {
        if(probability[j] != 0)
        {
            tmp = (huffmanNode *)malloc(sizeof(huffmanNode));
            if(NULL == tmp)
            return ERROR;

            tmp->symbol = (char)j;     //���ַ�j�ŵ�tmp->symbol
            tmp->weight = probability[j];  //Ȩ��Ϊprobability[j]
            tmp->left = NULL;
            tmp->right = NULL;

            orderEnQueue(Q, tmp);  //���

            free(tmp);   //�ͷ��ڴ�
            tmp = NULL;
        }
    }

    free(probability);   //�ͷ��ڴ�
    probability = NULL;

    return OK;
}

/*
 *=============================================================================
 *����huffman��
 *=============================================================================
*/
huffmanNode* createHuffmanTree(linkQueue *Q)
{
    huffmanNode *left, *right, *current;
    huffmanNode *huffmantree;

    while(Q->queueSize != 1)   //������1����Ϊ�ڶ���Ҫ���һ����������ʱ��������
    {
        left = deQueue(Q);
        right = deQueue(Q);

        current = (huffmanNode *)malloc(sizeof(huffmanNode));
        if(NULL == current)
            exit(-1);

        current->weight = left->weight + right->weight;  //�½ڵ��Ȩ�ص�����������Ȩ�����
        current->left = left;
        current->right = right;
        strcpy(current->code, "");    //warning:��strcpy��������г�ʼ��,����ı���ǵ��ȳ�ʼ������Ȼ����ı���ͻ�������

        orderEnQueue(Q, current);

        free(current);
        current = NULL;
    }

    huffmantree = deQueue(Q);  //��ʱ����о�ֻ��һ���ڵ��ˣ����ظ�huffman��

    return huffmantree;
}

/*
 *=============================================================================
 *huffman����
 *=============================================================================
*/
Status huffmanCode(huffmanNode *root, char *stringToCode, char *inputString)
{
    int i = 0, j;   //ר��ѭ������
    huffmanNode *current = NULL;
    linkQueue Q;
    storeCode *array;   //���ڴ��huffman�������

    array = (storeCode *)malloc(sizeof(storeCode)*256);    //�����ڴ�
    if(NULL == array)
    return ERROR;

    queueInit(&Q);  //��ʼ��huffman������

    enQueue(&Q, root);   //���������

    while(isEmpty(&Q))    //�ж϶����Ƿ�Ϊ��
    {
        current = deQueue(&Q);

        if(current->left == NULL && current->right == NULL)   //�����������������������Ϊ�գ���˵����������Ҷ����
        {
            printf("����:%c,Ȩ��:%d,����:%s\n", current->symbol,current->weight, current->code);
            array[i].symbol = current->symbol;  //��������ַ��ŵ���������
            array[i].weight = current->weight;  //�������Ȩ�طŵ���������
            array[i].code = current->code;      //������ı���ŵ���������,����Ҫ�õ�
            i++;
        }
        if(current->left != NULL)
        {
            strcpy(current->left->code, current->code);   //�Ѹ��ڵ�ı��븴�Ƶ��ӽڵ㣬�����ſ��԰Ѹ��ڵ�ı���̳���ȥ
            strcat(current->left->code, "0");   //��Ϊ�ڵ�����ߣ����԰�'0'�ŵ��ڵ���

            enQueue(&Q, current->left);
        }
        if(current->right != NULL)
        {
            strcpy(current->right->code, current->code);  //�Ѹ��ڵ�ı��븴�Ƶ��ӽڵ㣬�����ſ��԰Ѹ��ڵ�ı���̳���ȥ
            strcat(current->right->code, "1");   //��Ϊ�ڵ����ұߣ����԰�'1'�ŵ��ڵ���

            enQueue(&Q, current->right);
        }
    }

    for(i = 0, j = 0; ; i++)
    {
        if(array[i].symbol == inputString[j])
        {
            strcat(stringToCode, array[i].code);   //����õ�����strcat��������
            if(strlen(stringToCode) >= MAXSIZE)     //��ֹstringToCode������
            {
                stringToCode = realloc(stringToCode, (MAXSIZE + EXTENDSIZE)*sizeof(char));
                if(NULL == stringToCode)
                return  ERROR;
            }

            i = -1;   //-1����Ϊfor�����i++,���0
            j++;
            if(inputString[j] == '\0')  //���������ַ�����β��Ҫ������,��Ȼ������ȥ�ͻ��������
            {
                break;
            }
        }
    }
    free(array);
    array = NULL;

    for(i = 0; stringToCode[i] != '\0'; i++)   //���huffman����
    {
        printf("%c", stringToCode[i]);
    }
    puts("");

    return OK;
}

/*
 *=============================================================================
 *huffman����
 *ԭ��������0ʱ�����ߣ�����1ʱ�����ߣ�ֱ������Ҷ�ӽڵ�Ͷ�����Ӧ�ķ���
 *=============================================================================
*/
Status huffmandeCode(huffmanNode *T, char *stringToDecode)
{
    int i;   //ѭ������
    huffmanNode *tmp;  //��ʱ����

    tmp = T;

    for(i = 0; stringToDecode[i] != '\0'; i++)
    {
        if(stringToDecode[i] == '0')  //������
        {
            tmp = tmp->left;
        }
        if(stringToDecode[i] == '1')  //������
        {
            tmp = tmp->right;
        }
        if(NULL == tmp->left && NULL == tmp->right)  //����Ҷ�ӽڵ㣬�����Ӧ���ַ�
        {
            printf("%c", tmp->symbol);
            tmp = T;
        }
        if(stringToDecode[i] != '0' || stringToDecode[i] != '1')  //��ֹ�������
        {
            continue;
        }
    }
    if(NULL == tmp->left && NULL == tmp->right)   //����Ҷ�ӽڵ㲢��������ַ����Ҫ�ص������ټ���
    {
        printf("%c", tmp->symbol);
        tmp = T;
    }

    return OK;
}

/*
 *=============================================================================
 *�ݹ����huffman��(test�õ�)
 *=============================================================================
*/
Status huffmanShow(huffmanNode *T)
{
    if(T != NULL)
    {
        huffmanShow(T->left);   //����������
        printf("%c\t", T->symbol);  //��ӡȨ��
        huffmanShow(T->right);  //����������
    }

    return OK;
}
