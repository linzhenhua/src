/*
 * =====================================================================================
 *
 *       Filename:  7.14.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月17日 21时51分07秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    double x;
    double sum = 0;
    vector<double> arr;

    for(int i = 0; i != 10; i++)
    {
        cin >> x;
        arr.push_back(x);
    }

    for(vector<double>::iterator i = arr.begin(); i != arr.end(); i++)
    {
        cout << *i << '\t';
    }
    cout << endl;

    for(vector<double>::iterator i = arr.begin(); i != arr.end(); i++)
    {
        sum += *i;
    }    
    cout << sum << endl;

    return 0;
}
