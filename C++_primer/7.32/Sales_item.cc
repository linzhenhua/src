/*
 * =====================================================================================
 *
 *       Filename:  Sales_item.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月20日 21时46分12秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include "Sales_item.hpp"

std::istream& Sales_item::input(std::istream& in)
{
    double price;
    
    in >> isbn >> units_sold >> price;

    if(in)
        revenue = units_sold * price;
    else
    {
        units_sold = 0;
        revenue = 0.0;
    }

    return in;
}

std::ostream& Sales_item::output(std::ostream& out) const
{
    out << isbn << "\t" << units_sold << "\t" << revenue << "\t" << avg_price();

    return out;
}

double Sales_item::avg_price() const
{
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}
