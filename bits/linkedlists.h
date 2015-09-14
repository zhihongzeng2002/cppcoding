#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

#include <iostream>
#include <tr1/unordered_set>

//test case for linked list
//traversing the list
//edge cases:
//traversing an empty list
//traversing list where 1+ stored values are NULL
//operations (if applicable):
//deleting from the list
//inserting into the list
//inserting a sub-list into the linked list
//traversing the list backwards (if doubly-linked list)
//concurrency tests (if applicable):
//race condition tests

using namespace std;

template <class T>
struct Node
{
    T data;
    Node *next;
    Node(T d): data(d), next(NULL) {}
};

template <class T>
class linkedList
{
    Node<T> * headptr;
    int count;
public:
    linkedList(): count(0), headptr(NULL) {}
    ~linkedList()
    {
        deleteAllNodes();
    }

    Node<T> * getHead(){ return headptr; }
    int getcount(){ return count; }

    Node<T> * getNthNode(const int n)
    {
        if (count < n) return NULL;

        Node<T> *curPtr=headptr;

        for (int i=0; i<n-1; i++)
            curPtr = curPtr->next;

        return curPtr;
    }

    void addNodeToTail(T d)
    {
        Node<T> * newNode = new Node<T>(d);
        if (!headptr)
        {
            headptr=newNode;
            count++;
            return;
        }

        Node<T> *curPtr = headptr;

        while (curPtr->next)
            curPtr = curPtr->next;

        curPtr->next = newNode;
        count++;
    }

    void deleteNode(T d)
    {
        if (!headptr) return;
        if (headptr->data == d)
        {
            Node<T> *p=headptr;
            headptr=headptr->next;
            delete p;
            count--;
        }
        Node<T> * curPtr = headptr;
        while (curPtr->next && curPtr->next->data != d)
            curPtr = curPtr->next;

        if (!curPtr->next) return;

        Node<T> * t = curPtr->next;
        curPtr->next = curPtr->next->next;
        delete t;
        count--;
    }

    void deleteAllNodes()
    {
        if (!headptr) return;
//        if (!headptr->next)
//        {
//            delete headptr;
//            headptr=NULL;
//            count=0;
//        }
        Node<T> * curPtr = headptr;
        while (curPtr->next)
        {
            Node<T> *temp=curPtr;
            curPtr=curPtr->next;
            delete temp;
            count--;
        }
        headptr=NULL;
    }

    void printAllNodes()
    {
        Node<T> * curPtr=headptr;
        while (curPtr)
        {
            cout << curPtr->data << "->";
            curPtr=curPtr->next;
        }

        std::cout << "NULL" << std::endl;

    }

    void reverseList()
    {
        if (!headptr)  return;

        Node<T> *forwardCur = headptr;
        Node<T> *forwardNext = forwardCur->next;
        forwardCur->next = NULL;

        while (forwardNext)
        {
            Node<T> *temp = forwardCur;
            forwardCur = forwardNext;
            forwardNext=forwardNext->next;
            forwardCur->next = temp;
        }

        headptr=forwardCur;

    }

//    Node<T> * getNode(T d);

    void deleteDuplicates()
    {
//        if (!headptr) return;
//        if (!headptr->next) return;

//        std::unordered_set<T> unique;
//        unique.insert(headptr->data);

//        Node<T> * curPtr = headptr->next;
//        Node<T> * prev = headptr;

//        if (curPtr)
//        {
//            if (unique.find(curPtr->data) != unique.end())
//            {
//                cout << "dup" << endl;
//                Node<T> * temp = curPtr;
//                prev->next = curPtr->next;
//                curPtr = curPtr->next;
//                delete temp;
//            }
//            else
//            {
//                unique.insert(curPtr->data);
//                prev = curPtr;
//                curPtr = curPtr->next;
//            }

//        }


        if (!headptr) return;
        if (!headptr->next) return;
        std::tr1::unordered_set<T> unique;

        Node<T> *curPtr = headptr;
        unique.insert(curPtr->data);
        while (curPtr->next)
        {
            if (unique.find(curPtr->next->data) != unique.end())
            {
//                cout << "dups" << endl;
                Node<T> *temp=curPtr->next;
                curPtr->next=curPtr->next->next;
                delete temp;
                count--;
            }
            else
            {
//                cout << i << endl;
//                i++;
                unique.insert(curPtr->next->data);
                curPtr=curPtr->next;
            }
        }

    }

    void deleteDupsNoBuff()
    {
        // check the simple case
        if (!headptr) return;
        if (!headptr->next) return;

        // using two pointers
        Node<T> * p1 = headptr;
        Node<T> * p2;

        while (p1)
        {
            p2= p1;
            while (p2->next)
            {
                if (p1->data == p2->next->data)
                {
                    Node<T> * temp=p2->next;
                    p2=p2->next->next;
                    delete temp;

                }
                else
                {
                    p2=p2->next;
                }
            }
            p1=p1->next;
        }

    }

    Node<T> * findNthtoLast(int n) // using runner
    {
        if (!headptr) return NULL;

        Node<T> * p = headptr;
        Node<T> * runner = p;
        int i;
        for (i=0; i<n-1 && runner; i++)
            runner = runner->next;

//        cout << "i=" << i << endl;
        if (!runner) return NULL;
//        cout << "runner start at " << runner->data << endl;

        while (runner->next)
        {
            p=p->next;
            runner=runner->next;
        }

        return p;
    }

};

#endif // LINKEDLISTS_H
