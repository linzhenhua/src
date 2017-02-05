/******************************************************************************
*    > File Name: 12.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年01月18日 星期六 10时01分27秒
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

class Person{
    private:
        std::string name;
        std::string address;
    public:
        Person(const std::string &linzhenhua, const std::string &jiujie):name(linzhenhua), address(jiujie){}
};
