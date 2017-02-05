/******************************************************************************
*    > File Name: 11.2.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 08时48分35秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    string ch("lin");

    //string a = "llll" + ch;

    string sum = accumulate(ch.begin(), ch.end(), string(" zhen hua!") );

    cout << sum << endl;

    return 0;
}
