/*
 * =====================================================================================
 *
 *       Filename:  fibonacci.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月20日 16时22分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
Fibonacci为1200年代的欧洲数学家，在他的着作中曾经提到：
「若有一只免子每个月生一只小免子，一个月后小免子也开始生产。
起初只有一只免子，一个月后就有两只免子，二个月后有三只免子，
三个月后有五只免子（小免子投入生产）......
如果不太理解这个例子的话，举个图就知道了，
注意新生的小免子需一个月成长期才会投入生产，
类似的道理也可以用于植物的生长，这就是Fibonacci数列，
一般习惯称之为费氏数列，例如以下： 1、1 、2、3、5、8、13、21、34、55、89...... 
*/
//记得用非递归实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int main(int argc, char *argv[])
{
    int i;
    int fibonacci[N] = {0};
    FILE *fp = NULL;

    fp = fopen("fibonacci.txt","w");
    if(NULL == fp)
        perror("fibonacci.txt");

    fibonacci[0] = 1;
    fibonacci[1] = 1;

    for(i = 2; i < N; i++)
    {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    for(i = 0; i < N; i++)
    {
        fprintf(fp, "%d\n", fibonacci[i]);
    }

    fclose(fp);

    return 0;
}
