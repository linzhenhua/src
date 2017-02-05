/******************************************************************************
*    > File Name: 8.14.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年10月28日 星期一 21时36分20秒
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

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;

int main(int argc, char **argv)
{
    char arr1[255] = {0};
    char arr2[255] = {0};

   ofstream f_out("test.txt", ofstream::out);

   cout << "请输入文本的内容" << endl;

   cin.getline(arr1, 255, 0);
   f_out << arr1;
   f_out.close();

   cout << endl;
   ifstream f_in("test.txt", ifstream::in);
   f_in.getline(arr2, 255, 0);
   cout << arr2 << endl;
   f_in.close();

    return 0;
}
