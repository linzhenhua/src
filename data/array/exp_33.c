/*
 * =====================================================================================
 *
 *       Filename:  exp_33.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月24日 10时10分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
//穷举法的应用
//四大湖问题
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ph, hh, dh, th;

    for(ph = 1; ph <= 4; ph++)
        for(th = 1; th <= 4; th++)
            if(ph != th)
            {
                for(hh = 1; hh <= 4; hh++)
                {
                    if( (hh != ph)&&(hh != th) )
                    {
                        dh = 10 - ph - th - hh;
                    if( (((dh == 1)+(hh == 4)+(ph == 3)) == 1) &&
                            (((hh == 1)+(dh == 4)+(ph == 2)+(th ==3)) == 1) &&
                            (((hh == 4)+(dh == 3)) == 1) &&
                            (((ph == 1)+(th == 4)+(hh == 2)+(dh == 3)) == 1) )
                        printf("ph = %d, hh = %d, dh = %d, th = %d\n", ph, hh, dh, th);
                    }
                }
            }

    return 0;
}
