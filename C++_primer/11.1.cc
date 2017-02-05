/******************************************************************************
*    > File Name: 11.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月14日 星期六 23时07分44秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    int ival;
    int searchValue;
    vector<int> ivec;

    cout << "enter some integers(ctrl+d to end)" << endl;
    while(cin >> ival)
    {
        ivec.push_back(ival);
    }
    cin.clear();

    cout << "enter an integer you want to search: " << endl;
    cin >> searchValue;

    cout << count(ivec.begin(), ivec.end(), searchValue) << " elements in the vector have value " << searchValue << endl;

    return 0;
}
