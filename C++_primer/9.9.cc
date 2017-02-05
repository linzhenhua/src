/******************************************************************************
*    > File Name: 9.9.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月04日 星期一 20时35分43秒
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

using std::list;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    //int num;
    list <int> i;

    //cout << "请输入数字,按 Ctrl+d 结束" << endl;

    for(int n = 0; n != 9; ++n)
    {
        i.push_back(n);
    }

    for(list <int>::iterator iter = i.end(); iter != i.begin();)
    {
        cout << *--iter << '\t';
    }
    cout << endl;

    return 0;
}
