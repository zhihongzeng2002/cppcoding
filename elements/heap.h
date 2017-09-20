#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

class Heap
{
public:
    Heap();

    struct CompMedian{
        double m;
        CompMedian(double median) : m(median) {}

        bool operator()(const int &a, const int &b) const {
            return fabs(a-m) < fabs(b-m);
        }
    };

    int findNthElement(vector<int> & A, int k);
    double getMedian(vector<int> &A);

    vector<int> findKClosestMedian(vector<int> &A, int k);

    struct Compare {
        bool operator() (const pair<int, int> & a, const pair<int, int> &b) const {
            return a.first > b.first;
        }
    };

    vector<int> merge_arrays(const vector<vector<int> > &s);
    void mergeSortedFiles(const vector<string> &fins, const string &fout);
    vector<int> sort_k_increase_decrease_array(const vector<int> &s);
    void find_kth_largest_stream(istringstream & sin, int k);
    vector<int> find_k_closest_median(vector<int> &s, int k);
    void online_median(istringstream & sin);
    //10.10
    int compare_kth_largest_heap(const vector<int> & max_heap, int k, int x);
    // 11.1.1
    int find_local_minimum(const vector<int> &A, int s, int e);

    struct Num {
        int a, b;
        double v;
        Num(int _a, int _b) : a(_a), b(_b), v(a+b*sqrt(2)) {}
        bool operator<(const Num & y) const {
            return v>y.v;
        }
        bool operator==(const Num y) const {
            return a==y.a && b==y.b;
        }
    };

    struct HashNum {
        size_t operator() (const Num & x) const {
            return hash<int>()(x.a) ^ hash<int>()(x.b);
        }
    };

    vector<Num> generate_first_k(int k);
};

template<typename T>
struct Compare_heap {
    bool operator()(const pair<int, T> & a, const pair<int, T> &b) const {
        return a.first<b.first;
    }
};

// using max_heap to implement a stack (LIFO);
template<typename T>
class Stack_heap {
    int idx=0;
    priority_queue<pair<int, T>, vector<pair<int, T> >, Compare_heap<T> > max_heap;

public:
    void push(const T & x) {
        max_heap.emplace(idx++, x);
    }

    T pop() {
        T ret = max_heap.top().second;
        max_heap.pop();
        return ret;
    }

    T peek() {
        return max_heap.top().second;
    }
};

// using max_heap to implement a queue (FIFO)
template<typename T>
class Queue_heap {
    int idx=0;
    priority_queue<pair<int, T>, vector<pair<int, T> >, Compare_heap<T> > max_heap;

public:
    void push(const T &x) {
        max_heap.emplace(idx--, x);
    }

    T pop() {
        T ret = max_heap.top().second;
        max_heap.pop();
        return ret;
    }

    T peek() {
        return max_heap.top().second;
    }

};

class Star {
    int ID;
    double x, y, z;

public:
    Star(int id, vector<double> &data) : ID(id), x(data[0]), y(data[1]), z(data[2]) {}

    double distance( ) const {
        return sqrt(x*x+y*y+z*z);
    }

    bool operator<(const Star & b) const  {
        return distance() < b.distance();
    }
};

vector<Star> find_closest_stars(istringstream &sin, int k);


#endif // HEAP_H
