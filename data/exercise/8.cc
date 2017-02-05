/*
 * =====================================================================================
 *
 *       Filename:  8.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月26日 22时36分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>

int main(int argc, char **argv)
{
    int result = 1;
    int base, exponent;
    int i;

    std::cout<<"please enter base and exponent"<<std::endl;
    std::cin>>base>>exponent;

    for(i = 1; i <= exponent; i++)
    {
        result *= base;
    }

    std::cout<<result<<std::endl;

    return 0;
}
