/******************************************************************************
*    > File Name: 8.8.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月27日 星期日 22时59分01秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//using namespace std;

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::cerr;
using std::endl;
using std::ifstream;

void process(string);

int main(int argc, char **argv)
{
    vector<string> files;
    string fileName, s;

    cout << "Enter filename:(Ctrl + d)" << endl;
    while(cin >> fileName)
    {
        files.push_back(fileName);
    }

    ifstream input;
    vector<string>::const_iterator it = files.begin();

    while(it != files.end())
    {
        input.open(it->c_str());
        if(!input)
        {
            cerr << "error: can not open files: " << *it << endl;
            input.clear();
            ++it;
        }
        else
        {
            while(input >> s)
            {
                process(s);
            }
            input.close();
            input.clear();
            ++it;
        }
    }

    return 0;
}

void process(string s)
{
    cout << s;
}
