#ifndef MULTITHREAD_H
#define MULTITHREAD_H

#include <thread>
#include <future>
#include <iostream>
#include <mutex>
#include <atomic>

using namespace std;

namespace B
{
class A
{
public:
    int simplefunc(std::string a)
    {
        cout << a << endl;
        return 3;
    }
};
}


class Multithread
{
public:
    Multithread();
    void test()
    {
        string t("Hello World");
        B::A a;
        for (int i=0; i<10000000; i++)
        {
            cout << i<<":";
            async(std::launch::async, &B::A::simplefunc, &a, t);
        }
        //        int x= future0.get();  // future equall to join in thread

    }
};

class Chopstick
{

};

template <typename T>
class threadSafeReadWrite
{
    static mutex _mutex;
    static atomic<int> write_count, read_count;
    static int x;
public:
    threadSafeReadWrite() {}

    T read()
    {
        while (write_count) {}
        read_count++;

        T y=x;

        read_count--;
        return y;
    }

    void write(T data)
    {
        _mutex.lock();

        while (read_count) {}
        write_count++;

        x=data;

        write_count--;

        _mutex.unlock();
    }

};

template <typename T>
atomic<int> threadSafeReadWrite<T>::write_count=0;
template <typename T>
atomic<int> threadSafeReadWrite<T>::read_count=0;

#endif // MULTITHREAD_H
