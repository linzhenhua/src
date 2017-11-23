#include "Utility.h"
#include "ebc2hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //16位字符串
    //unsigned char bufSrc[] = "0123456789";

    char *pszFilePath = "rsa_private_key.pem";
    //char *pszFilePath = "rsa_public_key.pem";
    FILE *pszFile = NULL;
    pszFile = fopen(pszFilePath, "rb");
    if(NULL == pszFilePath)
    {
        printf("打开文件失败\n");
        return -1;
    }
    fseek(pszFile, 0, SEEK_END);  //把文件指针移动到文件尾
    int nFileLen = 0;
    nFileLen = ftell(pszFile);    //获取文件内容的长度

    printf("main: nFileLen: %d\n", nFileLen);

    unsigned char *pszSrc = NULL;
    pszSrc = (unsigned char *)malloc(nFileLen + 1);
    if(NULL == pszSrc)
    {
        printf("分配内存失败\n");
        return -1;
    }
    memset(pszSrc, 0, nFileLen + 1);

    fseek(pszFile, 0, SEEK_SET);     //把文件指针移动到文件首
    fread(pszSrc, nFileLen, 1, pszFile);
    pszSrc[nFileLen] = '\0';
    fclose(pszFile);

    printf("source: \n%s\n", pszSrc);

    const char *bufPath = "CipherTest.key";

    if( 0 == D3DesEncrypt(pszSrc, bufPath) )
    {
        printf("encode ok\n");
    }

    free(pszSrc);
    pszSrc = NULL;

    unsigned char buf[1024] = {0};
    if( 0 == D3DesDecrypt(bufPath, buf) )
    {
        printf("decode ok\ndecode source: \n%s\n", buf);
    }

    return 0;
}
