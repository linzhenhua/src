/******************************************************************************
*    > File Name: 9.43.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月13日 星期三 19时53分01秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <stack>
#include <string>

int main(int argc, char **argv)
{
    std::stack<char> sexp;
    std::string exp;

    std::cout << "enter a expression:" << std::endl;
    std::cin >> exp;

    std::string::iterator iter = exp.begin();
    while(iter != exp.end())
    {
        if(*iter != ')')
        {
            sexp.push(*iter);
        }
        else
        {
            while( !sexp.empty() && sexp.top() != '(' )
            {
                sexp.pop();
            }

            if(sexp.empty())
            {
                std::cout << "parentheses are not mached" << std::endl;
            }
            else
            {
                sexp.pop();
                sexp.push('@');
            }
        }
        ++iter;
    }

    return 0;
}
