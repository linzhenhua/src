/******************************************************************************
*    > File Name: 9.26.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月07日 星期四 19时39分54秒
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
#include <list>

int main(int argc, char **argv)
{
    int ia[] = {0,1,1,2,3,5,8,13,21,55,89};
    std::vector<int> val1;
    std::list<int> val2;

    for(int i = 0; i != sizeof(ia)/sizeof(ia[0]); ++i)
    {
        val1.push_back(ia[i]);
        val2.push_back(ia[i]);
    }
    //std::cout << sizeof(ia) << std::endl;
    std::vector<int>::iterator iter1 = val1.begin();
    std::list<int>::iterator iter2 = val2.begin();

    std::cout << "val1 is:" << std::endl;
    for(;iter1 != val1.end(); ++iter1)
    {
        std::cout << *iter1 << '\t';
    }
    std::cout << std::endl;

    std::cout << "val2 is:" << std::endl;
    while(iter2 != val2.end())
    {
        std::cout << *iter2++ << '\t';
    }
    std::cout << std::endl;

    iter1 = val1.begin();
    while(iter1 != val1.end())
    {
        if((*iter1 & 1) == 0)
        {
            iter1 = val1.erase(iter1);
        }
        else
        {
            ++iter1;
        }
    }
    std::cout << "after:" << std::endl;
    iter1 = val1.begin();
    while(iter1 != val1.end())
    {
        std::cout << *iter1++ << '\t';
    }
    std::cout << std::endl;

    iter2 = val2.begin();
    while(iter2 != val2.end())
    {
        if((*iter2 & 1) != 0)
        {
            iter2 = val2.erase(iter2);
        }
        else
        {
            ++iter2;
        }
    }
    std::cout << "after" << std::endl;
    iter2 = val2.begin();
    while(iter2 != val2.end())
    {
        std::cout << *iter2++ << '\t';
    }
    std::cout << std::endl;

    return 0;
}
