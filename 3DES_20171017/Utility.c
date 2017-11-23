#include "d3des.h"
#include "ebc2hex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//3DES密钥的长度必须是8的倍数，可取24位或32位；
static unsigned char key[] = "0123456789ABCDEFFEDCBA9876543210";    //32位16进制的key

/*
 * 参数1：32位16进制的key
 * 参数2：8位BCD码的key1
 * 参数3：8位BCD码的key2
 * 返回值：无
 * */
void ParseKey(unsigned char *key, unsigned char *key1, unsigned char *key2)
{
    if( (NULL == key) || (NULL == key1) || (NULL == key2) )
    {
        return;
    }

    char keyA[16+1] = {0};
    char keyB[16+1] = {0};

    strncpy(keyA, (char *)key, 16);         //0~15位
    strncpy(keyB, (char *)(key+16), 16);    //16~31位

    AscToEbc(keyA, (int)strlen(keyA));
    AscToEbc(keyB, (int)strlen(keyB));

    memcpy(key1, keyA, 8);
    memcpy(key2, keyB, 8);
}

/*
 * 函数说明：3DES加密
 * 参数1：明文(就是891位的RSA私钥)
 * 参数2：密文保存的绝对路径(保存16进制数)
 * 返回值: 0:成功 -1:失败
 */
int D3DesEncrypt(unsigned char *pszIn, const char *pszPath)
{
    if( (NULL == pszIn) || (NULL == pszPath) )
    {
        printf("函数参数不能为0\n");
        return -1;
    }

    //判断字符串是否为8的倍数，不足的需要填充'\0'
    //方法：对字符串长度对8取余为r，如r大于0，则在字符串后面补8-r个0，如果r等于0，则不补。
    unsigned char *pszInBuf = NULL;          //待加密的数据
    int nInBufLen = 0;
    int nInLen = 0;
    nInLen = (int)strlen((char *)pszIn);
    int nRema = 0;          //余数
    nRema = nInLen % 8;
    int nPad = 0;           //需要填充多少位
    if( nRema > 0 )
    {
        nPad = 8 - nRema;                       //填充的位数
        pszInBuf = (unsigned char *)malloc(nInLen + nPad + 1);
        if(NULL == pszInBuf)
        {
            printf("分配内存失败\n");
            return -1;
        }
        memset(pszInBuf, 0, nInLen + nPad + 1);
        memcpy(pszInBuf, pszIn, nInLen);
        //memset(pszInBuf+nInLen, 0, nPad);     //多余，注释掉

        nInBufLen = nInLen + nPad;
    }
    else
    {
        pszInBuf = (unsigned char *)malloc(nInLen + 1);
        if(NULL == pszInBuf)
        {
            printf("分配内存失败\n");
            return -1;
        }
        memset(pszInBuf, 0, nInLen+1);
        memcpy(pszInBuf, pszIn, nInLen);

        nInBufLen = nInLen;
    }

    //test
    //printf("nInBufLen:%d \npszInBuf: \n%s\n", nInBufLen, pszInBuf);
    //test

    int i = 0;
    unsigned char *pszEncData = NULL;              //用于保存加密后的数据
    pszEncData = (unsigned char *)malloc( nInBufLen );
    if(NULL == pszEncData)
    {
        printf("分配内存失败\n");
        return -1;
    }
    memset(pszEncData, 0, nInBufLen);

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    ParseKey(key, key1, key2);

    //第一次des begin===========================================================================
    deskey(key1, EN0);
    for(i = 0; i < nInBufLen; i += 8)
    {
        des(pszInBuf + i, pszEncData + i);
    }
    //第一次des end=============================================================================

    //第二次des begin===========================================================================
    deskey(key2, DE1);
    for(i = 0; i < nInBufLen; i += 8)
    {
        des(pszEncData + i, pszEncData + i);
    }
    //第二次des end===========================================================================

    //第三次des begin===========================================================================
    //第三次的des加密的key跟第一次des加密的一样
    deskey(key1, EN0);
    for(i = 0; i < nInBufLen; i += 8)
    {
        des(pszEncData + i, pszEncData + i);
    }
    //第三次des end===========================================================================

    //把BCD码转换为16进制
    char *pszDest = NULL;
    pszDest = (char *)malloc(nInBufLen * 2 + 1);
    if(NULL == pszDest)
    {
        printf("分配内存失败\n");
        return -1;
    }
    memset(pszDest, 0, nInBufLen * 2 + 1);
    EbcToAsc((char *)pszEncData, pszDest, nInBufLen);

    //test
    printf("after encode: \n%s\n", pszDest);
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

    free(pszInBuf);
    pszInBuf = NULL;
    free(pszEncData);
    pszEncData = NULL;
    free(pszDest);
    pszDest = NULL;

    return 0;
}

/*
 * 函数说明：3DES解密
 * 参数1：密文保存的绝对路径
 * 参数2：明文
 * 返回值: 0:成功 -1:失败
 */
int D3DesDecrypt(const char *pszPath, unsigned char *pszOut)
{
    if( (NULL == pszPath) || (NULL == pszOut) )
    {
        printf("函数参数不能为0\n");
        return -1;
    }

    int i = 0;

    FILE *pszFile = NULL;
    pszFile = fopen(pszPath, "r");
    if(NULL == pszFile)
    {
        printf("打开文件失败\n");
        return -1;
    }
    fseek(pszFile, 0, SEEK_END);  //把文件指针移动到文件尾
    int nFileLen = 0;
    nFileLen = ftell(pszFile);    //获取文件内容的长度

    unsigned char *pszSrc = NULL;
    pszSrc = (unsigned char *)malloc(nFileLen + 1);
    if(NULL == pszSrc)
    {
        printf("分配内存失败\n");
        return -1;
    }
    memset(pszSrc, 0, nFileLen + 1);

    fseek(pszFile, 0, SEEK_SET);     //把文件指针移动到文件首
    fscanf(pszFile, "%s", pszSrc);
    pszSrc[nFileLen] = '\0';
    fclose(pszFile);

    //printf("pszSrc: \n%s\n", pszSrc);

    //把16进制字符串转换为Ebc码
    int nSrcLen = nFileLen;
    AscToEbc((char *)pszSrc, nSrcLen);

    //获取BCD码形式下pszSrc的数据长度
    if(nSrcLen % 2 == 0)
    {
        nSrcLen /= 2;
    }
    else
    {
        nSrcLen = nSrcLen / 2 + 1;
    }

    printf("nSrcLen: %d\n", nSrcLen);

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    ParseKey(key, key1, key2);

    unsigned char *pszDecData = NULL;   //用于保存解密后的内容
    pszDecData = (unsigned char *)malloc(nSrcLen + 1);
    if(NULL == pszDecData)
    {
        printf("分配内存失败\n");
        return -1;
    }
    memset(pszDecData, 0, nSrcLen + 1);

    //第一次des begin===========================================================================
    deskey(key1, DE1);
    for(i = 0; i < nSrcLen; i += 8)
    {
        des(pszSrc + i, pszDecData + i);
    }
    //第一次des end=============================================================================

    //第二次des begin===========================================================================
    deskey(key2, EN0);
    for(i = 0; i < nSrcLen; i += 8)
    {
        des(pszDecData + i, pszDecData + i);
    }
    //第二次des end=============================================================================

    //第三次des begin===========================================================================
    //第三次的des加密的key跟第一次des加密的一样
    deskey(key1, DE1);
    for(i = 0; i < nSrcLen; i += 8)
    {
        des(pszDecData + i, pszDecData + i);
    }
    //第三次des end===========================================================================

    memcpy(pszOut, pszDecData, nSrcLen);

    free(pszSrc);
    pszSrc = NULL;
    free(pszDecData);
    pszDecData = NULL;

    return 0;
}
