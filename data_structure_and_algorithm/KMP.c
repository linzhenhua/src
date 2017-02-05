/*
 * =====================================================================================
 *
 *       Filename:  KMP.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月16日 09时00分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_nextval(char const *ptrn, int plen, int *nextval);
int kmp_search(char const *src, int slen, char const *patn, int plen, int const *nextval, int pos);

int main(int argc, char *argv[])
{
    int len1;  //S串的长度
    int len2;  //T串的长度
    int num;   //第num个字符开始匹配

    char str1[] = "BBC ABCDAB ABCDABCDABDE";
    char str2[] = "ABCDABD";

    int nextval[sizeof(str2)];   //用于存放next数组

    len1 = strlen(str1);
    len2 = strlen(str2);

    get_nextval(str2, len2, nextval);
    num = kmp_search(str1, len1, str2, len2, nextval, 0);   //最后一个0表示从首元素开始匹配

    if(num >= 0)
    {
        printf("从第%d个字符开始匹配\n", num);
    }
    else
    {
        printf("没有找到匹配的字符串\n");
    }

    return 0;
}

void get_nextval(char const *ptrn, int plen, int *nextval)
{
    int i = 0;
    nextval[i] = -1;
    int j = -1;

    while(i < plen-1)
    {
        if(j == -1 || ptrn[i] == ptrn[j])
        {
            ++i;
            ++j;

            if(ptrn[i] != ptrn[j])//++i，++j之后，再次判断ptrn[i]与ptrn[j]的关系 
            {                     //之前的错误解法就在于整个判断只有这一句。
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            }
        }/*if(j == -1 || ptrn[i] == ptrn[j])*/
        else
        {
            j = nextval[j];
        }
    }/*while(i < plen-1)*/
}
//int kmp_seach(char const*, int, char const*, int, int const*, int pos)  KMP模式匹配函数  
//输入：src, slen主串  
//输入：patn, plen模式串  
//输入：nextval KMP算法中的next函数值数组 
int kmp_search(char const *src, int slen, char const *patn, int plen, int const *nextval, int pos)
{
    int i = pos;
    int j = 0;

    while(i < slen && j < plen)
    {
        if(j == -1 || src[i] == patn[j])
        {
            ++i;
            ++j;
        }
        else
        {
            //当匹配失败的时候直接用p[j_next]与s[i]比较，  
            //下面阐述怎么求这个值，即匹配失效后下一次匹配的位置 
            j = nextval[j];
        }
    }
    if(j >= plen)
        return i - plen;
    else
        return -1;
}
