/*
 * =====================================================================================
 *
 *       Filename:  7.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月26日 21时20分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    int val1, val2, val3;

    val1 = sizeof(int);
    val2 = sizeof(long);
    val3 = sizeof(double);

    std::cout<<val1<<std::endl;
    std::cout<<val2<<std::endl;
    std::cout<<val3<<std::endl;
    return 0;
}
