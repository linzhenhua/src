/******************************************************************************
*    > File Name: 11.2.6.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月15日 星期日 20时00分14秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

bool isShorter(const string &s1, const string &s2);
bool GT6(const string &s);
string make_plural(size_t ctr, const string &word, const string &ending);

int main(int argc, char **argv)
{
    char *ch[] = {"lin", "zhen", "hua", "is", "chinese", "lin", "linzhenhua", "linzhenhua"};
    vector<string> words(ch, ch+8);

    /*输出words*/
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    /*对words进行排序*/
    sort(words.begin(), words.end());
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    /*找到重复的元素*/
    vector<string>::iterator end_unique = unique(words.begin(), words.end());
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    /*删除重复的元素*/
    words.erase(end_unique, words.end());
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    /*按照长度对单词进行排序*/
    stable_sort(words.begin(), words.end(), isShorter);
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    /*输出长度大于等于6的单词*/
    vector<string>::size_type wc = count_if(words.begin(), words.end(), GT6);

    cout << wc << " " << make_plural(wc, "word", "s") << " 6 characters or longer" << endl;

    return 0;
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

bool GT6(const string &s)
{
    return s.size() >= 6;
}

string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr == 1) ?  word : word+ending;
}
