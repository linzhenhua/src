/******************************************************************************
*    > File Name: 12.13.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月21日 星期六 19时40分54秒
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
using std::ostream;
using std::cout;

class Screen
{
    public:
        typedef string::size_type index;

        char get() const
        {
            return contents[cursor];
        }
        inline char get(index ht, index wd) const;
        index get_cursor() const;

        Screen(index hght, index wdth, const string &cntnts);   //构造函数

        Screen& move(index r, index c);
        Screen& set(char);
        Screen& display(ostream &os);

    private:
        string contents;
        index cursor;
        index height, width;
};

//构造函数
Screen::Screen(index hght, index wdth, const string &cntnts):
    contents(cntnts), cursor(0), height(hght), width(wdth)
{
}

char Screen::get(index r, index c) const
{
    index row = r * width;
    
    return contents[row + c];
}

inline Screen::index Screen::get_cursor() const
{
    return cursor;
}

Screen& Screen::set(char c)
{
    contents[cursor] = c;
    
    return *this;
}

Screen& Screen::move(index r, index c)
{
    index row = r * width;
    cursor = row + c;

    return *this;
}

Screen& Screen::display(ostream &os)
{
    os << contents;

    return *this;
}

int main(int argc, char **argv)
{
    Screen myScreen(5, 6, "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa\n");

    myScreen.move(4, 0).set('#').display(cout);

    return 0;
}
