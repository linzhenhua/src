/*
 * =====================================================================================
 *
 *       Filename:  7.3.3.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月18日 21时22分19秒
 *       Revision:  none
 *       Compiler:  g
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    int x;
    int sum = 1;

    cin >> x;


    for(int i = 0; i != 5; ++i)
    {
        sum *= x--;
    }

    cout << 5 << "的阶乘为:" << sum << endl;

    return 0;
}
