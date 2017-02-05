/******************************************************************************
*    > File Name: 11.2.2.3.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 15时07分30秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    std::vector<int> vec;

    fill_n(back_inserter(vec), 10, 1);

    for(std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        std::cout << *iter << ", ";
    }
    std::cout << std::endl;

    return 0;
}
