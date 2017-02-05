/*
 * =====================================================================================
 *
 *       Filename:  7.20.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月18日 22时04分51秒
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

int main(int argc, char **argv)
{
    int arr[10];

    arr[0] = 0;
    arr[1] = 1;

    for(int i = 2; i != 10; ++i)
    {
        arr[i] = arr[i-1]+arr[i-2];
    }

    for(int i = 0; i != 10; ++i)
    {
        cout << arr[i] << '\t';
    }

    cout << endl;

    return 0;
}
