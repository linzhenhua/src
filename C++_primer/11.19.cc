/******************************************************************************
*    > File Name: 11.19.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月16日 星期一 22时41分12秒
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
#include <iterator>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    vector<int> ival;
    int num;

    cout << "enter integer(ctrl+d to end): " << endl;

    while(cin >> num)
    {
        ival.push_back(num);
    }
    cin.clear();

    vector<int>::reverse_iterator r_iter;

    for(r_iter = ival.rbegin(); r_iter != ival.rend(); ++r_iter)
    {
        cout << *r_iter << " ";
    }
    cout << endl;

    vector<int>::iterator iter;

    for(iter = ival.end()-1; iter >= ival.begin(); --iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}
