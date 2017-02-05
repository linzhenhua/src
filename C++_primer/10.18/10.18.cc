/******************************************************************************
*    > File Name: 10.18.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月13日 星期五 09时11分42秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <utility>

//using namespace std;

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::pair;

ifstream& open_file(ifstream &in, const string &file);

int main(int argc, char **argv)
{
    map<string, string> familyName;

    if(argc != 2)
    {
        cerr << "wrong number of arguments, please try again" << endl;
        cout << "usage: ./a.out file" << endl;
        return -1;
    }

    /*把文本file里面的内容插入map_file文件中*/
    ifstream map_file;
    string key;
    string value;

    if ( !open_file(map_file, argv[1]) )
    {
        cerr << "open file error" << endl;
        return -1;
    }
    while(map_file >> key >> value)
    {
        familyName.insert( make_pair(key, value) );
    }

    /*查找特定的姓氏*/
    string word;
    map<string, string>::iterator iter;
    cout << "please input you want to find the file:" << "\t";
    cin >> word;
    if( (iter = familyName.find(word)) == familyName.end() )
    {
        cout << "this file was not found" << endl;
        return -1;
    }
    else
    {
        cout << iter->second << endl;
    }
    
    return 0;
}

/*
 * ============================================================================
 * 函数名:open_file
 * 参数:
 * in: 待输入的文件
 * file: 待输入的文件名
 * 返回值: 把in和file绑定,然后返回输入文件in的状态
 *============================================================================= 
 */
ifstream& open_file(ifstream &in, const string &file)
{
    in.close();
    in.clear();
    in.open(file.c_str());

    return in;
}
