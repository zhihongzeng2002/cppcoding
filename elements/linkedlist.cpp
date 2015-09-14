#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList()
{
}

void LinkedList::evenOddList(shared_ptr<Node> &head)
{
    if (!head || !head->next) return;

    shared_ptr<Node> even_cur=head, odd_cur=head->next, odd_head=odd_cur, pre_even=even_cur;

    while(even_cur && odd_cur)
    {
        pre_even=even_cur;
        even_cur->next = odd_cur->next;
        even_cur=even_cur->next;
        if (even_cur)
        {
            odd_cur->next=even_cur->next;
            odd_cur=odd_cur->next;
        }
    }

    if (!odd_cur)
        even_cur->next=odd_head;

    if (!even_cur)
    {
        odd_cur->next=nullptr;
        pre_even->next=odd_head;
    }

}

static void append_advance(shared_ptr<LinkedList::Node> & head, shared_ptr<LinkedList::Node> & tail,
                           shared_ptr<LinkedList::Node> &node) {
    head ? tail->next = node : head = node;
    tail = node;
    node = node->next;
}

shared_ptr<LinkedList::Node> LinkedList::evenOddList2(shared_ptr<Node> head) {
    shared_ptr<Node> even=nullptr, eventail=nullptr, odd=nullptr, oddtail=nullptr;
    while (head) {
        append_advance(even, eventail, head);
        if (head) {
            append_advance(odd, oddtail, head);
        }
    }
    if (eventail)
        eventail->next = odd;
    if (oddtail) oddtail->next=nullptr;
    return even;

}

shared_ptr<LinkedList::Node> LinkedList::evenOddList3(shared_ptr<Node> & L) {
    if (!L || !L->next)
        return L;
    shared_ptr<Node> L0=L, L1=L->next;
    while (L->next) {
        shared_ptr<Node> tmp = L->next;
        L->next = tmp->next;
        L=tmp;
    }
    L=L0;
    while (L->next)
        L=L->next;

    L->next=L1;
    return L0;
}

shared_ptr<LinkedList::Node> LinkedList::buildList(const vector<int> &A) {
    shared_ptr<Node> head=nullptr, tail;
    for (auto & x: A) {
        shared_ptr<Node> node(new Node(x));
        head? tail->next = node : head = node;
        tail = node;
    }
    return head;
}

void LinkedList::print(shared_ptr<Node> head) {
    while (head) {
        cout << head->value << " ";
        head=head->next;
    }
    cout << endl;
}
