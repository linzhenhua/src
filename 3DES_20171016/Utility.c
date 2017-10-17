#include "d3des.h"
#include "ebc2hex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char key[] = "0123456789ABCDEFFEDCBA9876543210";    //32位16进制的key

/*
 * 参数1：32位16进制的key
 * 参数2：8位BCD码的key
 * 参数3：8位BCD码的key
 * 返回值：无
 * */
void parseKey(unsigned char *key, unsigned char *key1, unsigned char *key2)
{
    unsigned char keyA[16+1] = {0};
    unsigned char keyB[16+1] = {0};

    strncpy((char *)keyA, (char *)key, 16);         //0~15
    strncpy((char *)keyB, (char *)(key+16), 16);    //16~31

    AscToEbc(keyA, strlen((char*)keyA));
    AscToEbc(keyB, strlen((char*)keyB));

    memcpy(key1, keyA, 8);
    memcpy(key2, keyB, 8);
}

/*
 * 函数说明：3DES加密
 * 参数1：明文
 * 参数2：密文保存的绝对路径
 * 返回值: 0:成功 -1:失败
 */
int Des(unsigned char *pszSrc, const char *pszPath)
{
    if(NULL == pszSrc || NULL == pszPath)
    {
        return -1;
    }

    //des加密===========================================================================
    int i;
    unsigned char pszTarget[8+1] = {0};

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    parseKey(key, key1, key2);

    //把明文转换为BCD码
    int iLength = strlen(pszSrc);     //明文长度16位
    //printf("iLength: %d\n", iLength);

    AscToEbc(pszSrc, iLength);        //EBC码为8位
    //printf("pszSrc: %s\n", pszSrc);

    //printf("strlen(pszSrc): %d\n", strlen(pszSrc));
    //unsigned char temp[16+1] = {0};
    //EbcToAsc(pszSrc, temp, 8);
    //printf("temp: %s\n", temp);

    unsigned char byKey1[8] = {0};

    char szTempKey1[20];
    memcpy(szTempKey1, key1, 8);
    printf("szTempKey11:\n");
    for(i = 0; i < 20; ++i)
    {
        printf("%X", szTempKey1[i]);
    }
    printf("\n");

    makekey(szTempKey1, byKey1);
    printf("byKey11:\n");
    for(i = 0; i < 8; ++i)
    {
        printf("%X", byKey1[i]);
    }
    printf("\n");

    deskey(byKey1, EN0);
    for(i = 0; i < 8; i += 8)
    {
        des(pszSrc + i, pszTarget + i);
    }

    //把BCD码转换为16进制
    unsigned char pszDest[16+1] = {0};
    EbcToAsc(pszTarget, pszDest, 8);

    //test
    printf("encode %s\n", pszDest);
    //test

    //把16进制加密内容保存到文件中
    FILE *pszFile = NULL;
    pszFile = fopen(pszPath, "w");
    if(NULL == pszFile)
    {
        printf("打开文件失败\n");
        return -1;
    }
    fprintf(pszFile, "%s", pszDest);
    fclose(pszFile);

    //des加密===========================================================================

    //des解密===========================================================================
    unsigned char pszSrc1[16+1] = {0};
    //FILE *pszFile = NULL;
    pszFile = fopen(pszPath, "r");
    if(NULL == pszFile)
    {
        printf("打开文件失败\n");
        return -1;
    }
    fscanf(pszFile, "%s", pszSrc1);
    fclose(pszFile);

    //把16进制字符串转换为Ebc码
    AscToEbc(pszSrc1, 16);

    unsigned char pszTemp[8+1] = {0};
    unsigned char pszAsc[16+1] = {0};

    unsigned char byKey2[8] = {0};

    char szTempKey2[20];
    memcpy(szTempKey2, key1, 8);
    printf("szTempKey2:\n");
    for(i = 0; i < 20; ++i)
    {
        printf("%X", szTempKey2[i]);
    }
    printf("\n");
    makekey(szTempKey2, byKey2);
    printf("byKey2:\n");
    for(i = 0; i < 8; ++i)
    {
        printf("%X", byKey2[i]);
    }
    printf("\n");

    deskey(byKey2, DE1);
    for(i = 0; i < 8; i += 8)
    {
        des(pszSrc1 + i, pszTemp + i);
    }

    EbcToAsc(pszTemp, pszAsc, 8);

    printf("decode %s\n", pszAsc);

    //des解密===========================================================================

    return 0;
}
