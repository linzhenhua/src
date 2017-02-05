/******************************************************************************
*    > File Name: 10.3.9.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月12日 星期四 17时06分39秒
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
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <stdexcept>

using std::string;
using std::map;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;
using std::istringstream;

ifstream& open_file(ifstream &in, const string &file);

/*
 * ============================================================================
 * 函数名:main
 * 参数:
 * argc:命令行输入命令的个数
 * argv:每个命令的名字
 * 返回值:返回给操作系统，成功return 0 ，失败return 非0
 *=============================================================================
 */
int main(int argc, char **argv)
{
    map<string, string> trans_map;
    string key, value;

    if(argc != 3)
    {
        runtime_error("wrong number of arguments");
    }

    ifstream map_file;
    if(!open_file(map_file, argv[1]))
    {
        runtime_error("no transformation file");
    }

    while(map_file >> key >> value)
    {
        trans_map.insert(make_pair(key, value));
    }

    ifstream input;
    if(open_file(input, argv[2]))
    {
        runtime_error("no input file");
    }

    string line;
    while(getline(input, line))
    {
        istringstream stream(line);
        string word;
        bool firstword = true;
        
        while(stream >> word)
        {
            map<string, string>::const_iterator map_it = trans_map.find(word);
            if(map_it != trans_map.end())
            {
                word = map_it->second;
            }
            if(firstword)
            {
                firstword = false;
            }
            else
            {
                cout << " ";
            }
            cout << word;
        }/*end of while(stream >> word)*/
        cout << endl;
    }/*end of while(getline(input, line))*/

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
