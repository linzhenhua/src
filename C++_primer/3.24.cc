/*
 * =====================================================================================
 *
 *       Filename:  3.24.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月07日 21时25分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <bitset>

using std::cin;
using std::cout;
using std::bitset;
using std::endl;

int main(int argc, char **argv)
{
    bitset<32> bit;
    int x = 0;
    int y = 1;
    int z;

    cout << bit << endl;

    z = x + y;
    while(z <= 21)    //斐波那契数列
    {
        bit.set(z);
        x = y;
        y = z;
        z = x + y;
    }

    cout << bit << endl;

    return 0;
}
