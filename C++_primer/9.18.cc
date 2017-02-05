/******************************************************************************
*    > File Name: 9.18.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月05日 星期二 21时04分03秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <list>
#include <deque>

using std::cin;
using std::endl;
using std::cout;
using std::list;
using std::deque;

int main(int argc, char **argv)
{
    list<int> num;
    deque<int> val1;
    deque<int> val2;

    for(int i = 0; i < 10; ++i)
    {
        num.push_back(i);
    }

    list<int>::iterator first = num.begin();
    while(first != num.end())
    {
        cout << *first++ << '\t';
    }
    cout << endl;

    first = num.begin();
    while(first != num.end())
    {
        if( (*first & 1) == 0 )
        {
            val1.push_back(*first);
        }
        else
        {
            val2.push_back(*first);
        }
        ++first;
    }

    deque<int>::iterator iter = val1.begin();
    while(iter != val1.end())
    {
        cout << *iter++ << '\t';
    }
    cout << endl;

    iter = val2.begin();
    while(iter != val2.end())
    {
        cout << *iter++ << '\t';
    }
    cout << endl;

    return 0;
}
