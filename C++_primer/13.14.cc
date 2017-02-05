/******************************************************************************
*    > File Name: 13.14.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月23日 星期一 17时15分13秒
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

struct Exmpl{
    //默认构造函数
    Exmpl()
    {
        std::cout << "Exmpl()" << std::endl;
    }
    //复制构造函数
    Exmpl(const Exmpl&)
    {
        std::cout << "Exmpl(const Exmpl&)" << std::endl;
    }
    //赋值操作函数
    Exmpl& operator = (const Exmpl &rhe)
    {
        std::cout << "operator = (const Exmpl&)" << std::endl;

        return *this;
    }
    //析构函数
    ~Exmpl()
    {
        std::cout << "~Exmpl()" << std::endl;
    }
};

void func1(Exmpl obj)
{
}

void func2(Exmpl& obj)
{
}

Exmpl func3()
{
    Exmpl obj;
    
    return obj;
}

int main(int argc, char **argv)
{
    Exmpl eobj;
    std::cout << std::endl;

    func1(eobj);
    std::cout << std::endl;

    func2(eobj);
    std::cout << std::endl;

    eobj = func3();
    std::cout << std::endl;

    Exmpl *p = new Exmpl;
    std::cout << std::endl;

    std::vector<Exmpl> evec(3);
    std::cout << std::endl;

    delete p;
    std::cout << std::endl;
    p = NULL;

    return 0;
}
