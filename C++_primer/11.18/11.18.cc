/******************************************************************************
*    > File Name: 11.18.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月16日 星期一 21时08分01秒
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
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <iterator>

using std::cin;
using std::endl;
using std::cout;
using std::vector;
using std::ifstream;
using std::ofstream;

int main(int argc, char **argv)
{
    ofstream oddFile("oddfile.dat");
    ofstream evenFile("evenfile.dat");

    if(!oddFile || !evenFile)
    {
        cout << "can not open output file" << endl;
        return EXIT_FAILURE;

    }

    cout << "enter some numbers:(ctrl+d to end) " << endl;

    std::istream_iterator<int> inIter(cin), eof;
    std::ostream_iterator<int> outEvenFile(evenFile, "\n");
    std::ostream_iterator<int> outOddFile(oddFile, " ");

    while(inIter != eof)
    {
        if( (*inIter & 1) == 0)    //是偶数
        {
            *outEvenFile = *inIter;
            ++outEvenFile;
        }
        else
        {
            *outOddFile = *inIter;
            ++outOddFile;
        }
        ++inIter;
    }

    oddFile.close();
    evenFile.close();

    return 0;
}


