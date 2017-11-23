#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

class IsHexType
{
    public:
        bool operator()(const char &ch) const
        {
            if(ch >= '0' && ch <= '9')     //属于0~9集合，返回true
                return true;
            if(ch >= 'A' && ch <= 'F')     //属于A~F集合，返回true
                return true;
            if(ch >= 'a' && ch <= 'f')     //属于a~f集合，返回true
                return true;

            return false;
        }

        typedef int argument_type;
};

int main()
{
    std::string m_strIn1("abcdef123456");

    int count = std::count_if(m_strIn1.begin(), m_strIn1.end(), std::not1(IsHexType()) );

    std::cout << count << std::endl;

    if(0 == count)
    {
        std::cout << "满足" << std::endl;
    }
    else
    {
        std::cout << "不满足" << std::endl;
    }

    return 0;
}
