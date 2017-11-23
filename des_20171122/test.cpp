#include "d3des.h"
#include "ebc2hex.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

//3DES密钥的长度必须是8的倍数，可取24位或32位；
static unsigned char key[] = "0123456789ABCDEFFEDCBA9876543210";    //32位16进制的key

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

void test()
{
    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};
    ParseKey(key, key1, key2);

    unsigned char pszInBuf[8+1] = {'\0'};
    unsigned char pszEncData[8+1] = {'\0'};

    unsigned char byKey1[8] = {0};
    char szTempKey1[20] = {0};
    memcpy(szTempKey1, key1, 8);
    makekey(szTempKey1, byKey1);
    deskey(byKey1, EN0);
    for(int i = 0; i < 8; i += 8)
    {
        des(pszInBuf + i, pszEncData + i);
    }

    char pszDest[16+1] = {'\0'};
    EbcToAsc((char *)pszEncData, pszDest, 8);

    std::cout << pszDest << std::endl;
}
