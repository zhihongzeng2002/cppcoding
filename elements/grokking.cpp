#include "grokking.h"
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>

void Grokking::pythagoreamTriplets(int limit) {
    int a, b, c=0;
    int m=2;
    while (c<limit) {
        for (int n=1; n<m; n++) {
            a = m*m - n*n;
            b = 2*m*n;
            c = m*m + n*n;
            if (c>limit)
                break;
            else {
                cout <<a << " " << b << " " << c << endl;
            }
        }
        m++;
    }
}

int Grokking::findMissNumber(vector<int> &A){
    int miss_dup_xor = 0;
    for (int i=0; i<A.size(); i++)
        miss_dup_xor ^=i^A[i];

    int h = miss_dup_xor & (~(miss_dup_xor-1));

    int miss_dup = 0;
    for (int i=0; i<A.size(); i++) {
        if (i&h)
            miss_dup ^= i;
        if (A[i] & h)
            miss_dup ^= A[i];
    }

    for (int i=0; i<A.size(); i++){
        if (A[i]==miss_dup)
            return miss_dup ^ miss_dup_xor;
    }
    return miss_dup;
}

int Grokking::findMissNumber_easy(vector<int> &A){
    // put the element in the right position; easy sort
    for (int i=0; i<A.size(); i++) {
        while (A[i]>=0 && A[i] <A.size() && A[i]-1 != i)
            swap(A[i], A[A[i]-1]);
    }

    for (int i=0; i<A.size(); i++) {
        if (A[i]-1 != i)
            return i+1;
    }
    return -1;
}

shared_ptr<Grokking::TNode> Grokking::Inorder_successor(shared_ptr<TNode> &root, shared_ptr<TNode> &node){
    if (node->right) {
        shared_ptr<TNode> curr = node->right;
        while (curr->left)
            curr = curr->left;
        return curr;
    }

    shared_ptr<TNode> n = root, succ=nullptr;
    while (n) {
        if (n->data > node->data) {
            succ = n;
            n = n->left;
        } else if (n->data < node->data) {
            n = n->right;
        } else if (n->data == node->data && n==node)
            n = n->right;
        else
            break;
    }
    return succ;
}

shared_ptr<Grokking::TNode> Grokking::Inorder_successor_parentPointers(shared_ptr<TNode> &node){
    if (node->right) {
        auto n = node->right;
        while (n->left)
            n = n->left;
        return n;
    }

    while (node && node->parent->left != node) {
        node = node->parent;
    }
    return node->parent;

}

shared_ptr<Grokking::TNode> Grokking::serialize_to_bst(vector<string> &A){
    stack<shared_ptr<TNode> > T;
    for (int i=A.size()-1; i>=0; i--) {
        if (A[i]=="#")
            T.push(nullptr);
        else {
            auto left = T.top();
            T.pop();
            auto right = T.top();
            T.pop();
            shared_ptr<TNode> node(new TNode(stoi(A[i]), left, right));
            T.push(node);
        }

    }
    return T.top();

}

vector<string> Grokking::bst_deserialize(shared_ptr<TNode> &A){
    vector<string> ans;
    if (!A)
        return ans;
    queue<shared_ptr<TNode> >Q;
    Q.push(A);
    while (!Q.empty()) {
        auto n = Q.front();
        ans.push_back(to_string(n->data));
        if (n->left)
            Q.push(n->left);
        else
            ans.push_back("#");
        if (n->right)
            Q.push(n->right);
        else
            ans.push_back("#");
    }
    return ans;

}

static int deleteZeroSumSubTree_helper(shared_ptr<Grokking::TNode> &root) {
    int x=0,y=0;
    if (root->left) {
        x=deleteZeroSumSubTree_helper(root->left);
        if (!x)
            root->left = nullptr;
    }
    if (root->right) {
        y=deleteZeroSumSubTree_helper(root->right);
        if (!y)
            root->right = nullptr;
    }
    return x+y+root->data;
}

void Grokking::deleteZeroSumSubTree(shared_ptr<TNode> &root) {
    if (!root) return;
    int sum = deleteZeroSumSubTree_helper(root);
    if (!sum)
        root = nullptr;
}

void static cloneGraph_helper(shared_ptr<Grokking::GNode> &root, unordered_map<shared_ptr<Grokking::GNode>, shared_ptr<Grokking::GNode> > &T) {
    shared_ptr<Grokking::GNode> node(new Grokking::GNode(root->data));
    T[root] = node;
    for (auto &e: root->edges) {
        if (T.find(e) == T.end()) {
            cloneGraph_helper(e, T);
        }
        node->edges.push_back(T[e]);
    }
}

shared_ptr<Grokking::GNode> Grokking::cloneGraph(shared_ptr<GNode> &root){
    if (!root) return nullptr;
    unordered_map<shared_ptr<GNode>, shared_ptr<GNode> > T;
    cloneGraph_helper(root, T);
    return T[root];
}

//list
void copyComplexList_helper(shared_ptr<Grokking::LNode> & head, unordered_map<shared_ptr<Grokking::LNode>, shared_ptr<Grokking::LNode> > &T) {
    shared_ptr<Grokking::LNode> node(new Grokking::LNode(head->data));
    T[head] = node;
    if (head->next){
        auto x = head->next;
        if (T.find(x)==T.end()) {
            copyComplexList_helper(x, T);
        }
        node->next = T[x];
    }
    if (head->jump){
        auto x = head->jump;
        if (T.find(x)==T.end()) {
            copyComplexList_helper(x, T);
        }
        node->jump = T[x];
    }

}

shared_ptr<Grokking::LNode> Grokking::copyComplexList(shared_ptr<LNode> &head) {
    if (!head) return nullptr;
    unordered_map<shared_ptr<LNode>, shared_ptr<LNode> > T;
    copyComplexList_helper(head, T);
    return T[head];

}

void Grokking::boggle_matrix_wordfinding(vector<vector<char> > &A){

}
