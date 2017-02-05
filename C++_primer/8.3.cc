/******************************************************************************
*    > File Name: 8.3.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月24日 星期四 19时28分41秒
*    >Revision: none
*    >Compiler: g++
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
//using std::in;
//using std::cin;
//using std::cout;
//using std::endl;
//using std::cerr;
//using std::string;

istream& io_function(istream&);   //函数声明

int main(int argc ,char **argv)
{
    int dval;

    io_function(cin);

    cin >> dval;
    cout << dval << endl;

    return 0;
}

istream& io_function( istream& in)
{
    int num;

    while( in >> num, !in.eof() )
    {
        if(in.bad())
        {
            throw runtime_error("IO stream corruped");
        }
        if(in.fail())
        {
            cerr << "bad data, try again";
            in.clear();
            in.ignore(200, ' ');
            continue;

        }
        cout << num << '\t';
    }
    cout << endl;

    in.clear();

    return in;
}
