#include "mylist.h"
#include <iostream>
#include <set>

void testNestedIterator()
{
    NestedList<int> nlist;
    nlist.push_pack(new NestedNode<int>(1, nullptr, nullptr));
    nlist.push_pack(new NestedNode<int>(2, new NestedNode<int>(3, nullptr, nullptr), nullptr));

    NestedIterator<int> itr(nlist.head());
    NestedNode<int> *pNode=itr.next();
    while(pNode != nullptr)
    {
        cout << pNode->value << " " << endl;
        pNode=itr.next();
    }
    cout << endl;

}

/**
 * @brief MyList::alternateNodes
 *given linked list a->b->c->d->e convert to
b->a->d->c->e without creating new node.
 */
void MyList::alternateNodes()
{
//    printList();
    if (!head || !head->pNext) return;
    shared_ptr<Node> cur=head, next, prev, nextnext;

    while (cur)
    {
        next=cur->pNext;
        if (!next) break;
        nextnext=next->pNext;
        if (cur==head)
        {
            head=next;
        }
        else
        {
            prev->pNext=next;
        }
        next->pNext=cur;
        cur->pNext=nextnext;
        prev=cur;
        cur=nextnext;
    }
//    printList();
}

/**
 * @brief MyList::deleteDups. There is a bug which does not work for seq list like "1 1". Using deleteDup2 instead
 */
void MyList::deleteDups()
{
    if (!head) return;

    shared_ptr<Node> curPtr = head;
    shared_ptr<Node> prePtr = head;
    while (curPtr->pNext)
    {
        shared_ptr<Node> runner = head;
        while (runner != curPtr)
        {
            if (runner->value == curPtr->value)
            {
                prePtr->pNext = curPtr->pNext;
                curPtr = curPtr->pNext;
                break;
            }
            runner = runner->pNext;
        }
        if (runner == curPtr)
        {
            prePtr = curPtr;
            curPtr = curPtr->pNext;
        }
    }
}

MyList::MyList(vector<int> arr)
{
    if (arr.empty()) return;

    shared_ptr<Node> prev;
    for (int i=0; i<arr.size() ; i++)
    {
        shared_ptr<Node> node(new Node(arr[i]));
        if (i==0)
        {
            head=node;
            prev=node;
            continue;
        }
        prev->pNext=node;
        prev=node;
    }
}

MyList::MyList(const int * seq, const int length)
{
    if (!seq || length<=0) return;

    shared_ptr<Node> previous;
    for (int i=0; i<length; i++)
    {
        shared_ptr<Node> newNode(new Node(seq[i]));
        if (!i)
        {
            previous = newNode;
            head=newNode;
            continue;
        }

        previous->pNext = newNode;
        previous = newNode;

    }
}

void MyList::printList()
{
    shared_ptr<Node> curPtr = head;
    while(curPtr)
    {
        cout << curPtr->value << ' ' ;
        curPtr = curPtr->pNext;
    }
    cout << endl;
}

shared_ptr<Node> MyList::findNthToLast(const int n)
{
    if (!head || n<1) return nullptr;

//    shared_ptr<Node> pRight = head;
    shared_ptr<Node> pLeft = nullptr;

    int count=1;
    for (shared_ptr<Node> temp = head; temp; temp=temp->pNext, count++ )
    {
        if (count == n)
        {
            pLeft = head;
        }
        else if (count > n)
        {
            pLeft = pLeft->pNext;
        }

    }
    return pLeft;
}

void MyList::printListReverse()
{
    if (!head) return;
    printNode(head);
    cout << endl;
}

void MyList::printNode(shared_ptr<Node> node)
{
    if (!node) return;
    printNode(node->pNext);
    cout << node->value << ' ' ;
}

void MyList::deleteNode(int _value)
{
    cout <<_value <<':';

    if (!head)
    {
        cout << "empty list" << endl;
        return;
    }

    shared_ptr<Node> node = head;


    // find the node
    while (node)
    {
        if (node->value == _value)
            break;

        node = node->pNext;
    }

    if (!node)
    {
        cout <<  ": there is no such node" << ' ';
        return;
    }
    if (node->pNext)
    {
//        shared_ptr<Node> temp = node;
        node->value = node->pNext->value;
        node->pNext = node->pNext->pNext;

    }
    else  // this is the last element
    {
        if (head==node)
        {
            head = nullptr;
            return;
        }
        shared_ptr<Node> curPrev = head;

        while (curPrev->pNext != node)
            curPrev = curPrev->pNext;

        curPrev->pNext = nullptr;

    }
}

void MyList::deleteAll()
{
    if (!head) return;
    head=nullptr;
}

static int getLength(const shared_ptr<Node> &listHead)
{
    shared_ptr<Node> node = listHead;
    int len=0;
    while (node)
    {
        len++;
        node=node->pNext;
    }
    return len;
}

shared_ptr<Node> MyList::findFirstCommonNode(shared_ptr<Node> &firstList, shared_ptr<Node> &secondList)
{
    if (!firstList || !secondList) return nullptr;

    // find the lengths of link
    int firstLen = getLength(firstList);
    int secondLen = getLength(secondList);

    shared_ptr<Node> firstRunner=firstList, secondRunner=secondList;
    if (firstLen > secondLen)
    {
        int dif=firstLen-secondLen;
        for (int i=0; i< dif; i++) firstRunner = firstRunner->pNext;
    }
    else
    {
        int dif=secondLen-firstLen;
        for (int i=0; i< dif; i++) secondRunner = secondRunner->pNext;
    }

        while (firstRunner && secondRunner && (firstRunner != secondRunner))
        {
            firstRunner=firstRunner->pNext;
            secondRunner = secondRunner->pNext;
        }

        return firstRunner;

}

shared_ptr<ComplexNode> MyList::copyComplexNode(shared_ptr<ComplexNode> headptr)
{
    if (!headptr) return nullptr;

    shared_ptr<ComplexNode> nodeptr=headptr;

    while(!nodeptr)
    {
        shared_ptr<ComplexNode> temp(new ComplexNode(nodeptr->value));
        temp->next=nodeptr->next;
        nodeptr->next=temp;
        nodeptr=temp->next;
    }

    nodeptr=headptr;
    while(!nodeptr)
    {
        nodeptr->next->sibling=nodeptr->sibling->next;
        nodeptr=nodeptr->next->next;
    }

    nodeptr=headptr;
    shared_ptr<ComplexNode> copyhead=nodeptr->next;
    shared_ptr<ComplexNode> copyptr=copyhead;
    while (!nodeptr)
    {
        nodeptr->next=copyptr->next;
        copyptr->next=nodeptr->next->next;
        nodeptr=nodeptr->next;
    }

    return copyhead;
}

void MyList::deleteDup2()
{
    if (!head) return;

    shared_ptr<Node> preNode=head;
    shared_ptr<Node> leftNode=head;
    shared_ptr<Node> curNode;

    while(leftNode)
    {
        curNode=preNode->pNext;
        preNode=curNode;
        while (curNode)
        {
            if (curNode->value==leftNode->value)
            {
                preNode->pNext=curNode->pNext;
            }
            else
                preNode=curNode;

            curNode=preNode->pNext;
        }
        leftNode=leftNode->pNext;
//        preNode=leftNode;
    }
}

void MyList::printListReverse2(shared_ptr<Node> &node)
{
    if (!node) return;

    printListReverse2(node->pNext);
    cout << node->value << " ";
}

/**
 * @brief MyList::mergeLists: merge two sorted lists
 * @param list0
 * @param list1
 * @return
 */
shared_ptr<Node> MyList::mergeLists(shared_ptr<Node> &list0, shared_ptr<Node> &list1)
{
    if (!list0) return list1;
    if (!list1) return list0;

    shared_ptr<Node> node0=list0;
    shared_ptr<Node> node1=list1;
    shared_ptr<Node> headerM=nullptr;
    shared_ptr<Node> nodeM=nullptr;

    while(node0 || node1)
    {
        shared_ptr<Node> temp;
        if (node0 && node1)
        {
            if (node0->value==node1->value)
            {
                temp=shared_ptr<Node>(new Node(node0->value));
                node0=node0->pNext;
                node1=node1->pNext;

            }
            else if (node0->value > node1->value)
            {
                temp=shared_ptr<Node>(new Node(node1->value));
                node1=node1->pNext;
            }
            else
            {
                temp=shared_ptr<Node>(new Node(node0->value));
                node0=node0->pNext;
            }
        }
        else if (node0)
        {
            temp=shared_ptr<Node>(new Node(node0->value));
            node0=node0->pNext;
        }
        else
        {
            temp=shared_ptr<Node>(new Node(node1->value));
            node1=node1->pNext;

        }

//        cout << temp->value << endl;

        if (!headerM)
        {
            nodeM=temp;
            headerM=temp;
        }
        else
        {
            nodeM->pNext=temp;
            nodeM=nodeM->pNext;
        }
    }

    return headerM;
}

/**
 * @brief MyList::deleteNodeWithLastNodePointerToMiddle
 *C program to Delete a node from SLL, in which the last node points to the middle node
 *( in case of even no of nodes, it points to the first middle node) and update the SLL
 * Note: using additional array could simplify the solution a lot: first go through the list with push_back the node to a vector, then delete the node in the list,
 * then set the pNext of tail to the middle
 * Otherwise: working on the list, there are a lot special cases need to handle: head, tail, middle, change the pNext of tail, even and odd number of list nodes. That will bring many bugs
 * @param head
 * @param deleteValue
 */
void MyList::deleteNodeWithLastNodePointerToMiddle(shared_ptr<Node> &head, int deleteValue)
{
//    if (!head || head->pNext==head) return;

//    shared_ptr<Node> slow=head, fast=head, middle, middle_prev=head, slow_prev=head, tail, tail_prev=head, deleteNode;

//    while (fast->pNext==slow || fast==slow_prev)
//    {
//        if (slow->value==deleteValue)
//            deleteNode=slow;

//        slow_prev=slow;
//        tail=fast;
//        slow=slow->pNext;
//        fast=fast->pNext->pNext;
//        tail_prev=tail;
//    }

//    if (fast->pNext==slow) // even nodes
//    {
//        middle_prev=slow_prev;
//        middle=slow;
//        tail=fast;
//    }
//    else
//    {
//        middle=fast;
//    }

//    switch (deleteNode->value)
//    {
//    case head->value:
//        head=head->pNext;
//        if (deleteNode == middle)
//        {
//            tail->pNext=head;
//        }
//        break;
//    case middle->value:
//        middle=middle->pNext;
//        if (fast->pNext==slow)
//        {
//            tail->pNext=middle_prev;
//        }
//        else
//            tail->pNext=middle;
//        break;
//    case tail->value:
//        break;
//    default:

//    }



}
