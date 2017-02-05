/******************************************************************************
*    > File Name: 11.16.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月16日 星期一 20时32分10秒
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
#include <cstdlib>
#include <string>
#include <iterator>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main(int argc, char **argv)
{
    string fileName;

    cout << "enter input File name:" << endl;
    cin >> fileName;

    ifstream inFile(fileName.c_str());
    if(!inFile)
    {
        cout << "can not open file: " << fileName << endl;
        return EXIT_FAILURE;
    }

    std::istream_iterator<string> in_iter(inFile) ,eof;
    std::ostream_iterator<string> out_iter(cout, " ");

    copy(in_iter, eof, out_iter);

    cout << endl;

    inFile.close();

    return 0;
}
