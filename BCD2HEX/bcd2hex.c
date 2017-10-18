#include <stdlib.h>
#include <string.h>

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

	//动态申请内存
    pszTemp = (char *)malloc(nLen+2);
    if(NULL == pszTemp)
    {
        return;
    }
	memset( pszTemp, 0, nLen+2 );

	//不为2的整数倍时前补字符0
	if( nLen % 2 != 0 )
	{
		memcpy( &pszTemp[1], pszData, nLen );
		pszTemp[0] = '0';
		nLen++;
	}
	else
		memcpy( pszTemp, pszData, nLen );

	//逐个字节进行转化和移位
	for( i = 0, nPos = 0; i < nLen; i++ )
	{
		//判断是奇数位还是偶数位
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
	//后面赋值结束符0
	pszData[nPos] = 0;

	//释放动态申请的内存
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
