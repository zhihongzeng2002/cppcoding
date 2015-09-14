#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
//using namespace boost;

static std::mutex m;
static int x=0;

void foo(int id)
{
    for (int i=0; i<20; i++)
    {
        std::lock_guard<std::mutex> lock(m);
        x+=id;
        cout << "Output from thread " << '(' << id << "): x=" << x << endl;

    }


    //    // simulate expensive operation
//    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

int main()
{
//    std::cout << "starting first helper...\n";
    std::thread helper1(foo, 1);

//    std::cout << "starting second helper...\n";
    std::thread helper2(foo, 2);

//    std::cout << "starting third helper...\n";
    std::thread helper3(foo, 3);

//    cout << "thread id: " << helper1.get_id() << ',' << helper2.get_id() << ',' << helper3.get_id() << endl;

    helper1.join();
    helper2.join();
    helper3.join();
//    std::cout << "waiting for helpers to finish...\n";
//    helper2.join();
//    cout << "helper2 is done" << endl;
//    helper1.join();

//    std::shared_ptr<int> p1(new int);
//    *p1 = 1;
//    std::cout << "done!\n";
//    cout << *p1 << endl;
}
