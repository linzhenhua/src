/*
 * =====================================================================================
 *
 *       Filename:  6.1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月03日 08时00分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

char *find_char(char const *source, char const *chars);  //

char *find_char(char const *source, char const *chars)
{
    char *cp;

    if(source != NULL && chars != NULL)
    {
        while(*source != '\0')
        {
            for(cp = chars; *cp != '\0'; cp++)
            {
                if(*cp == *source)
                {
                    return source;
                }
            }
            source++;
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    char *string1 = "ABCDEF";
    char *string2 = "KKF";
    char *ch;

    if( (ch = find_char(string1, string2)) == NULL)
    {
        printf("the character is not found!\n");
    }
    else
    {
        printf("the character is %c\n", *ch);
    }

    return 0;
}
