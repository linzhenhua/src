#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

/*求字符串s_xor1与s_xor2异或结果
异或长度为i_len,结果放在s_ret*/
void str_xor(unsigned char s_xor1[],unsigned char s_xor2[],int i_len,char s_ret[])
{
	int j;

	for(j=0;j<i_len;j++)
	{
		s_ret[j]= s_xor1[j] ^ s_xor2[j];
	}
	return ;
}

int main()
{
/*
    unsigned char xor1[] = "a";
    unsigned char xor2[] = "b";
    int len = strlen((char*)xor1);
    char ret[50] = {'\0'};

    str_xor(xor1, xor2, len, ret);

    printf("ret: %s\n", ret);
*/

    char a = 'A';
    char b = 'B';

    char c = a^b;

    printf("%x", c);

    return 0;
}







