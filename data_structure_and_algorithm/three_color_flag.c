/*
 * =====================================================================================
 *
 *       Filename:  three_color_flag.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月22日 15时20分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//三色旗：蓝，白，红
/*不合格
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BULE 'b'
#define RED 'r'
#define WHITE 'w'

int main(int argc, char **argv)
{
    char color[] = {'b', 'r', 'w', 'r', 'b', 'w', 'r', 'b', 'w', 'w', 'w', '\0'};

    char *p = NULL;
    p = color;

    int rFlag = 0;
    int wFlag = 0;
    int bFlag = 0;
    int i;

    while(*p != '\0')
    {
        if(BULE == *p)
        {
            bFlag++;
        }
        else if(WHITE == *p)
        {
            wFlag++;
        }
        else
        {
            rFlag++;
        }

        p++;
    }
    
    for(i = 0; bFlag != i; i++)
    {
        printf("%c,", BULE);
    }
    for(i = 0; wFlag != i; i++)
    {
        printf("%c,", WHITE);
    }
    for(i = 0; rFlag != i; i++)
    {
        printf("%c,", RED);
    }
    puts("");

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 'r'
#define WHITE 'w'
#define BULE 'b'
//记得加\连接符
#define SWAP(x, y) {\
                    char temp;\
                    temp = color[x];\
                    color[x] = color[y];\
                    color[y] = temp;\
                   }

int main(int argc, char **argv)
{
    char color[] = {'w', 'r', 'w', 'b', 'r', 'w', 'b', 'w', 'r', 'b', '\0'}; //记得加'\0'，相当于字符串

    int wFlag = 0;
    int bFlag = 0;
    int rFlag = strlen(color) - 1;
    int i;

    for(i = 0; i < strlen(color); i++)
    {
        printf("%c ", color[i]);
    }
    puts("");

    while(wFlag <= rFlag)
    {
        if(color[wFlag] == WHITE)
        {
            wFlag++;
        }
        else if(color[wFlag] == BULE)
        {
            SWAP(wFlag, bFlag);    //wFlag和bFlag的前后位置随意放
            wFlag++;
            bFlag++;
        }
        else
        {
            while(wFlag < rFlag && color[rFlag] == RED)
                rFlag--;
            SWAP(wFlag, rFlag);   //wFlag和bFlag的前后位置随意放
            rFlag--;

        }
    }

    for(i = 0; i < strlen(color); i++)
    {
        printf("%c ", color[i]);
    }
    puts("");

    return 0;
}
