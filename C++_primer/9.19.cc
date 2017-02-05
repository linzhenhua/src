/******************************************************************************
*    > File Name: 9.19.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月05日 星期二 20时23分16秒
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

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    vector <int> num;

    for(int i = 0; i < 10; ++i)
    {
        num.push_back(i);
    }
    for(int i = 0; i < 10; ++i)
    {
        cout << num[i] << '\t';
    }
    cout << endl;

    vector <int>::iterator first = num.begin();

    while(first != num.end())
    {
        first = num.insert(first, 10);
        first += 2;
    }

    first = num.begin();
    while(first != num.end())
    {
        cout << *first++ << '\t';
    }
    cout << endl;

    return 0;
}
