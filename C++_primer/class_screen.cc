/******************************************************************************
*    > File Name: class_screen.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月18日 星期三 22时35分51秒
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

using std::string;

class Screen
{
    public:
        typedef string::size_type index;
        Screen(const index &height, const index &width, const string &content): high(height), wid(width), cont(content){}
    private:
        index high, wid;
        string cont;
};

int main(int argc, char **argv)
{

    return 0;
}
