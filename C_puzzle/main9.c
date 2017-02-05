/*
 * =====================================================================================
 *
 *       Filename:  main9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 16时06分48秒
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

int main(int argc, char **argv)
{
    int a = 3, b = 5;

    printf(&a["Ya, How is this?%s\n"], &b["junk\super"]);

    printf(&a["WHAT%c%c%c %c%c %c!\n"], 
            1["this"],
            2["beauty"],
            0["tool"],
            0["is"],
            3["sensitive"],
            4["CCCCCC"]
            );

    return 0;
}




