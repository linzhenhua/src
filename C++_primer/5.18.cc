/*
 * =====================================================================================
 *
 *       Filename:  5.18.cc
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月14日 21时57分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:
 *        Company:
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char **argv)
{
    vector<string *> iter;

    string str;
    cout << "enter some strings(ctrl+z to end)" << endl;
    while(cin >> str)
    {
        string *pstr = new string;    //指向string对象的指针
        *pstr = str;
        iter.push_back(pstr);
    }

    //输出每个string的内容及其相对应的长度
    vector<string *>::iterator i = iter.begin();
    while(i != iter.end())
    {
        cout << **i << '\t' << (**i).size() << endl;
        ++i;
    }

    //释放各个动态分配的string对象
    i = iter.begin();
    while(i != iter.end())
    {
        delete *i++;
    }

    return 0;
}

