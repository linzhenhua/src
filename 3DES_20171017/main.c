#include "Utility.h"
#include "ebc2hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //16位16进制字符串
    unsigned char bufSrc[] = "0123456789ABCDEF";

    const char *bufPath = "CipherTest.key";

    printf("source: %s\n", bufSrc);

    if( 0 == DesEncrypt(bufSrc, bufPath) )
    {
        printf("encode ok\n");
    }

    unsigned char buf[16+1] = {0};
    if( 0 == DesDecrypt(bufPath, buf) )
    {
        printf("decode ok\ndecode source: %s\n", buf);
    }

    return 0;
}
