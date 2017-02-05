/*
 * =====================================================================================
 *
 *       Filename:  7.5.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月18日 21时01分26秒
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
using std::string;

char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

int main(int argc, char **argv)
{
    string s("a value");

    cout << s << endl;

    get_val(s, 0) = 'A';

    cout << s << endl;

    return 0;
}
