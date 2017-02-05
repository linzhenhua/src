/******************************************************************************
*    > File Name: 10.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月14日 星期四 20时25分01秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main(int argc, char **argv)
{
    int ival;
    std::string str;
    std::pair<std::string, int> sipr;
    std::vector< std::pair<std::string, int> > pvec;

    std::cout << "enter a string and an integer(ctrl+d to end)" << std::endl;

    while(std::cin >> str >> ival)
    {
        sipr = make_pair(str, ival);
        pvec.push_back(sipr);
    }

    return 0;
}
