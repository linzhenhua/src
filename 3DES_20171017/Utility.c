#include "d3des.h"
#include "ebc2hex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//3DES密钥的长度必须是8的倍数，可取24位或32位；
static unsigned char key[] = "0123456789ABCDEFFEDCBA9876543210";    //32位16进制的key

/*
 * 参数1：32位16进制的key
 * 参数2：8位BCD码的key
 * 参数3：8位BCD码的key
 * 返回值：无
 * */
void parseKey(unsigned char *key, unsigned char *key1, unsigned char *key2)
{
    if( (NULL == key) || (NULL == key1) || (NULL == key2) )
    {
        return;
    }

    unsigned char keyA[16+1] = {0};
    unsigned char keyB[16+1] = {0};

    strncpy((char *)keyA, (char *)key, 16);         //0~15位
    strncpy((char *)keyB, (char *)(key+16), 16);    //16~31位

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
int DesEncrypt(unsigned char *pszSrc, const char *pszPath)
{
    if(NULL == pszSrc || NULL == pszPath)
    {
        return -1;
    }

    int i;
    unsigned char pszTarget[8+1] = {0};

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    parseKey(key, key1, key2);

    //把明文转换为8位BCD码
    int iLength = strlen(pszSrc);     //明文长度16位
    AscToEbc(pszSrc, iLength);

    //test  输出正确
    //unsigned char key3[16+1] = {0};
    //unsigned char key4[16+1] = {0};
    //EbcToAsc((char*)key1, (char*)key3, 8);
    //EbcToAsc((char*)key2, (char*)key4, 8);
    //printf("key3: %s\n", key3);
    //printf("key4: %s\n", key4);
    //test

    //第一次des===========================================================================
    unsigned char byKey1[8] = {0};

    char szTempKey1[20] = {0};
    memcpy(szTempKey1, key1, 8);
    makekey(szTempKey1, byKey1);

    deskey(byKey1, EN0);
    for(i = 0; i < 8; i += 8)
    {
        des(pszSrc + i, pszTarget + i);
    }

    //test
    //把BCD码转换为16进制
    //unsigned char buf[256] = {0};
    //EbcToAsc(pszTarget, buf, 8);
    //printf("buf:%s\n", buf);
    //test

    //第一次des===========================================================================

    //第二次des===========================================================================
    unsigned char byKey2[8] = {0};

    char szTempKey2[20] = {0};
    memcpy(szTempKey2, key2, 8);
    makekey(szTempKey2, byKey2);

    deskey(byKey2, DE1);
    for(i = 0; i < 8; i += 8)
    {
        des(pszTarget + i, pszTarget + i);
    }
    //第二次des===========================================================================

    //第三次des===========================================================================
    //第三次的des加密的key跟第一次des加密的一样
    unsigned char byKey3[8] = {0};

    char szTempKey3[20] = {0};
    memcpy(szTempKey3, key1, 8);
    makekey(szTempKey3, byKey3);

    deskey(byKey3, EN0);
    for(i = 0; i < 8; i += 8)
    {
        des(pszTarget + i, pszTarget + i);
    }
    //第三次des===========================================================================

    //把BCD码转换为16进制
    unsigned char pszDest[16+1] = {0};
    EbcToAsc(pszTarget, pszDest, 8);

    //test
    printf("after encode: %s\n", pszDest);
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

    return 0;
}

/*
 * 函数说明：3DES解密
 * 参数1：密文保存的绝对路径
 * 参数2：明文
 * 返回值: 0:成功 -1:失败
 */
int DesDecrypt(const char *pszPath, unsigned char *pszDest)
{
    if(NULL == pszPath || NULL == pszDest)
    {
        return -1;
    }

    int i = 0;

    unsigned char pszSrc[16+1] = {0};
    FILE *pszFile = NULL;
    pszFile = fopen(pszPath, "r");
    if(NULL == pszFile)
    {
        printf("打开文件失败\n");
        return -1;
    }
    fscanf(pszFile, "%s", pszSrc);
    fclose(pszFile);

    //把16进制字符串转换为Ebc码
    int iLength = strlen(pszSrc);     //明文长度16位
    AscToEbc(pszSrc, iLength);

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    parseKey(key, key1, key2);

    unsigned char pszTemp[8+1] = {0};   //用于临时保存DES后的内容

    //第一次des===========================================================================
    unsigned char byKey1[8] = {0};

    char szTempKey1[20] = {0};
    memcpy(szTempKey1, key1, 8);

    makekey(szTempKey1, byKey1);

    deskey(byKey1, DE1);
    for(i = 0; i < 8; i += 8)
    {
        des(pszSrc + i, pszTemp + i);
    }
    //第一次des===========================================================================

    //第二次des===========================================================================
    unsigned char byKey2[8] = {0};

    char szTempKey2[20] = {0};
    memcpy(szTempKey2, key2, 8);
    makekey(szTempKey2, byKey2);

    deskey(byKey2, EN0);
    for(i = 0; i < 8; i += 8)
    {
        des(pszTemp + i, pszTemp + i);
    }
    //第二次des===========================================================================

    //第三次des===========================================================================
    //第三次的des加密的key跟第一次des加密的一样
    unsigned char byKey3[8] = {0};

    char szTempKey3[20] = {0};
    memcpy(szTempKey3, key1, 8);
    makekey(szTempKey3, byKey3);

    deskey(byKey3, DE1);
    for(i = 0; i < 8; i += 8)
    {
        des(pszTemp + i, pszTemp + i);
    }
    //第三次des===========================================================================

    //把EBC码的结果转换为16进制
    EbcToAsc(pszTemp, pszDest, 8);

    return 0;
}
