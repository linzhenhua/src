/******************************************************************************
*    > File Name: 11.14.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 22时50分28秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;

int main(int argc, char **argv)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    list<int> ival(arr, arr+9);
    vector<int> vec1;
    vector<int> vec2;
    list<int> vec3;

    for(list<int>::iterator iter = ival.begin(); iter != ival.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    replace_copy(ival.begin(), ival.end(), inserter(vec1, vec1.begin()), 1, 100);
    for(vector<int>::iterator iter = vec1.begin(); iter != vec1.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
    
    replace_copy(ival.begin(), ival.end(), back_inserter(vec2), 1, 100);
    for(vector<int>::iterator iter = vec2.begin(); iter != vec2.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    replace_copy(ival.begin(), ival.end(), front_inserter(vec3), 1, 100);
    for(list<int>::iterator iter = vec3.begin(); iter != vec3.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
    
    return 0;
}
