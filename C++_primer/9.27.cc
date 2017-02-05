/******************************************************************************
*    > File Name: 9.27.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月07日 星期四 20时30分54秒
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
#include <list>
#include <deque>
#include <algorithm>

using std::string;

int main(int argc, char **argv)
{
    string str;
    std::list<string> ival;
    std::list<string>::iterator iter;

    std::cout << "enter some strings (ctrl +d to end):" << std::endl;
    while(std::cin >> str)
    {
        ival.push_back(str);
    }
    std::cin.clear();
    std::cout << std::endl;
    std::cout << "enter a string that you want to search:" << std::endl;
    std::cin >> str;

    iter = find(ival.begin(), ival.end(), str);
    if(iter != ival.end())
    {
        std::cout << "delete element is:" << *iter << std::endl;
        ival.erase(iter);
    }
    iter = ival.begin();
    while(iter != ival.end())
    {
        std::cout << *iter++ << '\t';
    }
    std::cout << std::endl;

    return 0;
}
