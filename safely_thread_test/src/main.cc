#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

void do_work(unsigned id)
{
    //std::cout << "id = " << id << std::endl;
}

void thread_test()
{
    std::vector<std::thread> threads;

    for (unsigned i = 0; i < 10; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

    //����thread�ǽ�ֹ���ƹ��캯����Deleted constructor form (thread objects cannot be copied).
    //����[](std::thread th)���У���Ҫ����[](std::thread &th)
    std::for_each(threads.begin(), threads.end(), [](std::thread& th) { th.join(); /*std::cout << "hello world" << std::endl;*/ });

    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   //����

    //ʵ��Ҫ����д�ȽϺ�
    //for (auto& thread : threads) {
    //       thread.join();
    //   }

    std::cout << std::thread::hardware_concurrency() << std::endl;
}

//�̰߳�ȫ���� begin
class Test1 {
public:
    Test1(int i)
    {
        val_ = new int(i);
    }

    ~Test1()
    {
        delete val_;
        val_ = nullptr;
    }

    void print()
    {
        std::cout << "val_ = " << *val_ << std::endl;
    }

private:
    int *val_;
};

class Test2 {
public:
    Test2(const Test1* t)
        : t1_(t)
    {
    }

	~Test2(){}

	void print()
    {
        std::cout << "t1_ = " << t1_->print() << std::endl;
    }

private:
    Test1* t1_;
};

//�̰߳�ȫ���� end

int main(int argc, char** argv)
{
    Test1 t(1);

	t.print();

    return 0;
}