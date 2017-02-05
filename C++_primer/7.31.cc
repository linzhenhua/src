/*
 * =====================================================================================
 *
 *       Filename:  7.31.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月20日 16时08分12秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Sales_item
{
    public:
        double avg_price() const;

        bool same_isbn(const Sales_item &rhs) const
        {
            return isbn == rhs.isbn;
        }

        //构造函数
        Sales_item(): units_sold(0), revenue(0.0) {}

    private:
        string isbn;
        unsigned units_sold;
        double revenue;
};

double Sales_item::avg_price() const
{
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

int main(int argc, char **argv)
{
    Sales_item trans, total;

    if( total.same_isbn(trans) )
        cout << "yes" << endl;
    else 
        cout << "no" << endl;

    return 0;
}
