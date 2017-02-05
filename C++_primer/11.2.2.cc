/******************************************************************************
*    > File Name: 11.2.2.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 10时33分18秒
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
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    vector<int> vec(11, 3);

    for(vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cout << *iter << ", ";
    }
    cout << endl;

    fill_n(vec.begin(), 11, 0);

    for(vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cout << *iter << ", ";
    }
    cout << endl;

    return 0;
}
