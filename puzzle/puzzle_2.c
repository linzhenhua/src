/*
 * =====================================================================================
 *
 *       Filename:  puzzle_2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 11时19分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>

void OS_Solaris_print()
{
    printf("Solaris - Sun Microsystrms\n");
}

void OS_Windows_print()
{
    printf("Windows - Microsoft\n");
}

void OS_HP_UX_print()
{
    printf("HP-UX - Hewlett Packard\n");
}

int main(int argc, char **argv)
{
    int num;

    printf("Enter the number(1-3):\n");
    scanf("%d", &num);

    switch(num)
    {
        case 1:
            OS_Solaris_print();
            break;
        case 2:
            OS_Windows_print();
            break;
        case 3:
            OS_HP_UX_print();
            break;
        default:
            printf("Hmm! only 1-3 \n");
            break;
    }

    return 0;
}









