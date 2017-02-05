/******************************************************************************
*    > File Name: 10.12.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月12日 星期四 16时04分59秒
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
#include <utility>

using std::string;
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

int main(int argc, char **argv)
{
    map<string, int> wordCount;
    string word;

    /*读入单词并统计其出现次数*/
    cout << "enter sone words(ctrl+d to end)" << endl;

    while(cin >> word)
    {
        pair<map<string, int>::iterator, bool> ret = 
            wordCount.insert( make_pair(word, 1) );
        if(!ret.second)
        {
            ++ret.first->second;
        }
    }

    /*输出结果*/
    cout << "word \t\t times" << endl;
    for(map<string, int>::iterator iter = wordCount.begin(); iter != wordCount.end(); ++iter)
    {
        cout << iter->first << "\t\t" << iter->second << endl;
    }

    return 0;
}
