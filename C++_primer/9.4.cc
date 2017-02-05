/******************************************************************************
*    > File Name: 9.4.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月08日 星期五 21时57分16秒
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

int main(int argc, char **argv)
{
    std::vector<int> ivec;

    std::cout << "ivec size " << ivec.size() << std::endl << "capacity: " << ivec.capacity() << std::endl;

    for(std::vector<int>::size_type ix = 0; ix != 24; ++ix)
    {
        ivec.push_back(ix);
    }

    std::cout << "ivec size " << ivec.size() << std::endl << "capacity: " << ivec.capacity() << std::endl;

    ivec.reserve(50);

    std::cout << "ivec size " << ivec.size() << std::endl << "capacity: " << ivec.capacity() << std::endl;

    return 0;
}
