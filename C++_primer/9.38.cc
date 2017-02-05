/******************************************************************************
*    > File Name: 9.38.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月10日 星期日 21时49分38秒
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

int main(int argc, char **argv)
{
    std::string str("ab2c3d7R4E6");
    std::string numerics("0123456789");
    std::string letters("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    std::string::size_type pos = 0;

    while( ( pos = str.find_first_not_of(numerics, pos) ) != std::string::npos )
    {
        std::cout << "found letters at index: " << pos << '\t' << "element is " << str[pos] << std::endl;
        ++pos;
    }

    std::cout << std::endl;
    pos  = 0;
    while( ( pos = str.find_first_not_of(letters, pos)) != std::string::npos)
    {
        std::cout << "found numerics at index: " << pos << '\t' << "element is " << str[pos] << std::endl;
        ++pos;
    }

    std::cout << std::endl;
    pos = 0;
    while( ( pos = str.find_first_of(numerics, pos) ) != std::string::npos )
    {
        std::cout << "found number at index: " << pos << '\t' << "element is " << str[pos] << std::endl;
        ++pos;
    }

    std::cout << std::endl;
    pos  = 0;
    while( ( pos = str.find_first_of(letters, pos)) != std::string::npos)
    {
        std::cout << "found letters at index: " << pos << '\t' << "element is " << str[pos] << std::endl;
        ++pos;
    }

    return 0;
}
