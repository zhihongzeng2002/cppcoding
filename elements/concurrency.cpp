#include "concurrency.h"
#include <stdexcept>
#include <chrono>

void Concurrency::testDinnerPhilosophers() {
    vector<string> names{"Aristotle", "Spinoza", "Russell", "Kant", "Plato" };

    vector<shared_ptr<Chopstick> > sticks;
    for (int i=0; i<names.size(); i++)
        sticks.emplace_back(new Chopstick());

    shared_ptr<AtomicLog> printer(new AtomicLog);

    vector<shared_ptr<Philosopher> > philos;
    for (int i=0; i<names.size(); i++)
        philos.emplace_back(new Philosopher(names[i], sticks[i], sticks[(i+1)%names.size()], printer));

    for (auto &p : philos) {
        p->wait_for_cmplt();
    }

}

void Concurrency::Philosopher::wait_for_cmplt() {
    m_thread.join();
}

void Concurrency::Philosopher::thread_func() {
//    void Concurrency::Philosopher::thread_func(shared_ptr<Chopstick> &left, shared_ptr<Chopstick> &right) {
    while (true) {
        if (try_lock(leftStick->m, rightStick->m)) {
                break;
            }
        this_thread::sleep_for(chrono::milliseconds(100));
        }
    lock_guard<mutex> a(leftStick->m, adopt_lock);
    lock_guard<mutex> b(rightStick->m, adopt_lock);
    printer->log(string(name+" is eating"));

}

void Concurrency::testDataBuff() {
    vector<int> arr{1,2,3,4,5};
    vector<thread> tasks;
    DataBuff<int> buf(0);
    for (int i=0; i<arr.size(); i++) {
        tasks.push_back(thread(&DataBuff<int>::write, ref(buf), arr[i]));
        tasks.push_back(thread(&DataBuff<int>::read, &buf));
    }
    for (auto &x : tasks)
        x.join();
}

condition_variable cvs;

void Concurrency::Reader::thread_func() {
//   this is for solution 2: writing preference
    //    {
//        lock_guard<mutex> lck(data->lw);
//    }
    {
        lock_guard<mutex> lck(data->lr);
        data->countReader++;
    }
    string str = data->data;
//    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lck(data->lr);
        data->countReader--;
        cout << "Reading: " << str << endl;
//        cout << "notify--" << endl;
    }
    cvs.notify_all();
}

void Concurrency::Reader::thread_func3() {
    {
        data->lr.lock();
        if (data->isReadPriority==false) {
            data->lr.unlock();
            data->lr.lock();
        }
//        lock_guard<mutex> a(data->lr, adopt_lock);
        data->countReader++;
        data->lr.unlock();
    }

    string str = data->data;
    //    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lck(data->lr);
        data->countReader--;
        data->isReadPriority=false;

        cout << "Reading: " << str << endl;
//        cout << "notify--" << endl;
    }
    cvs.notify_all();
}

void Concurrency::Writer::thread_func3() {
    {
        data->lr.lock();
        if (data->isReadPriority==true) {
            data->lr.unlock();
            data->lr.lock();
        }
//        lock_guard<mutex> a(data->lr, adopt_lock);
        data->lr.unlock();
    }

    unique_lock<mutex> lck(data->lw);
//    if (data->isReadPriority==true)
//        cvs.wait(lck);

    unique_lock<mutex> t(data->lr);
//    cout << "start wait..." << endl;
    cvs.wait(t, [&]{return data->countReader==0;});
//    cout << "wake up..." << endl;

    data->data=update;
    data->isReadPriority=true;
//    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "writing: " << update << endl;
    cvs.notify_all();
}

void Concurrency::Writer::thread_func() {
    lock_guard<mutex> lck(data->lw);
    unique_lock<mutex> t(data->lr);
//    cout << "start wait..." << endl;
    cvs.wait(t, [&]{return data->countReader==0;});
//    cout << "wake up..." << endl;

    data->data=update;
//    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "writing: " << update << endl;
}

void Concurrency::testReaderWriter() {
    shared_ptr<DataArea> buff(new DataArea());

    vector<string> data{"Aristotle", "Spinoza", "Russell", "Kant", "Plato" };

    shared_ptr<condition_variable> cvar;

    vector<shared_ptr<Reader> > readers;
    vector<shared_ptr<Writer> > writers;
    for (int i=0; i<data.size(); i++) {
//        this_thread::sleep_for(chrono::milliseconds(500));
        readers.emplace_back(new Reader(buff,cvar));
        writers.emplace_back(new Writer(buff, data[i], cvar));
    }
    for (int i=0; i<data.size(); i++) {
        readers[i]->wait_complete();
        writers[i]->wait_complete();
    }

}

template<typename T>
bool Concurrency::Blocking_queue<T>::push(const T &t, const chrono::milliseconds &timeout) {
//    chrono::milliseconds timeout = chrono::system_clock::now+_timeout;
    {
        unique_lock<mutex> lck(m);
        if (!push_cv.wait_for(lck, timeout, [&]{ return q.size()<max_size; })) {
            return false;
        } else {
            cout << "push: " << t << endl;
            q.push(t);
        }
    }
    pop_cv.notify_one();
    return true;
}

template<typename T>
bool Concurrency::Blocking_queue<T>::pop(T &t, const chrono::milliseconds &timeout) {
    {
        unique_lock<mutex> lck(m);
//        cout << "pop size: " <<  q.size() << endl;
        if (!pop_cv.wait_for(lck, timeout, [&]{ return q.size()>0; }))
            return false;
        else {
            t=q.front();
            cout << "pop: " << t << endl;
            q.pop();
        }
    }
    push_cv.notify_one();
    return true;
}

void Concurrency::Consumer::thread_func() {
    for (int i=0; i<20; i++) {
        int x;
//        while (true) {
            if (buff->pop(x, chrono::milliseconds(500))) {
                cout << "read:" << x << endl;
            }
            else
                cout << "fail to read" << endl;
        }

}

void Concurrency::Producer::thread_func() {
    for (auto & x: arr) {
//        while (true) {
            if (buff->push(x, chrono::milliseconds(500)))
                cout << "write: " << x << endl;
            else
                cout << "fail to write" << endl;
        }
}

void Concurrency::testConsumerProducer() {
    shared_ptr<Blocking_queue<int> > buff(new Blocking_queue<int>(10));
    vector<int> arr(20, 5);
    Producer p(buff, arr);
    Consumer c(buff);
}

void Concurrency::Collatz::thread_func() {
//    cout << "start, end=" << startInt << "," << endInt << endl;
    for (int i=startInt; i<=endInt; i++)  {
        unordered_set<int> visited;
//        cout << "visited init size=" << visited.size() << endl;
        cout << check(i,visited);
    }
}

bool Concurrency::Collatz::check(int x, unordered_set<int> &visited) {
    if (x==1) return true;
    else if (visited.find(x) != visited.end())
        return false;

    visited.insert(x);
    if (x&1)
        return check(x*3+1, visited);
    else
        return check(x>>1, visited);
}

void Concurrency::testCollatz(int n) {
    int chunkSize=2;
    vector<shared_ptr<Collatz> > tasks;
    int i=0;
    for (; i<n/chunkSize; i++)
        tasks.emplace_back(new Collatz(i*chunkSize+1, (i+1)*chunkSize));
    if (n%chunkSize !=0)
        tasks.emplace_back(new Collatz(i*chunkSize+1, n));
    cout << endl;
}

//void Concurrency::eat(shared_ptr<Chopstick> & leftStick, shared_ptr<Chopstick> & rightStick,
//                      int philoNo, int leftStickNo, int rightStickNo) {
//    if(leftStick==rightStick)
//        throw invalid_argument("left and rihgt sticks should not same");

//    lock(leftStick->m, rightStick->m);
//    lock_guard<mutex>(leftStick->m, adopt_lock);
//    cout << "  Philosopher " << philoNo << " pick up Stick " << leftStickNo << endl;

//    lock_guard<mutex>(rightStick->m, adopt_lock);
//    cout << "  Philosopher " << philoNo << " pick up Stick " << rightStickNo << endl;
//    cout << "Philosopher " << philoNo << " is eating " << rightStickNo << endl;
//    this_thread::sleep_for(chrono::milliseconds(2000));
//}

void Concurrency::dinnerPhilosophers() {

    auto eat = [](shared_ptr<Chopstick> leftChopstick, shared_ptr<Chopstick> rightChopstick, int philosopherNumber, int leftChopstickNumber, int rightChopstickNumber)
    {
        if (leftChopstick == rightChopstick)
            throw invalid_argument("Left and right chopsticks should not be the same!");

    while (true) {
        if(try_lock(leftChopstick->m, rightChopstick->m)==-1)
            break;                // ensures there are no deadlocks
        this_thread::sleep_for(chrono::milliseconds(100));
    }

        lock_guard<mutex> a(leftChopstick->m, adopt_lock);
        string sl = "   Philosopher " + to_string(philosopherNumber) + " picked " + to_string(leftChopstickNumber) + " chopstick.\n";
        cout << sl.c_str();

        lock_guard<mutex> b(rightChopstick->m, adopt_lock);
        string sr = "   Philosopher " + to_string(philosopherNumber) + " picked " + to_string(rightChopstickNumber) + " chopstick.\n";
        cout << sr.c_str();

        string pe = "Philosopher " + to_string(philosopherNumber) + " eats.\n";
        cout << pe;

        //std::chrono::milliseconds timeout(500);
        //std::this_thread::sleep_for(timeout);
    };

cout << "start dinner" << endl;

    static const int numPhilosophers = 5;

    // 5 utencils on the left and right of each philosopher. Use them to acquire locks.
    vector< shared_ptr<Chopstick> > chopsticks(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i)
    {
        auto c1 = shared_ptr<Chopstick>(new Chopstick());
        chopsticks[i] = c1;
    }

    // This is where we create philosophers, each of 5 tasks represents one philosopher.
    vector<thread> tasks(numPhilosophers);

    tasks[0] = thread(eat,
            chopsticks[0],                        // left chopstick:  #1
            chopsticks[numPhilosophers - 1],        // right chopstick: #5
            0 + 1,                                        // philosopher number
            1,
            numPhilosophers
        );

    for (int i = 1; i < numPhilosophers; ++i)
    {
        tasks[i] = (thread(eat,
                chopsticks[i - 1],                // left chopstick
                chopsticks[i],                    // right chopstick
                i + 1,                                    // philosopher number
                i,
                i + 1
                )
            );
    }

    // May eat!
    for (auto &t : tasks)
      t.join();
//    for_each(tasks.begin(), tasks.end(), mem_fn(&thread::join));

}
