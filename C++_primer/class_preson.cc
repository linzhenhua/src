/******************************************************************************
*    > File Name: class_preson.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月18日 星期三 20时40分13秒
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

using std::cout;
using std::endl;
using std::string;

class Person
{
    public:
        string getName() const;
        string getAddress() const;
        typedef string::size_type index;
        Person(const string &nm, const string &add): name(nm), address(add){} 
    private:
        string name;
        string address;
};

int main(int argc, char **argv)
{
    string ch1("lin"), ch2("zhenhua");
    Person human(ch1, ch2);

    string ch3 = human.getName();

    cout << ch3 << endl;

    return 0;
}

string Person::getName() const
{
    return name;
}

string Person::getAddress() const
{
    return address;
}


