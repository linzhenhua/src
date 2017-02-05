/******************************************************************************
*    > File Name: 10.9.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月15日 星期五 08时21分02秒
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
#include <map>

int main(int argc, char **argv)
{
    std::map<std::string, int> word_count;
    std::string word;

    std::cout << "enter some word:(ctrl+d to end)" << std::endl;
    while(std::cin >> word)
    {
        ++word_count[word];
    }

    std::map<std::string, int>::iterator iter = word_count.begin();
    while(iter != word_count.end())
    {
        std::cout << iter->first << '\t' << iter->second << std::endl;
        ++iter;
    }

    return 0;
}
