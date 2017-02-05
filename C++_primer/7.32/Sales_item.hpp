/*
 * =====================================================================================
 *
 *       Filename:  Sales_item.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月20日 21时37分44秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
/*定义类*/
#ifndef SALESITEM_H
#define SALESITEM_H
#include <iostream>
#include <string>

class Sales_item
{
    public:
        std::istream& input(std::istream& in);
        std::ostream& output(std::ostream& out) const;
        double avg_price() const;
        bool same_isbn(const Sales_item &rhs) const
        {
            return isbn == rhs.isbn;
        }

        Sales_item():units_sold(0), revenue(0.0) {}

    private:
        std::string isbn;
        unsigned units_sold;
        double revenue;
};

#endif

