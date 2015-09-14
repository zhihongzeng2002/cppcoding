#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "utilities.hpp"
#include <stack>

class Stackqueue
{
public:
    Stackqueue();

    int reverserPolishNotation(string s);
    void sortStackInPlace(stack<int> & S);
    void reverseStackInPlace(stack<int> & S);

    template<typename T>
    void print_in_sorted_bst(shared_ptr<BSTNode<T> > & n) {
        stack<shared_ptr<BSTNode<T> > > s;
        shared_ptr<BSTNode<T> > curr = n;

        while (!s.empty() || curr) {
            if (curr) {
                s.push(curr);
                curr = curr.left;
            } else {
                curr = s.top();
                s.pop();
                cout << curr.data << endl;
                curr = curr.right;
            }
        }
    }

    template<typename T>
    void search_posting_list_helper(const shared_ptr<BSTNode<T> > &L, int & order) {
        if (L && L.order==-1) {
            L.order=order++;
            search_posting_list_helper(L->left, order);
            search_posting_list_helper(L->right, order);
        }
    }

    template<typename T>
    void search_posting_list_recursive(const shared_ptr<BSTNode<T> > &L) {
        int order=0;
        search_posting_list_helper(L, order);
    }

    template<typename T>
    void search_posting_list_iterative(const shared_ptr<BSTNode<T> > &L) {
        stack<shared_ptr<BSTNode<T> > > s;
        s.push(L);
        int order=0;

        if (!s.empty()) {
            shared_ptr<BSTNode<T> > curr = s.top();
            s.pop();
            if (curr && curr->order==-1) {
                curr->order=order++;
                s.push(curr->left);
                s.push(curr->right);
            }
        }
    }

};

#endif // STACKQUEUE_H
