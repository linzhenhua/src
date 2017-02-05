/******************************************************************************
*    > File Name: 9.28.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月07日 星期四 22时03分44秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <list>
#include <vector>

using std::string;

int main(int argc, char **argv)
{
    char *pch[] = {"lin", "zhen", "hua"};
    std::list<char*> ival(pch, pch+3);
    std::vector<std::string> sval;
    //std::string;

    sval.assign(ival.begin(), ival.end());

    for(std::list<char*>::iterator iter = ival.begin(); iter != ival.end(); ++iter)  
    {
        std::cout << *iter << '\t';
    }
    std::cout << std::endl;

    for(std::vector<string>::iterator iter = sval.begin(); iter != sval.end(); ++iter)
    {
        std::cout << *iter << '\t';
    }
    std::cout << std::endl;

    return 0;
}

