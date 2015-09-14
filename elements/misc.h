#ifndef MISC_H
#define MISC_H

#include <vector>
#include <string>
#include <stack>
#include <memory>
#include <mutex>
#include <iostream>

using namespace std;

class Misc
{
public:
    Misc();

    bool checkPushPop(const vector<int> &pushV, const vector<int> &popV);
    void ArrayToOddEvenArray(vector<int> & A);
    void findContinuousSequence(const vector<int> &A, int k);
    void findContinuousSequence2(int n, int k);
    void findContinuousSequence3(int n);

    int findLastElmentInRemove(vector<int> &A, int k);
    int findLastElmentInRemove_efficient(vector<int> &A, int k);

    int findDigit_from1ToN(int n, int digit);

    int Fibonacci(int n);
    int StairJump(int n, const vector<int> &ways);

    int StrToInt(const string str);

    string findLongestCommonSubsequence(const string x, const string y);
    string findLongestCommonSubarray(const string x, const string y);

    void printUglyNum(int k);
    // print the number from 1 to 9999 which has n digits. Using permutation is best choice
    void printNDigits(int n);
    void reverseStack(stack<int> & s);

    void findMinIntCombination(vector<int> & a);
    int minRotateSortArray(const vector<int> &a);

    // O(6^n)
    void calcProbDices(int nDice);
    // O(n*(6*n)*6)
    void calcProbDices_DP(int nDice);

    int getLongestSymmetrySubString(string s);

    double powDouble(double x, int exp);

    int findMajorityNum(const vector<int> &A);

    struct ComplexNode {
        int value;
        shared_ptr<ComplexNode> next;
        shared_ptr<ComplexNode> sibling;
        ComplexNode(int _value) : value(_value), next(nullptr), sibling(nullptr) {}
    };

    shared_ptr<ComplexNode> copyComplexNode(shared_ptr<ComplexNode> & head);

    struct tNode {
        int data;
        shared_ptr<tNode> left;
        shared_ptr<tNode> right;
    };

    bool isSubTree(shared_ptr<tNode> & big, shared_ptr<tNode> &small);

    void printMatrixClockwisely(const vector<vector<int> > &A);

    void printTreePathSum(shared_ptr<tNode> &root, int k);

    // problem 61: page 88
    int maxDiff_DP(const vector<int> &A);
    int maxDiff_divide(const vector<int> &A);
    int maxDiff_subArray(const vector<int> &A);

    // Problem 08
    class Temp{
        static int N;
        static int sum;
    public:
        Temp(){
            N++;
            sum += N;
        }
        static void reset() {
            N=0;
            sum=0;
        }
        static int getSum() {
            return sum;
        }
    };

    int addWithConstrains(int n);

    template<typename T>
    struct ListNode {
        T val;
        ListNode * next;
    };

    template<typename T>
    void reverseList(ListNode<T> * head)
    {
        if (!head || !head->next) return;

        ListNode<T> *curr=head->next, *prev=head, *next;
        prev->next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    template<typename T>
    class SmartPointer {
        T * data;
//        int size;
        int * count;
        void release() {
            (*count)--;
            if (*count==0) {
                if (data) {
                    delete data;
                    data=nullptr;
                }

                delete count;
            }
        }
        SmartPointer(){}

    public:
//        SmartPointer(int _size) : size(_size) {
//            if (size>0) {
//                data = new T[size];
//                count = new int;
//                *count=1;
//            }
//        }
        SmartPointer(T *ptr) {
            if (ptr!=NULL) {
                data = ptr;
                count = new int;
                *count=1;
            }
        }

        SmartPointer(const SmartPointer<T> & that) {
            data=that->data;
            count=that->count;
            (*count)++;
        }

        ~SmartPointer() {
            release();
        }
        SmartPointer & operator=(const SmartPointer<T> & that) {
            if (this == &that)
                return *this;

            release();
            data=that->data;
//            size=that.size;
            count=that->count;
            (*count)++;

            return *this;
        }
        T * operator->() {
            return data;
        }
    };

    class Singleton {
        Singleton(){}
        Singleton(const Singleton & that) {}
        Singleton & operator=(const Singleton & that) {}

        static std::mutex _mutex;
        static shared_ptr<Singleton> instance;

    public:
        static shared_ptr<Singleton> getInstance() {
            if (!instance) {
                std::lock_guard<mutex> lock(_mutex);

                if (!instance)
                    instance.reset( new Singleton());
            }
            return instance;
        }

    };

    struct Interval {
        int low, high;
    };
    struct INode {
        Interval interval;
        int max;
        shared_ptr<INode> left, right;
        INode(Interval &x) : interval(x), max(x.high), left(nullptr), right(nullptr) {}
    };

    class IntervalTree {
        shared_ptr<INode> root;
        bool isOverlap(Interval &x, Interval &y) const {
            return x.high >= y.low && y.high >=x.low;
        }

    public:
        void insert(Interval & x) {
            if (!root)
                root = shared_ptr<INode>(new INode(x));
            auto curr=root;
            shared_ptr<INode> parent=nullptr;
            while (curr) {
                parent = curr;
                curr->max = max(curr->max, x.high);
                if (curr->interval.low > x.low) {
                    curr=curr->left;
                } else {
                    curr=curr->right;
                }
            }
            if (parent->interval.low>x.low)
                parent->left=shared_ptr<INode>(new INode(x));
            else
                parent->right=shared_ptr<INode>(new INode(x));

        }

        Interval search(Interval &x ) const {
            auto curr=root;
            while (curr) {
                Interval tmp = curr->interval;
            if (isOverlap(tmp, x))
                return curr->interval;
            if (curr->left && curr->left->max>=x.low)
                curr= curr->left;
            else
                curr=curr->right;
            }
            return Interval();

        }


    };

//    char* GetString1()
//    {
//    char p[] = "Hello World";
//    return p;
//    }
//    char* GetString2()
//    {
//    char *p = "Hello World";
//    return p;
//    }

//    void testprintA() {
//        char str1[] = "hello world";
//        char str2[] = "hello world";
//        char* str3 = "hello world";
//        char* str4 = "hello world";
//        if(str1 == str2)
//        printf("str1 and str2 are same.\n");
//        else
//        printf("str1 and str2 are not same.\n");
//        if(str3 == str4)
//        printf("str3 and str4 are same.\n");
//        else
//        printf("str3 and str4 are not same.\n");    }
};

#endif // MISC_H
