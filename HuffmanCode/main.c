#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char *argv[])
{
    int i;
    char string[] = "we love fishc!!";   //要编码的字符串(只能编ASCII码，中文的话虽然能译码，但是不知道它的编码)
    char *stringToCode = NULL;  //用来存放编码的
    linkQueue Q;     //定义一个huffman树队列
    huffmanNode *huffmantree = NULL;   //定义一个huffman树节点

    huffmantree = (huffmanNode *)malloc(sizeof(huffmanNode));    //初始化
    if(NULL == huffmantree)
    exit(-1);

    stringToCode = (char *)malloc(MAXSIZE*sizeof(char));  //分配内存大小
    if(NULL == stringToCode)
    exit(-1);
    memset(stringToCode, 0, sizeof(char)*MAXSIZE);    //将字符数组置为空

    queueInit(&Q);   //初始化huffman树队列

    printf("输入的字符串为\n");
    for(i = 0; string[i] != '\0'; i++)
    {
        printf("%c", string[i]);
    }
    puts("");

    selectWeight(&Q, string);  //对权重进行统计，就是对输入的字符出现次数统计,将节点按权值从小到大放入队列

    huffmantree = createHuffmanTree(&Q);  //创建huffman树

    printf("huffman编码为\n");
    huffmanCode(huffmantree, stringToCode, string);     //huffman编码
    printf("huffman解码为\n");
    huffmandeCode(huffmantree, stringToCode);    //huffman解码
/*============释放内存================*/
    free(huffmantree);
    huffmantree = NULL;
    free(stringToCode);
    stringToCode = NULL;

    return 0;
}
