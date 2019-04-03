#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

void do_work(unsigned id)
{
    //std::cout << "id = " << id << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<std::thread> threads;

    for (unsigned i = 0; i < 10; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

	//����thread�ǽ�ֹ���ƹ��캯����Deleted constructor form (thread objects cannot be copied).
	//����[](std::thread th)���У���Ҫ����[](std::thread &th)
    std::for_each(threads.begin(), threads.end(), [](std::thread &th) { th.join(); /*std::cout << "hello world" << std::endl;*/ });

    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   //����

	//ʵ��Ҫ����д�ȽϺ�
	//for (auto& thread : threads) {   
 //       thread.join();
 //   } 

	std::cout << std::thread::hardware_concurrency() << std::endl;

    return 0;
}