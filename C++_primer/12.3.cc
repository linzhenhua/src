/******************************************************************************
*    > File Name: 12.3.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年01月18日 星期六 10时14分11秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
class Person{
    public:
        Person(const std::string &linzhenhua, const std::string &jiujie){}
        std::string getName() const
        {
            return name;
        }
        std::string getAddress() const
        {
            return address;
        }
    private:
        std::string name;
        std::string address;
};
