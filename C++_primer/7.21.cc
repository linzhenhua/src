/*
 * =====================================================================================
 *
 *       Filename:  7.21.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月18日 22时24分46秒
 *       Revision:  none
 *       Compiler:  g++
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

int factorial(int val)
{
    if(val > 1)
        return factorial(val - 1) * val;
    return 1;
}

int main(int argc, char **argv)
{
    int x = 5;
    int sum = 0;

    sum = factorial(x);

    cout << sum <<endl;

    return 0;
}
