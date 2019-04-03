#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

//void do_work(unsigned id)
//{
//    //std::cout << "id = " << id << std::endl;
//}
//
//void thread_test()
//{
//    std::vector<std::thread> threads;
//
//    for (unsigned i = 0; i < 10; ++i) {
//        threads.push_back(std::thread(do_work, i));
//    }
//
//    //由于thread是禁止复制构造函数，Deleted constructor form (thread objects cannot be copied).
//    //所以[](std::thread th)不行，需要引用[](std::thread &th)
//    std::for_each(threads.begin(), threads.end(), [](std::thread& th) { th.join(); /*std::cout << "hello world" << std::endl;*/ });
//
//    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   //可以
//
//    //实际要这样写比较好
//    //for (auto& thread : threads) {
//    //       thread.join();
//    //   }
//
//    std::cout << std::thread::hardware_concurrency() << std::endl;
//}

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
    void print(Test1 *t)
    {
        //std::shared_ptr<Test1> t1(t);

		if (t == nullptr)
            return;

        t->print();
    }
};
//线程安全测试 end

void test(Test1 *t)
{
    t->print();
}

void thread_safe_test()
{
    Test1 t1(1);

    //t1.print();

    t1.~Test1();

    std::thread th1(test, &t1);

	th1.join();
}

int main(int argc, char** argv)
{
    thread_safe_test();

    return 0;
}