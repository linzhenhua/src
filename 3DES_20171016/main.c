#include "Utility.h"
#include "ebc2hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //16λ16�����ַ���
    unsigned char bufSrc[]="0123456789ABCDEF";

    const char *bufPath = "CipherTest.key";

    printf("source %s\n", bufSrc);

    if( 0 == Des(bufSrc, bufPath) )
    {
        printf("���Գɹ�\n");
    }

    return 0;
}
