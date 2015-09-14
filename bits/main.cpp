#include <iostream>
#include "linkedlists.h"

using namespace std;

void testCases_addNodeToTail();
void testCases_deleteNode();
void testCases_deleteDuplicates();
void testCases_reverse();

int main()
{
// testCase

    // test empty list
    linkedList<double> t;
    t.printAllNodes();

    testCases_addNodeToTail();
    testCases_reverse();
    testCases_deleteNode();

    return 0;
}

void testCases_addNodeToTail()
{
    cout << "test cases for addNode" << endl;
    // add a node to empty list
    linkedList<int> t;
    t.addNodeToTail(1);
    t.addNodeToTail(1);
    // add a sequence
    for (int i=0; i<5; i++)
    {
        t.addNodeToTail(i);
    }
    // add a duplicate sequence
    for (int i=0; i<5; i++)
    {
        t.addNodeToTail(i);
    }
    // show results
    t.printAllNodes();
}

void testCases_deleteDuplicates()
{
    cout << "test cases for deleteDuplicates without buffer" << endl;
    linkedList<int> t;
    t.deleteDupsNoBuff();
    t.printAllNodes();

}

void testCases_reverse()
{
    cout << "test cases for reverse" << endl;
    linkedList<int> t;
        t.reverseList();
        t.printAllNodes();
}

void testCases_deleteNode()
{
    //    t.deleteNode(2);
    //    t.printAllNodes();

        // test delete non-exsist number
    //    t.deleteNode(5);
    //    t.printAllNodes();

    //    t.deleteAllNodes();
    //    t.printAllNodes();
}

void testCases_findNode()
{
linkedList<int> t;
// long list

Node<int> * x = t.findNthtoLast(3);
if (x)
cout << x->data << endl;

}

