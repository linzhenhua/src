/******************************************************************************
*    > File Name: 11.3.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 10时04分32秒
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
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    int num, result;
    vector<int> sum;

    cout << "enter some numbers(ctrl+d to end):" << endl;

    while(cin >> num)
    {
        sum.push_back(num);
    }

    cin.clear();

    result = accumulate(sum.begin(), sum.end(), 0);

    cout << result << endl;

    return 0;
}
