#ifndef MYLIST_H
#define MYLIST_H

#include <memory>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

struct Node{
    int value;
    shared_ptr<Node> pNext;
    Node(int _value): pNext(nullptr), value(_value) {}
    Node(){}
};

struct ComplexNode
{
    int value;
    shared_ptr<ComplexNode> next;
    shared_ptr<ComplexNode> sibling;
    ComplexNode(): value(0), next(nullptr), sibling(nullptr)
    {
    }
    ComplexNode(int _value): value(_value), next(nullptr), sibling(nullptr)
    {
    }
};


class MyList
{
    shared_ptr<Node> head;
    MyList(const MyList & );
    const MyList & operator()(const MyList &);
    void printNode(shared_ptr<Node> node);
public:

    MyList(const int * seq, const int length);
    MyList(vector<int> arr);
    void printList();
    shared_ptr<Node> findNthToLast(const int n);
    void printListReverse();
    void printListReverse2(shared_ptr<Node> &node);
    void deleteNode(int _value);
    void deleteAll();
    shared_ptr<Node> findFirstCommonNode(shared_ptr<Node> &firstLink, shared_ptr<Node> & secondLink);
    void deleteDups();
    void deleteDup2();

    shared_ptr<Node> getHead() {return head; }

    shared_ptr<ComplexNode> copyComplexNode(shared_ptr<ComplexNode> headptr);

    shared_ptr<Node> mergeLists(shared_ptr<Node> & list0, shared_ptr<Node> & list2);

    void deleteNodeWithLastNodePointerToMiddle(shared_ptr<Node> & head, int deleteValue);

    void alternateNodes(); /// a->b->c->d ==> b->a->d->c


};

// Iterator implementation
template<class T>
struct NestedNode
{
    T value;
    NestedNode<T> * node;
    NestedNode<T> * nested;
    NestedNode() : value(0), node(nullptr), nested(nullptr) {}
    NestedNode(T _value, NestedNode<T> * _node, NestedNode<T> * _nested)
        : value(_value), node(_node), nested(_nested) {}
};

template<class T>
class NestedIterator
{
public:
    NestedIterator(NestedNode<T> * head)
    {
        mstack.push(head);
    }

    NestedNode<T> * next()
    {
        if (mstack.empty()) return nullptr;

        NestedNode<T> *pCur = mstack.top();
        mstack.pop();;

        if (pCur->node != nullptr)
            mstack.push(pCur->node);
        if (pCur->nested != nullptr)
            mstack.push(pCur->nested);
        return pCur;
    }

private:
    stack<NestedNode<T> *> mstack;
};

template <class T>
class NestedList
{
public:
    NestedList(): phead(nullptr) {}
    void push_pack(NestedNode<T> * node)
    {
        if (phead==nullptr) phead=node;
        else
        {
            phead->node=node;
        }
    }
    NestedNode<T> * head() { return phead;}

private:
    NestedNode<T> * phead;

};


#endif // MYLIST_H
