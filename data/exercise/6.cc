/*
 * =====================================================================================
 *
 *       Filename:  6.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月24日 22时15分47秒
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
    int v1, v2;

    std::cout<<"enter two numbers"<<std::endl;

    std::cin>>v1>>v2;
    
    std::cout<<"the sum of "<<v1<<" and "<<v2<<" is "<<v1*v2<<std::endl;

    return 0;
}
