#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char *argv[])
{
    int i;
    char string[] = "we love fishc!!";   //Ҫ������ַ���(ֻ�ܱ�ASCII�룬���ĵĻ���Ȼ�����룬���ǲ�֪�����ı���)
    char *stringToCode = NULL;  //������ű����
    linkQueue Q;     //����һ��huffman������
    huffmanNode *huffmantree = NULL;   //����һ��huffman���ڵ�

    huffmantree = (huffmanNode *)malloc(sizeof(huffmanNode));    //��ʼ��
    if(NULL == huffmantree)
    exit(-1);

    stringToCode = (char *)malloc(MAXSIZE*sizeof(char));  //�����ڴ��С
    if(NULL == stringToCode)
    exit(-1);
    memset(stringToCode, 0, sizeof(char)*MAXSIZE);    //���ַ�������Ϊ��

    queueInit(&Q);   //��ʼ��huffman������

    printf("������ַ���Ϊ\n");
    for(i = 0; string[i] != '\0'; i++)
    {
        printf("%c", string[i]);
    }
    puts("");

    selectWeight(&Q, string);  //��Ȩ�ؽ���ͳ�ƣ����Ƕ�������ַ����ִ���ͳ��,���ڵ㰴Ȩֵ��С����������

    huffmantree = createHuffmanTree(&Q);  //����huffman��

    printf("huffman����Ϊ\n");
    huffmanCode(huffmantree, stringToCode, string);     //huffman����
    printf("huffman����Ϊ\n");
    huffmandeCode(huffmantree, stringToCode);    //huffman����
/*============�ͷ��ڴ�================*/
    free(huffmantree);
    huffmantree = NULL;
    free(stringToCode);
    stringToCode = NULL;

    return 0;
}
