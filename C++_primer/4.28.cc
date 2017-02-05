/*
 * =====================================================================================
 *
 *       Filename:  4.28.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 22时04分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::vector;
using std::endl;

int main(int argc, char **argv)
{
    vector<int> ivec;
    int ival;

    //读入数据并建立vector
    cout << "enter number:(Ctrl+Z to end)" << endl;
    while(cin >> ival)
    {
        ivec.push_back(ival);
    }

    //动态建立数组
    int *pia = new int[ivec.size()];
    
    //复制元素
    int *tp = pia;
    for(vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter, ++tp)
    {
        *tp = *iter;
    }

    //释放动态数组的内存
    delete [] pia;
    pia = NULL;

    return 0;
}

