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
//    //����thread�ǽ�ֹ���ƹ��캯����Deleted constructor form (thread objects cannot be copied).
//    //����[](std::thread th)���У���Ҫ����[](std::thread &th)
//    std::for_each(threads.begin(), threads.end(), [](std::thread& th) { th.join(); /*std::cout << "hello world" << std::endl;*/ });
//
//    //std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   //����
//
//    //ʵ��Ҫ����д�ȽϺ�
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
    //ֱ���ж�ָ���Ƿ�Ϊ���ǲ��е�
    if (t == nullptr)
        return;

    t->print();
}

//������̲߳���ȫ��
void thread_safe_test()
{
    Test1 t1(1);

    t1.print();

    t1.~Test1();  //ģ����̻߳����ж�������

    std::thread th1(test, &t1);  //ģ����󱻶���߳̿���

	th1.join();
}

void test_v2(std::weak_ptr<Test1> t)
{
    std::shared_ptr<Test1> obj(t.lock());
    if (obj) {
        obj->print();
	}
}

void thread_safe_test_v2()
{
    std::shared_ptr<Test1> t1 = std::make_shared<Test1>(1);

    //t1.reset(); //ģ����̻߳����ж�������

    std::thread th1(test_v2, t1); //ģ����󱻶���߳̿���

    th1.join();
}

int main(int argc, char** argv)
{
    //thread_safe_test();

	thread_safe_test_v2();

    return 0;
}