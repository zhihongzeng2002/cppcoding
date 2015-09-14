#ifndef STACK_H
#define STACK_H

#include <deque>
#include <assert.h>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Stack
{
public:
    void push(const T value);
    void pop();
    T minValue();
    size_t getDataSize(){ return data.size(); }
    static void reverseStack(stack<T> &mystack);
    static void sortStack(stack<T> & mystack);
    static void simulateHanoiTower(const int k);

private:
    deque<T> data;
    deque<size_t> minIndex;
    static void addStackBottom(stack<T> & mystack, T top);

};

template <typename T>
void Stack<T>::sortStack(stack<T> &mystack)
{
    if (mystack.empty()) return;
    stack<T> buff;
    while(!mystack.empty())
    {
        T temp = mystack.top();
        mystack.pop();
        while (!buff.empty() && temp< buff.top())
        {
            T x = buff.top();
            buff.pop();
            mystack.push(x);
        }
        buff.push(temp);

    }

    // reverse
    while (!buff.empty())
    {
        T x = buff.top();
        buff.pop();
        mystack.push(x);
    }

    // print
    while (!mystack.empty())
    {
        cout << mystack.top() << ' ';
        mystack.pop();
    }
    cout << endl;

}

template <typename T>
void Stack<T>::reverseStack(stack<T> &mystack)
{
    if (mystack.empty()) return;
    T top=mystack.top();
    mystack.pop();
    reverseStack(mystack);
    addStackBottom(mystack, top);
}

template <typename T>
void Stack<T>::addStackBottom(stack<T> &mystack, T top)
{
    if (mystack.empty()) mystack.push(top);
    else
    {
        T x=mystack.top();
        if (top > x)
        {
        mystack.pop();
        addStackBottom(mystack, top);
        mystack.push(x);
        }
        else
            mystack.push(top);
    }
}

template <typename T>
void Stack<T>::push(const T value)
{
    data.push_back(value);
    if (minIndex.size()==0)
    {
        minIndex.push_back(0);
    }
    else
    {
//        cout << "cur=" << value << "; min=" << data[minIndex.back()];
//        minIndex.push_back(0);

        if (value<data[minIndex.back()])
            minIndex.push_back(data.size()-1);
        else
            minIndex.push_back(minIndex.back());
    }
}

template <typename T>
void Stack<T>::pop()
{
    if (data.size()==0) return;
    data.pop_back();;
    minIndex.pop_back();
}

template <typename T>
T Stack<T>::minValue()
{
    assert(data.size()>0);
    return data[minIndex.back()];
}

class Tower
{
public:
    Tower(const int _index): index(_index){}
    bool add(const int x);
    bool moveTopTo(Tower & t);
    void moveDisks(int x, Tower & dest, Tower & buffer);
    int getIndex() { return index; }

    void print();

private:
    int index;
    stack<int> disks;

};

bool Tower::add(const int x)
{
    if (disks.empty())
    {
        disks.push(x);
    }
    else
    {
        if (x<disks.top())
        {
            disks.push(x);
        }
        else
            return false;
    }
    return true;
}

bool Tower::moveTopTo(Tower &t)
{
    if (disks.empty()) return false;
    int x = disks.top();
    if (t.add(x))
    {
        disks.pop();
        cout << "Move " << x << " from Tower " << getIndex() << " to " << " Tower " << t.getIndex() << endl;
        return true;
    }
    else
    {
        cout << "FAIl TO move " << x << " from Tower " << getIndex() << " to " << " Tower " << t.getIndex() << endl;
        return false;
    }
}

void Tower::moveDisks(int x, Tower &dest, Tower &buffer)
{
    if (x<0) return;

    moveDisks(x-1, buffer, dest);
    moveTopTo(dest);
    buffer.moveDisks(x-1, dest, *this);
}

void Tower::print()
{
    stack<int> temp;
    while (!disks.empty())
    {
        int x=disks.top();
        cout << x << ' ' ;
        disks.pop();
        temp.push(x);

    }

    while (!temp.empty())
    {
        disks.push(temp.top());
        temp.pop();
    }

    cout << endl;
}

template <typename T>
void Stack<T>::simulateHanoiTower(const int k)
{
    Tower tower0(0), tower1(1), tower2(2);
    for (int i=k-1; i>=0; i--)
        tower0.add(i);
    cout << "Initial status (only tower0)" << endl;
    tower0.print();

    cout << "Simulation begins" << endl;

    tower0.moveDisks(k, tower2, tower1);

    cout << "Simulation results" << endl;
    cout<< "Tower 0: ";    tower0.print();
    cout<< "Tower 1: ";    tower1.print();
    cout<< "Tower 2: ";    tower2.print();
}

void sortStack2(stack<int> &t)
{
    if (t.empty()) return;
    stack<int> buff;
    while(!t.empty())
    {
        int x=t.top();
        t.pop();
        while (!buff.empty() && x < buff.top())
        {
            int y=buff.top();
            buff.pop();
            t.push(y);
        }
//        cout << __LINE__ << ":" << x << endl;
        buff.push(x);
    }

    while(!buff.empty())
    {
        int x=buff.top();
        buff.pop();
        t.push(x);
    }

    while(!t.empty())
    {
        cout << t.top() << " ";
        t.pop();
    }
    cout << endl;
}

bool isPushPopMatch(vector<int> & pushVect, vector<int>& popVect)
{
    if (pushVect.empty() || popVect.empty() || pushVect.size() != popVect.size()) return false;

    int indexPush=0;
    stack<int> buff;

    for (int i=0; i<popVect.size(); i++)
    {
        int x=popVect[i];
        while ( (buff.empty() || x!=buff.top() ) && indexPush<pushVect.size() )
        {
            buff.push(pushVect[indexPush]);
            indexPush++;
        }

        if (x==buff.top())
        {
            buff.pop();
        }
        else
            return false;

    }
    return true;
}


#endif // STACK_H
