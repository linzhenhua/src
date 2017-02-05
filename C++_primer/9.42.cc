/******************************************************************************
*    > File Name: 9.42.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月13日 星期三 19时34分34秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <stack>
#include <string>

int main(int argc, char **argv)
{
    std::string arr;
    std::stack<std::string> str;

    std::cout << "enter some string" << std::endl;
    while(std::cin >> arr )
    {
        str.push(arr);
    }

    while( str.empty() != true )
    {
        arr = str.top();
        std::cout << arr << std::endl;
        str.pop();
    }

    return 0;
}
