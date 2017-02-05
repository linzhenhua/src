/******************************************************************************
*    > File Name: 12.13.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月21日 星期六 20时29分23秒
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
#include <cstdlib>

using std::string;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

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
        const Screen& display(ostream &os) const;

    private:
        string contents;
        index cursor;
        index height, width;

        void do_display(ostream &os) const;
};

//构造函数
Screen::Screen(index hght, index wdth, const string &cntnts = ""):
    cursor(0), height(hght), width(wdth)
{
    contents.assign(hght * wdth, ' ');
    if(cntnts.size() != 0)
    {
        contents.replace(0, cntnts.size(), cntnts);
    }
}

char Screen::get(index ht, index wd) const
{
    index row = ht * width;
    
    return contents[row + wd];
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
    if(r >= height || c >= width)
    {
        cerr << "invalid row or column" << endl;
        throw EXIT_FAILURE;
    }

    index row = r * width;
    cursor = row + c;

    return *this;
}

Screen& Screen::display(ostream &os)
{
    do_display(os);

    return *this;
}

const Screen& Screen::display(ostream &os) const
{
    do_display(os);

    return *this;
}
void Screen::do_display(ostream &os) const
{
    string::size_type index = 0;

    while(index != contents.size())
    {
        os << contents[index];
        if( (index+1) % width == 0)
        {
            os << '\n';
        }
        ++index;
    }
}

int main(int argc, char **argv)
{
    Screen myScreen(5, 6, "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa\n");

    myScreen.move(4, 0).set('#').display(cout);

    return 0;
}
