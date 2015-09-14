#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include <vector>

using namespace std;

class LinkedList
{
public:
    LinkedList();

    struct Node
    {
        int value;
        std::shared_ptr<Node> next;
        Node(int x) : value(x), next(nullptr) {}
    };

    void evenOddList(shared_ptr<Node> & head);
    shared_ptr<Node> evenOddList2(shared_ptr<Node> head);
    shared_ptr<Node> evenOddList3(shared_ptr<Node> &L);

    void print(shared_ptr<Node> head);
    shared_ptr<Node> buildList(const vector<int> &A);
};

#endif // LINKEDLIST_H
