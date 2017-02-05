/******************************************************************************
*    > File Name: 13.10.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月23日 星期一 15时41分50秒
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
#include <cstdlib>

class Employee{
    public:
        //构造函数
        Employee():name("NoName")
        {
            setId();
        }
        Employee(std::string nm):name(nm)
        {
            setId();
        }
        Employee(const Employee& other):name(other.name)
        {
            setId();
        }
        //赋值操作符
        Employee& operator = (const Employee& rhe)
        {
            name = rhe.name;
            
            return *this;
        }
    private:
        std::string name;
        std::string id;
        static int counter;

        //设置雇员id
        void setId()
        {
            id = "Empl-";

            if(counter < 10)
            {
                id += "000";
            }
            else if(counter < 100)
            {
                id += "00";
            }
            else if(counter < 1000)
            {
                id += "0";
            }
            else
            {
                std::cerr << "no valid employee id!" << std::endl;
            }

            char buffer[5];

            itoa(counter, buffer, 10);
            id += buffer;
            ++counter;
        }
};
int Employee::counter = 1;

int main(int argc, char **argv)
{

    return 0;
}
