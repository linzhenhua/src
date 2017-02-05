/*
 * =====================================================================================
 *
 *       Filename:  hanoi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月20日 15时31分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
/*
 说明河内之塔(Towers of Hanoi)是法国人M.Claus(Lucas)于1883年从泰国带至法国的，
 河内为越战时北越的首都，即现在的胡志明市；1883年法国数学家 Edouard Lucas曾提及这个故事，
 据说创世纪时Benares有一座波罗教塔，是由三支钻石棒（Pag）所支撑，开始时神在第一根棒上
 放置64个由上至下依由小至大排列的金盘（Disc），并命令僧侣将所有的金盘从第一根石棒移至第三根石棒，
 且搬运过程中遵守大盘子在小盘子之下的原则，若每日仅搬一个盘子，
 则当盘子全数搬运完毕之时，此塔将毁损，而也就是世界末日来临之时。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hanoi(int n, char x, char y, char z );  //声明汉诺塔函数
    
void hanoi(int n, char x, char y, char z )   //将n个盘子从x借助y移动到z 
{
    if(1 == n)
    {
        printf("move sheet from %c->%c\n", x, z);
    }
    else
    {
        hanoi(n-1, x, z, y);  //将n-1个盘子从x借助z移动到y 
        printf("move sheet from %c->%c\n", x, z);  //将n个盘子从x移动到z 
        hanoi(n-1, y, x, z);   //将n-1个盘子从y借助x移动到z 
    }
}

int main(int argc, char *argv[])
{
    int n;

    printf("请输入盘子的个数\n");
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');

    return 0;
}
