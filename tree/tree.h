#ifndef TREE_H
#define TREE_H

#include <queue>
#include <list>
#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node * left;
    Node * right;

    Node(T _data) : data(_data), left(NULL), right(NULL)
    {}

private:
    Node(){}
};

template <typename T>
class Tree
{
public:
    Tree();
    ~Tree();

    void deleteTree(Node<T> ** rootNode);

    void build(std::list<T> & values);
    std::list<T> BFS();
    std::list<T> DFS_main();

    void addNodes(T *){}
    bool findNode(T & value);
    Node<T> * getRoot() { return root;}

private:
    Node<T> * root;
    void DFS(std::list<T> & nodeSeq, Node<T> * _root);
};

template <typename T>
Tree<T>::Tree() : root(NULL)
{
}

template <typename T>
Tree<T>::~Tree()
{
    if (root)
        deleteTree( & root);
    root = NULL;
}

template <typename T>
void Tree<T>::deleteTree(Node<T> **rootNode)
{
    Node<T> * curNode = *rootNode;
    if (curNode)
    {
        deleteTree(&(curNode->left));
        deleteTree(&(curNode->right));
        delete curNode;
    }
}

template <typename T>
void Tree<T>::build(std::list<T> & values)
{
    if (root)
        deleteTree( & root);

    root = new Node<T> (0);
//    std::queue<Node<T> * > nodeSeq;
//    nodeSeq.push(root);

//    std::cout << "build" << std::endl;
//    for (typename std::list<T>::iterator itr = values.begin(); itr != values.end(); itr++)
//    {
//        Node<T> * newNode = new Node<T>(*itr);
//        std::cout << newNode->data << " ";
//        Node<T> * curNode = nodeSeq.front();
//        nodeSeq.pop();
//        curNode = newNode;
//        nodeSeq.push(curNode->left);
//        nodeSeq.push(curNode->right);
//    }
    std::cout << "build= "<< root->data << std::endl;

}

template <typename T>
std::list<T> Tree<T>::BFS()
{
    std::list<T> nodeList;
//    if (!root) return nodeList;

    std::queue<Node<T> * > nodeSeq;
    nodeSeq.push(root);

    while(nodeSeq.size()>0)
    {
        Node<T> * curNode = nodeSeq.front();
        nodeSeq.pop();
        if (curNode)
        {
            nodeList.push_back(curNode->data);
            std::cout << curNode->data << " ";
            nodeSeq.push(curNode->left);
            nodeSeq.push(curNode->right);
        }
    }
    return nodeList;

}

template <typename T>
std::list<T> Tree<T>::DFS_main()
{
    std::list<T> nodeSeq;
    DFS(nodeSeq, root);
    return nodeSeq;
}

template <typename T>
void Tree<T>::DFS(std::list<T> & nodeList, Node<T> * _root)
{
    if (_root)
    {
        nodeList.push_back(_root->data);
        DFS(nodeList, _root->left);
        DFS(nodeList, _root->right);
    }
}

template <typename T>
bool Tree<T>::findNode(T &value)
{
    return true;
}

#endif // TREE_H
