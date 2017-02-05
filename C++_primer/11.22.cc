/******************************************************************************
*    > File Name: 11.22.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月16日 星期一 23时03分30秒
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
#include <iterator>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;

int main(int argc, char **argv)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> ivec(arr, arr+10);
    list<int> ilis;

    vector<int>::reverse_iterator rstart, rend;
    rstart = ivec.rbegin();
    //定位到第7个元素
    for(int i = 1; i != 4; ++i)
    {
        ++rstart;
    }
    //定位到第2个元素
    rend = rstart;
    for(int i = 1; i != 6; ++i)
    {
        ++rend;
    }

    copy(rstart, rend, inserter(ilis, ilis.begin()));

    for(list<int>::iterator iter = ilis.begin(); iter != ilis.end(); ++iter)
    {
        cout << *iter << " ";
    }

    cout << endl;
    

    return 0;
}
