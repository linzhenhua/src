/*
 * =====================================================================================
 *
 *       Filename:  3.18.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月06日 19时20分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    vector<int> elem;

    srand((unsigned)time(NULL));

    for(int i = 0; i < 10; i++)
    {
        elem.push_back(rand()%10);
    }

    for(vector<int>::const_iterator j = elem.begin(); j != elem.end(); ++j)
    {
        cout<<*j<<"\t";
    }
    cout<<endl;

    for(vector<int>::iterator iter = elem.begin(); iter != elem.end(); ++iter)
    {
        *iter = *iter * 2;
    }

    for(vector<int>::const_iterator i = elem.begin(); i != elem.end(); ++i)
    {
        cout<<*i<<"\t";
    }
    cout<<endl;

    return 0;
}

