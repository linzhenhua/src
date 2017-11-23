#include <iostream>
#include <string>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <assert.h>
#include <unistd.h>

class IsHexType
{
        public:
                    bool operator()(char ch)
                                {
                                                if(ch >= '0' && ch <= '9')     //属于0~9集合，返回true
                                                                    return true;
                                                            if(ch >= 'A' && ch <= 'F')     //属于A~F集合，返回true
                                                                                return true;
                                                                        if(ch >= 'a' && ch <= 'f')     //属于a~f集合，返回true
                                                                                            return true;

                                                                                    return false;
                                                                                            }
};

int main()
{
        std::string m_strIn1("g123gg");

            int count = count_if(m_strIn1.begin(), m_strIn1.end(), IsHexType());
                if(0 == count)
                {
                    std::cout << "不满足" << std::endl;
                }
                else
                {
                    std::cout << "满足" << std::endl;
                }

                return 0;
}

