#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include <unistd.h>

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
        t->print();
    }
};

void test(Test1* t)
{
    //直接判断指针是否为空是不行的
    if (t == nullptr)
        return;

    t->print();
}

//这个是线程不安全的
void thread_safe_test()
{
    Test1 t1(1);

    t1.print();

    t1.~Test1();  //模拟多线程环境中对象被销毁

    std::thread th1(test, &t1);  //模拟对象被多个线程看到

	th1.join();
}

void test_v2(std::weak_ptr<Test1> t)
{
    std::shared_ptr<Test1> obj(t.lock());

	sleep(5);

    std::cout << t.use_count() << std::endl;
    std::cout << obj.use_count() << std::endl;

    if (obj) {
        obj->print();
	}

	sleep(2);
}

void thread_safe_test_v2()
{
    std::shared_ptr<Test1> t1 = std::make_shared<Test1>(1);

    std::thread th1(test_v2, t1); //模拟对象被多个线程看到

	sleep(1);
	t1.reset(); //清空t1,模拟多线程环境中对象被销毁

    th1.join();
}

int main(int argc, char** argv)
{
    //thread_safe_test();

	thread_safe_test_v2();

    return 0;
}