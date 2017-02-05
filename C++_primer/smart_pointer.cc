/******************************************************************************
*    > File Name: smart_pointer.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月24日 星期二 10时31分12秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>

//智能指针
class U_Ptr{
    friend class HasPtr;
    int *ip;
    size_t use;

    //构造函数
    U_Ptr(int *p): ip(p), use(1){}

    //析构函数
    ~U_Ptr(){delete ip;}
};

class HasPtr{
    public:
        //构造函数
        HasPtr(int *p, int i): ptr(new U_Ptr(p)), val(i){}
        //复制构造函数
        HasPtr(const HasPtr &orig):
            ptr(orig.ptr), val(orig.val){++ptr->use;}
        //赋值操作符
        HasPtr& operator = (const HasPtr&);
        //析构函数
        ~HasPtr(){if(--ptr->use == 0) delete ptr;}
    
        //获取数据成员
        int *get_ptr() const 
        {
            return ptr->ip;
        }
        
        int get_int() const
        {
            return val;
        }

        //修改数据成员
        void set_ptr(int *p)
        {
            ptr->ip = p;
        }

        void set_int(int i)
        {
            val = i;
        }

        //返回或者修改基础int对象
        int get_ptr_val() const
        {
            return *ptr->ip;
        }

        void set_ptr_val(int i)
        {
            *ptr->ip = i;
        }

    private:
        U_Ptr *ptr;
        int val;
};

HasPtr& HasPtr::operator = (const HasPtr &rhs)
{
    ++rhs.ptr->use;
    if(--ptr->use == 0)
        delete ptr;
    ptr = rhs.ptr;
    val = rhs.val;

    return *this;
}

class HasPtr1{
    public:
        //构造函数
        HasPtr1(const int &p, int i): ptr(new int(p)), val(i){}
        //复制构造函数
        HasPtr1(const HasPtr1 &orig):ptr(new int(*orig.ptr)), val(orig.val){}
        //赋值操作符
        HasPtr1& operator = (const HasPtr1&);
        //析构函数
        ~HasPtr1(){delete ptr;}

        //获取数据成员
        int get_ptr_val() const
        {
            return *ptr;
        }
        int get_int() const
        {
            return val;
        }
        //修改数据成员
        void set_ptr(int *p)
        {
            ptr = p;
        }
        void set_int(int i)
        {
            val = i;
        }
        //返回指针成员
        int *get_ptr() const
        {
            return ptr;
        }
        //设置指针成员所指向的基础对象
        void set_ptr_val(int p) const
        {
            *ptr = p;
        }
    private:
        int *ptr;
        int val;
};
HasPtr1& HasPtr1::operator = (const HasPtr1 &rhs)
{
    *ptr = *rhs.ptr;
    val = rhs.val;

    return *this;
}

int main(int argc, char **argv)
{
    return 0;
}
