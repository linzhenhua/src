#include "Utility.h"
#include "ebc2hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //16位16进制字符串
    unsigned char bufSrc[]="0123456789ABCDEF";

    const char *bufPath = "CipherTest.key";

    printf("source %s\n", bufSrc);

    if( 0 == Des(bufSrc, bufPath) )
    {
        printf("测试成功\n");
    }

    return 0;
}
