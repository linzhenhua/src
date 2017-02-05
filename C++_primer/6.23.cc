/*
 * =====================================================================================
 *
 *       Filename:  6.23.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月16日 21时06分08秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <stdexcept>

//using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::bitset;
using std::runtime_error;

int main(int argc, char **argv)
{
    bitset<100> bs;

    for(size_t ix = 0; ix != bs.size(); ++ix)
    {
        bs[ix] = 1;
    }
    try
    {
        bs.to_ulong();
    }
    catch (runtime_error err)
    {
        cout << err.what() << endl;
    }
    
    return 0;
}
