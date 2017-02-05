/*
 * =====================================================================================
 *
 *       Filename:  7.32.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月20日 21时54分55秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include "Sales_item.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    Sales_item item;

    cout << "Enter some transactions(ctrl+d to end)" << endl;

    while(item.input(cin))
    {
        cout << "The transaction readed is:" << endl;
        item.output(cout);
        cout << endl;
    }

    return 0;
}
