#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "d3des.h"

using namespace std;

typedef struct AE{
	char a;
	unsigned char b;
}AE;

AE ae[] = {
	{'0',0x00}, {'1',0x01}, {'2',0x02}, {'3',0x03}, {'4',0x04}, {'5',0x05},
	{'6',0x06}, {'7',0x07}, {'8',0x08}, {'9',0x09},
	{'A',0x0A}, {'B',0x0B}, {'C',0x0C}, {'D',0x0D}, {'E',0x0E}, {'F',0x0F},
	{'a',0x0a}, {'b',0x0b}, {'c',0x0c}, {'d',0x0d}, {'e',0x0e}, {'f',0x0f}
};

AE ea[] = {
	{'0',0x00}, {'1',0x01}, {'2',0x02}, {'3',0x03}, {'4',0x04}, {'5',0x05},
	{'6',0x06}, {'7',0x07}, {'8',0x08}, {'9',0x09},
	{'A',0x0A}, {'B',0x0B}, {'C',0x0C}, {'D',0x0D}, {'E',0x0E}, {'F',0x0F},
	{'A',0x0a}, {'B',0x0b}, {'C',0x0c}, {'D',0x0d}, {'E',0x0e}, {'F',0x0f}
};

char ebccharasc( unsigned char codeE );

unsigned char asccharebc( char codeA );

void AscToEbc(char *pszData, int nLen);

void EbcToAsc(char *pszEbc, char *pszAsc, int nLen);

static unsigned char key[] = "0123456789ABCDEFFEDCBA9876543210";    //32λ16���Ƶ�key

/*
 * ����1��32λ16���Ƶ�key
 * ����2��8λBCD���key
 * ����3��8λBCD���key
 * */
 /*
void parseKey(unsigned char *key)
{
    unsigned char keyA[16+1] = {0};
    unsigned char keyB[16+1] = {0};

    strncpy((char *)keyA, (char *)key, 16);         //0~15
    strncpy((char *)keyB, (char *)(key+16), 16);    //16~31

    cout << keyA << "\n" << keyB << endl;

    cout << "=============================================" << endl;

    AscToEbc((char*)keyA, strlen((char*)keyA));
    AscToEbc((char*)keyB, strlen((char*)keyB));

    cout << strlen((char*)keyA) << endl;
    cout << strlen((char*)keyB) << endl;

    cout << keyA << "\n" << keyB << endl;

    cout << "=============================================" << endl;

    unsigned char key3[16+1] = {0};
    unsigned char key4[16+1] = {0};

    EbcToAsc((char*)keyA, (char*)key3, 8);
    EbcToAsc((char*)keyB, (char*)key4, 8);

    for(int i = 0; i < 16; ++i)
    {
        printf("%c", key3[i]);
    }
    cout << endl;

    for(int i = 0; i < 16; ++i)
    {
        printf("%c", key4[i]);
    }
    cout << endl;
}
*/

/*

void parseKey1(unsigned char *key, unsigned char *key1, unsigned char *key2)
{
    unsigned char keyA[16+1] = {0};
    unsigned char keyB[16+1] = {0};

    strncpy((char *)keyA, (char *)key, 16);         //0~15
    strncpy((char *)keyB, (char *)(key+16), 16);    //16~31

    //printf("keyA: %s\tkeyB: %s\n", keyA, keyB);

    AscToEbc((char *)keyA, strlen((char*)keyA));
    AscToEbc((char *)keyB, strlen((char*)keyB));

    //printf("strlen(keyA): %d\tstrlen(keyB): %d\n", strlen((char*)keyA), strlen((char*)keyB));

    memcpy(key1, keyA, 8);
    memcpy(key2, keyB, 8);
}


void test()
{
    int i;

    //16λ16�����ַ���
    unsigned char pszSrc[]="0123456789abcdef";
    printf("����ǰ��%s\n", pszSrc);

    unsigned char pszTarget[8+1] = {0};

    unsigned char key1[8+1] = {0};
    unsigned char key2[8+1] = {0};

    parseKey1(key, key1, key2);

    //printf("key1: %s\tkey1: %s\n", key1, key1);
    //printf("strlen(key1): %d\tstrlen(key1): %d\n", strlen((char*)key1), strlen((char*)key1));

    //������ת��ΪBCD��
    int iLength = strlen((char *)pszSrc);     //���ĳ���16λ
    //printf("iLength: %d\n", iLength);

    AscToEbc((char *)pszSrc, iLength);             //EBC��Ϊ8λ
    //printf("pszSrc: %s\n", pszSrc);

//��һ��des===========================================================================
    //unsigned char pszTarget[8+1] = {0};

    unsigned char byKey1[8] = {0};

    char szTempKey1[20];
    memcpy(szTempKey1, key1, 8);
    makekey(szTempKey1, byKey1);

    deskey(byKey1, EN0);
    for(i = 0; i < 8; i += 8)
    {
        des(pszSrc + i, pszTarget + i);
    }
//��һ��des===========================================================================

    //printf("strlen(pszSrc): %d\n", strlen((char *)pszSrc));
    unsigned char temp[16+1] = {0};
    EbcToAsc((char *)pszTarget, (char *)temp, 8);
    printf("���ܺ�temp: %s\n", temp);

    AscToEbc((char *)temp, 16);

//�ڶ���des===========================================================================
    unsigned char byKey2[8] = {0};

    char szTempKey2[20];
    memcpy(szTempKey2, key1, 8);
    makekey(szTempKey2, byKey2);

    deskey(byKey2, DE1);
    for(i = 0; i < 8; i += 8)
    {
        des(temp + i, temp + i);
    }
//�ڶ���des===========================================================================

    EbcToAsc((char*)temp, (char*)temp, 8);

    printf("���ܺ�temp: %s\n", temp);


}

*/

int main()
{
    char key1[] = "AA55EE44";
    char key2[] = "FFBACEDA";

    //AscToEbc(key1, strlen(key1));
    //printf("%s\n", key1);

     //parseKey(key);

     //test();

     char a = 'a';
     char b[10] = {0};

     EbcToAsc(&a,b, 1);
     printf("b = %s\n", b);

    return 0;
}

unsigned char asccharebc( char codeA )
{
	int i = 0;

	for( i = 0; i < sizeof(ae) / sizeof(AE); i++ )
	{
		if( ae[i].a == codeA )
			return( ae[i].b );
	}
	return( ae[0].b );
}

char ebccharasc( unsigned char codeE )
{
	int i = 0;
	for( i = 0; i < sizeof(ea) / sizeof(AE); i++ )
	{
		if( ea[i].b == codeE )
			return( ea[i].a );
	}
	return( ea[0].a );
}

void AscToEbc(char *pszData, int nLen)
{
	int  nPos, i;
	char cHalf;
    char * pszTemp;

	//��̬�����ڴ�
    pszTemp = (char *)malloc(nLen+2);
    if(NULL == pszTemp)
    {
        return;
    }
	memset( pszTemp, 0, nLen+2 );

	//��Ϊ2��������ʱǰ���ַ�0
	if( nLen % 2 != 0 )
	{
		memcpy( &pszTemp[1], pszData, nLen );
		pszTemp[0] = '0';
		nLen++;
	}
	else
		memcpy( pszTemp, pszData, nLen );

	//����ֽڽ���ת������λ
	for( i = 0, nPos = 0; i < nLen; i++ )
	{
		//�ж�������λ����ż��λ
		if( i % 2 == 0 )
		{
			cHalf = 0;
			cHalf = asccharebc( pszTemp[i] );
			cHalf = cHalf << 4;
		}
		else
		{
			pszData[nPos] = cHalf | ( asccharebc( pszTemp[i] ) & 0x0f );
			nPos++;
		}
	}
	//���渳ֵ������0
	pszData[nPos] = 0;

	//�ͷŶ�̬������ڴ�
	free(pszTemp);
	pszTemp = NULL;
}

void EbcToAsc(char *pszEbc, char *pszAsc, int nLen)
{
	int i;
	unsigned char ucAscii;
	for( i = 0; i < nLen; i++ )
	{
		ucAscii = ( pszEbc[i] >> 4 ) & 0x0f;
		pszAsc[2*i] = ebccharasc( ucAscii );
		ucAscii = pszEbc[i] & 0x0f;
		pszAsc[2*i+1] = ebccharasc( ucAscii );
	}
}
