/*
 * =====================================================================================
 *
 *       Filename:  3.1.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月30日 16时33分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;
/*
using std::cin;
using std::cout;
using std::endl;
*/
int main(int argc, char **argv)
{
    int base, exponent;
    int result = 1;

    cout<<"please enter base and exponent:\n";
    cin>>base>>exponent;

    for(int i = 0; i < exponent; i++)
    {
        result *= base; 
    }

    cout<<"result = "<<result<<endl;

    return 0;
}

