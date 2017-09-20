#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <memory>
#include <condition_variable>
#include <string>
#include <atomic>
#include <queue>
#include <unordered_set>

using namespace std;

//condition_variable cvs;

class Concurrency
{
public:

    struct Chopstick {
        mutex m;
    };

    struct AtomicLog {
        mutex m;
        void log(const string str) {
            m.lock();
            cout << str << endl;
            m.unlock();
        }
    };

//    void eat(shared_ptr<Chopstick> & leftStick, shared_ptr<Chopstick> & rightStick,
//                  int phiiloNo, int leftStickNo, int rightStickNo);
    void dinnerPhilosophers();

    class Philosopher {
    private:
        string name;
        shared_ptr<Chopstick> leftStick, rightStick;
        thread m_thread;
        shared_ptr<AtomicLog> printer;

//        void thread_func(shared_ptr<Chopstick> & left, shared_ptr<Chopstick> & right);
        void thread_func();

    public:
        Philosopher(string &_name, shared_ptr<Chopstick> & left, shared_ptr<Chopstick> & right, shared_ptr<AtomicLog> & _printer)
            : name(_name), leftStick(left), rightStick(right), printer(_printer),
              m_thread(thread(std::bind(&Philosopher::thread_func, this))) {
        }

        void wait_for_cmplt();

//        ~Philosopher() {
//            wait_for_cmplt();
//        }

    };

    void testDinnerPhilosophers();

    // optimized reader-writer implementation
    template<typename T>
    class DataBuff {
        mutex lw, lr, printer;
        int countReader;
        T data;
        condition_variable cv;
        atomic<bool> readPriority;

    public:
        DataBuff(const T & t) : data(t), countReader(0), readPriority(false) {}
        T read() {
            if (readPriority==false)
            {
                lock_guard<mutex> c(lr);
            }
            {
                lock_guard<mutex> a(lr);
                countReader++;
            }
            T ret = data;
            this_thread::sleep_for(chrono::milliseconds(500));
            {
                lock_guard<mutex> a(lr);
                countReader--;
                readPriority=false;
            }
            {
                lock_guard<mutex> b(printer);
                cout << "read:" << ret << endl;
            }
            cv.notify_all();
            return ret;
        }
        void write( const T &t) {
//            if (readPriority==true) {
//                lock_guard<mutex> a(lw);
//            }
            {
                lock_guard<mutex> a(lw);
                unique_lock<mutex> b(lr);
                cv.wait(b, [&]{ return countReader==0;});
                data=t;
                this_thread::sleep_for(chrono::milliseconds(500));
                readPriority=true;
            }
            {
                lock_guard<mutex> b(printer);
                cout << "write:" << data << endl;
            }

        }
    };

    void testDataBuff();

    struct DataArea {
        mutex lw, lr;
        atomic<int> countReader;
        string data;
        bool isReadPriority;
        DataArea(): data("initial"), countReader(0), isReadPriority(false) {}

    };

    class Reader {
        shared_ptr<DataArea> data;
        thread m_thread;
        void thread_func();
        void thread_func3();
        shared_ptr<condition_variable> cv; // problem happen using this cv, maybe condition_variable have to be global

    public:
        Reader(shared_ptr<DataArea> & _data, shared_ptr<condition_variable> &_cv)
            :data(_data), cv(_cv),
              m_thread(bind(&Reader::thread_func3, this)) {}

        void wait_complete() {
            m_thread.join();
        }

    };

    class Writer {
        shared_ptr<DataArea> data;
        thread m_thread;
        void thread_func();
        void thread_func3();
        string update;
        shared_ptr<condition_variable> cv;

    public:
        Writer(shared_ptr<DataArea> &_data, string _str, shared_ptr<condition_variable> &_cv)
            :data(_data), update(_str), cv(_cv),
              m_thread(bind(&Writer::thread_func3, this)) {}

        void wait_complete() {
            m_thread.join();
        }
    };

    void testReaderWriter();

    // consumer-producer
    template<typename T>
    class Blocking_queue {
        mutex m;
        size_t max_size;
        condition_variable push_cv; // maybe one condition_variable is enough?
                                    //No, in push, check push_condition, then notify pop_condition if success.
        condition_variable pop_cv;
        queue<T> q;

    public:
        Blocking_queue(const size_t _size) : max_size(_size) {}
        bool push(const T & t, const chrono::milliseconds & timeout);
        bool pop(T &t, const chrono::milliseconds & timeout);
        size_t size() { return q.size(); }
    };

    class Consumer {
        thread m_thread;
        void thread_func();
        shared_ptr<Blocking_queue<int> > buff;
    public:
        Consumer(shared_ptr<Blocking_queue<int> > &_buff) : buff(_buff), m_thread(bind(&Consumer::thread_func, this)) {}
        ~Consumer() { m_thread.join();}
    };

    class Producer {
        thread m_thread;
        void thread_func();
        vector<int> arr;
        shared_ptr<Blocking_queue<int> > buff;
    public:
        Producer(shared_ptr<Blocking_queue<int> > &_buff, vector<int> & _arr) : buff(_buff), arr(_arr), m_thread(bind(&Producer::thread_func, this)) {}
        ~Producer() { m_thread.join();}
    };

    void testConsumerProducer();

    // 18.11
    class Collatz {
        thread mthread;
        void thread_func();
        bool check(int x, unordered_set<int> & visited);
        int startInt, endInt;
    public:
        Collatz(int i, int j) : startInt(i), endInt(j), mthread(thread(bind(&Collatz::thread_func, this)))
        { }
        ~Collatz() {
            mthread.join();
        }
    };

    void testCollatz(int n);

};

class semaphore{
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    semaphore(int count_ = 0):count(count_){;}
    void notify()
    {
        unique_lock<mutex> lck(mtx);
        ++count;
        cv.notify_one();
    }
    void wait()
    {
        unique_lock<mutex> lck(mtx);

        while(count == 0){
            cv.wait(lck);
        }
        count--;
    }
};

#endif // CONCURRENCY_H
