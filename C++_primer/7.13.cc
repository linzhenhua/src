/*
 * =====================================================================================
 *
 *       Filename:  7.13.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月17日 21时37分19秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

void printArr1(int *p, int size);
void printArr2(int *beg, int *end);

int main(int argc, char **argv)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printArr1(arr, 10);
    cout << endl;

    printArr2(arr, arr+10);
    cout << endl;

    return 0;
}

void printArr1(int *p, int size)
{
    for(int i = 0; i != size; i++)
    {
        cout << *(p+i) << '\t';
    }

    return;
}

void printArr2(int *beg, int *end)
{
    while(beg != end)
    {
        cout << *beg++ << '\t';
    }
}
