#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

class IsHexType
{
    public:
        bool operator()(const char &ch) const
        {
            if(ch >= '0' && ch <= '9')     //����0~9���ϣ�����true
                return true;
            if(ch >= 'A' && ch <= 'F')     //����A~F���ϣ�����true
                return true;
            if(ch >= 'a' && ch <= 'f')     //����a~f���ϣ�����true
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
        std::cout << "����" << std::endl;
    }
    else
    {
        std::cout << "������" << std::endl;
    }

    return 0;
}
