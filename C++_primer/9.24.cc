/******************************************************************************
*    > File Name: 9.24.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月06日 星期三 20时16分00秒
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

int main(int argc, char **argv)
{
    std::vector<int> val;

    for(int i = 2; i < 10; ++i)
    {
        val.push_back(i);
    }
    std::vector<int>::iterator iter = val.begin();

    while(iter != val.end())
    {
        std::cout << *iter++ << '\t';
    }
    std::cout << std::endl;

    std::cout << "the first num is:" << std::endl;

    std::cout << val.at(0) << '\t' << val[0] << '\t' << val.front() << '\t' << *val.begin() << std::endl;

    return 0;
}
