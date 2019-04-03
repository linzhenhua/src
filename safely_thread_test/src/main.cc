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

    //由于thread是禁止复制构造函数，Deleted constructor form (thread objects cannot be copied).
    //所以[](std::thread th)不行，需要引用[](std::thread &th)
    std::for_each(threads.begin(), threads.end(), [](std::thread& th) { th.join(); /*std::cout << "hello world" << std::endl;*/ });

    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   //可以

    //实际要这样写比较好
    //for (auto& thread : threads) {
    //       thread.join();
    //   }

    std::cout << std::thread::hardware_concurrency() << std::endl;
}

//线程安全测试 begin
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
    int* val_;
};

class Test2 {
public:
    Test2(Test1* t)
        : t1_(t)
    {
    }

    ~Test2() {}

    void print()
    {
        t1_->print();
    }

private:
    Test1* t1_;
};

//线程安全测试 end

int main(int argc, char** argv)
{
    Test1 t(1);

    t.print();

    return 0;
}