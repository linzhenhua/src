/******************************************************************************
*    > File Name: 14.33.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月26日 星期四 10时24分49秒
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

using std::vector;
using std::cin;
using std::endl;
using std::cout;

class GT_cls{
    public:
        GT_cls(int val = 0): bound(val){}
        bool operator () (const int &ival)
        {
            return ival > bound;
        }
    private:
        int bound;
};

int main(int argc, char **argv)
{
    vector<int> ivec;
    int ival;

    cout << "enter numbers(ctrl+d to end): " << endl;
    while(cin >> ival)
    {
        ivec.push_back(ival);
    }
    cin.clear();

    int spval;

    cout << "enter a specified value: " << endl;
    cin >> spval;

    vector<int>::iterator iter;
    iter = find_if(ivec.begin(), ivec.end(), GT_cls(spval) );

    if(iter != ivec.end())
    {
        cout << "the first element that is larger than " << spval << " : " << *iter << endl;
    }
    else
    {
        cout << "no element that is larger than " << spval << endl;
    }

    return 0;
}
