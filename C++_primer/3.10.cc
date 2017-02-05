/*
 * =====================================================================================
 *
 *       Filename:  3.10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月02日 14时47分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    string s;

    getline(cin, s);
    cout << "before: " << s << endl;

    for(string::size_type i = 0; i < s.size(); ++i)
    {
        if( ispunct(s[i]) )
        {
            s[i] = ' ';
        }
    }
    cout << "after: " << s << endl;

    return 0;
}
