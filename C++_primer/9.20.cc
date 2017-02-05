/******************************************************************************
*    > File Name: 9.20.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月05日 星期二 22时19分11秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <vector>
#include <list>

int main(int argc, char **argv)
{
    std::vector<int> num1;
    std::list<int> num2;

    for(int i = 0; i < 10; ++i)
    {
        num1.push_back(i);
    }
    std::vector<int>::iterator iter1 = num1.begin();
    while(iter1 != num1.end())
    {
        std::cout << *iter1++ << '\t';
    }
    std::cout << std::endl;

    for(int j = 1; j < 2; ++j)
    {
        num2.push_back(j);
    }
    std::list<int>::iterator iter2 = num2.begin();
    while(iter2 != num2.end())
    {
        std::cout << *iter2++ << '\t';
    }
    std::cout << std::endl;

    iter1 = num1.begin();
    iter2 = num2.begin();
    if( num1.size() == num2.size() )
    {
        while(iter1 != num1.end())
        {
            if(*iter1 > *iter2)
            {
                std::cout << "num1 is greater than num2" << std::endl;
                break;
            }
            else if(*iter1 < *iter2)
            {
                std::cout << "num2 is greater than num1" << std::endl;
                break;
            }
            else
            {
                ++iter1;
                ++iter2;
            }
            if(iter1 == num1.end())
            {
                std::cout << "num1 == num2" << std::endl;
            }
        }
    }/*end of if(num1.size() == num2.size())*/
    else if( num1.size() > num2.size() )
    {
        while(iter2 != num2.end())
        {
            if(*iter1 > *iter2)
            {
                std::cout << "num1 is greater than num2" << std::endl;
                break;
            }
            else if(*iter1 < *iter2)
            {
                std::cout << "num2 is greater than num1" << std::endl;
                break;
            }
            else
            {
                ++iter1;
                ++iter2;
            }
        }
        if( iter2 == num2.end() )
        {
            std::cout << "num1 is greater than num2" << std::endl;
        }
    }/*end of else if(num1.size() > num2.size())*/
    else if( num1.size() < num2.size() )
    {
        while(iter1 != num1.end())
        {
            if(*iter1 > *iter2)
            {
                std::cout << "num1 is greater than num2" << std::endl;
                break;
            }
            else if(*iter1 < *iter2)
            {
                std::cout << "num2 is greater than num1" << std::endl;
                break;
            }
            else
            {
                ++iter1;
                ++iter2;
            }
        }
        if( iter1 == num1.end() )
        {
            std::cout << "num2 is greater than num1" << std::endl;
        }
    }/*end of else*/

    return 0;
}
