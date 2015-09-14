#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <stack>

template <typename T>
class MyQueue
{
public:
    MyQueue();
    void appendTail(const T& node);
    void deleteHead();

private:
    std::stack<T> mStack1;
    std::stack<T> mStack2;
};

template <typename T>
void MyQueue<T>::appendTail(const T &node)
{
    mStack1.push(node);
}

template <typename T>
void MyQueue<T>::deleteHead()
{
    if (!mStack2.size())
    {
        while (mStack1.size())
        {
            T x=mStack1.top();
            mStack1.pop();
            mStack2.push(x);
        }
    }

    assert(mStack2.size()>0);
        mStack2.pop();
}

#endif // MYQUEUE_H
