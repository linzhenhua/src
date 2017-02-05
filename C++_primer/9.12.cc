/******************************************************************************
*    > File Name: 9.12.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月04日 星期一 21时35分24秒
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

bool findInt(vector <int>::iterator beg, vector <int>::iterator end, int val);

int main(int argc, char **argv)
{
    vector <int> num;
    int val;

    for(int i = 0; i != 10; ++i)
    {
        num.push_back(i);
    }
    for(vector <int >::iterator iter = num.begin(); iter != num.end(); ++iter)
    {
        cout << *iter << '\t';
    }
    cout << endl;

    cout << "请输入你要查找的元素:";
    cin >> val;
    if( findInt(num.begin(), num.end(), val) )
    {
        cout << "找到元素了" << endl;
    }
    else
    {
        cout << "没有找到元素" << endl;
    }

    return 0;
}

bool findInt(vector <int>::iterator beg, vector <int>::iterator end, int val)
{
    while(beg != end)
    {
        if(*beg == val)
        {
            return true;
        }
        else
        {
            ++beg;
        }
    }
    return false;
}


