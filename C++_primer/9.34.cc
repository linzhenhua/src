/******************************************************************************
*    > File Name: 9.34.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月10日 星期日 19时49分17秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char **argv)
{
    std::string s("this is c++ program!");

    std::string::iterator iter = s.begin();

    while(iter != s.end())
    {
        *iter = toupper(*iter);
        iter++;
    }

    std::cout << s << std::endl;

    return 0;
}
