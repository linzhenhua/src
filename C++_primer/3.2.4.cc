/*
 * =====================================================================================
 *
 *       Filename:  3.2.4.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月01日 15时30分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    string s("hello world!!!");
    string::size_type punct_cnt = 0;

    for(string::size_type index = 0; index != s.size(); ++index)
    {
        if(ispunct(s[index]))
        {
            ++punct_cnt;
        }
    }

    cout<<punct_cnt<<" punctuation characters in "<<s<<endl;

    return 0;
}
