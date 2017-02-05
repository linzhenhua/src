/******************************************************************************
*    > File Name: 10.24.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月13日 星期五 15时55分16秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <map>
#include <string>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::string;

int main(int argc, char **argv)
{
    set<string> excluded;
    string word;

    //建立单词排除集
    excluded.insert("success");
    excluded.insert("class");

    cout << "enter a word(ctrl+d to end)" << endl;
    while(cin >> word)
    {
        if(!excluded.count(word))    //该单词未在排除集合中出现
        {
            word.resize(word.size()-1);   //删除单词尾部的's'
        }

        cout << "non-plural Version: " << word << endl;
        cout << "enter a word(ctrl+d to end)" << endl;
    }

    return 0;
}
