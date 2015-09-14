#ifndef BST_H
#define BST_H

#include <memory>
#include <vector>
#include "utilities.hpp"
#include <unordered_set>
#include <stdexcept>
#include <unordered_map>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <complex>

using namespace std;

//vector<complex<int> > generate_gaussian_primes(int n);

struct IntervalNode {
    int s, e;
    int maxe; //the highest e of subtrees
    shared_ptr<IntervalNode> left, right;
    IntervalNode(int _s, int _e, int _maxe) : s(_s), e(_e), maxe(_maxe), left(nullptr), right(nullptr) {}
};

class IntervalTree {
    shared_ptr<IntervalNode> root=nullptr;
public:
    void insert(int _s, int _e) {
        if (!root) {
            root = shared_ptr<IntervalNode>(new IntervalNode(_s, _e, _e));
            return;
        }
        auto curr=root, prev=root;
        while (curr) {
            prev=curr;
            curr->maxe = max(curr->maxe, _e);
            if (curr->s > _s)
                curr=curr->left;
            else if (curr->s <_s)
                curr=curr->right;
            else {
                if (curr->e > _e)
                    curr=curr->left;
                else if (curr->e < _e)
                    curr=curr->right;
                else
                    return;
            }
        }
        auto n = shared_ptr<IntervalNode>(new IntervalNode(_s, _e, _e));
        if (prev->s > _s)
            prev->left= n;
        else if (prev->s < _s)
            prev->right = n;
        else {
            if (prev->e > _e)
                prev->left=n;
            else
                prev->right=n;
        }
    }
    shared_ptr<IntervalNode> intervalSearch(int _s, int _e) {
        auto curr=root;
        while (root) {
            if (curr->e > _s && _e >> curr->s)
                return curr;
            if (curr->left && curr->left->maxe>_s)
                curr=curr->left;
            else
                curr=curr->right;
        }
        return nullptr;
    }
};

struct TreeEdgeNode
{
    vector<pair<shared_ptr<TreeEdgeNode>, double> > edges;
};

template<typename T>
class BST
{
public:
    BST();

    void preorder_iterative(const shared_ptr<BSTNode<T> > &root);
    void postorder_iterative(const shared_ptr<BSTNode<T> > &root);
    void printTree(shared_ptr<BSTNode<T> > & node);

    shared_ptr<BSTNode<T> > buildBTFromPreOrderArr(const vector<T> &pre);
    void printInOrderWithParentField_norecursive(const shared_ptr<BSTNode<T> > &root);
    void printPreOrderWithParentField_norecursive(shared_ptr<BSTNode<T> >&root);
    void printPostOrderWithParentField_norecursive(shared_ptr<BSTNode<T> >&root);
    void printBST_norecursive(shared_ptr<BSTNode<T> > &n);

    //14.17, find the most common visited pages which are at time window [currTime-winsize, currTime];
    pair<shared_ptr<BSTNode<T> >, shared_ptr<BSTNode<T> > > convertTreeToList_twoPtr(shared_ptr<BSTNode<T> > &root);
    //14.19
    void calc_view_from_above(const vector<LineSegment> & A);

    int find_min_dist_sorted_arrays(vector<vector<int> > &arr);
    //14.13
    bool is_r_s_descendat_ancestro_m(unique_ptr<TreeNode<T> > &r, unique_ptr<TreeNode<T> > &s, unique_ptr<TreeNode<T> > &m);

    void find_nodes_between(unique_ptr<TreeNode<T> > &r, T minv, T maxv, vector<TreeNode<T> *> &res);
    int find_nodes_between_withSizeField(shared_ptr<BSTNode<T> > &n, T minv, T maxv);

    TreeNode<T> * build_BST_from_preorder(const vector<T> & arr);

    TreeNode<T> * find_LCA(unique_ptr<TreeNode<T> > &root, unique_ptr<TreeNode<T> > &a, unique_ptr<TreeNode<T> > &b);

    vector<T> find_largest_k_elements(const unique_ptr<TreeNode<T> > & root, int k);
    shared_ptr<BSTNode<T> > mergeTwoBST(shared_ptr<BSTNode<T> > & A, shared_ptr<BSTNode<T> > & B);

    void testBSTtoDLL(vector<T> & arr);
    shared_ptr<BSTNode<T> > buildBSTfromVector(const vector<T> & arr, int s, int e);
    void convertBSTtoDLL(shared_ptr<BSTNode<T> > & currNode, shared_ptr<BSTNode<T> > &prevNode, shared_ptr<BSTNode<T> > & listHead);
    shared_ptr<BSTNode<T> > convertDLLtoBST(shared_ptr<BSTNode<T> > & head);

    void testmergeTwoBST(const vector<T> & arr);

    // see Problem 14.15 of the book for min distance definition
    int findMinDistanceSortedArrays(const vector<vector<int> > &arr);

    // view from above: Problem 14.19
    vector<shared_ptr<LineSegment> > computeViewFromAbove(vector<shared_ptr<LineSegment> > &arr);

    //Problem 15.4
    int computeTreeDiameter(shared_ptr<TreeEdgeNode> & node);

    void printPostOrderTraversalWithoutRecursion(shared_ptr<BSTNode<T> > &node);

    //9.8
    shared_ptr<BSTNode<T> > buildTreeFromInorderPreorder(const vector<T> &pre, const vector<T> & in);
    shared_ptr<BSTNode<T> > buildTreeFromInorderPostorder(const vector<T> &pre, const vector<T> & in);

    shared_ptr<BSTNode<T> > reconstruct_preorder(const vector<T> & preorder);

    void print_exterior_bst(const shared_ptr<BSTNode<T> > &root);

    shared_ptr<BSTNode<T> > LCA(shared_ptr<BSTNode<T> > &root, shared_ptr<BSTNode<T> > &a, shared_ptr<BSTNode<T> > &b);

    list<BSTNode<T> > findPathSum(shared_ptr<BSTNode<T> > & root, T sum);

    class BSTree {
        unique_ptr<TreeNode<T> > root = nullptr;
        void ReplaceParentChildLink(TreeNode<T> * par, TreeNode<T> * child, TreeNode<T> * new_link) {
            if (!par)
                return;
            if (par->left.get()==child)
                par->left.reset(new_link);
            else if (par->right.get() == child)
                par->right.reset(new_link);
        }

    public:
        bool insert(const T & key) {
            if (!root.get()) {
                root=unique_ptr<TreeNode<T> >(key, nullptr, nullptr);
                return true;
            } else {
                TreeNode<T>* curr = root.get(), *par;
                while (curr) {
                    par=curr;
                    if (key==curr->data)
                        return false;
                    else if (key>curr->data)
                        curr= curr->right.get();
                    else
                        curr = curr->left.get();
                }
                unique_ptr<TreeNode<T> > node(new TreeNode<T>(key, nullptr, nullptr));

                if (key>par->data)
                    par->right.reset(node.release());
                else
                    par->left.reset(node.release());

                return true;
            }
        }

        bool erase(const T &key) {
            TreeNode<T> * curr= root.get(), *par=nullptr;
            while (curr && curr->data != key) {
                par=curr;
                curr=key<curr->data ? curr->left.get() : curr->right.get();
            }

            if (!curr)
                return false;

            if (curr->right) {
                TreeNode<T> * r_curr=curr->right.get(), *r_par=curr;

                // find the min of right subtree
                while (r_curr->left) {
                    par=curr;
                    r_curr=r_curr->left.get();
                }

                TreeNode<T> * r_curr_right=r_curr->right.release();

                // resolve the min node
                if (r_par->left.get()==r_curr) {
                    r_curr = r_par->left.release();
                    r_par->left.reset(r_curr_right);
                } else {
                    r_curr = r_par->right.release();
                    r_par->right.reset(r_curr_right);
                }
                r_curr->left.reset(curr->left.release());
                if (r_par->right.get()!=r_curr) // if the curr->right==r_curr
                    r_curr->right.reset(r_curr_right); // or r_curr->right.reset(curr->right.release());

                // resolve the deleted node
                if (root.get()==curr)
                    root.reset(r_curr);
                else
                    ReplaceParentChildLink(par, curr, r_curr);


            } else {
                if (root.get()==curr) {
                    root.reset(curr->left.release());
                }
                ReplaceParentChildLink(par, curr, curr->left.release());
            }

        }
    };

    bool is_BST_recursive(const unique_ptr<TreeNode<T> > & root);
    bool is_BST_iterative(const unique_ptr<TreeNode<T> > & root);
    bool is_BST_constSpace(const unique_ptr<TreeNode<T> > & root);

    // problem 14.3
    TreeNode<T>* find_first_equal_k_recursive(const unique_ptr<TreeNode<T> > & root, const T key);
    TreeNode<T>* find_first_equal_k_iterative(const unique_ptr<TreeNode<T> > & root, const T key);

    // 14.4
    TreeNode<T> * find_first_larger_k_iterative(const unique_ptr<TreeNode<T> > &root, const T key);

    // 14.5
    TreeNode<T> * find_k_minBST(const unique_ptr<TreeNode<T> > & root, const T key);

};

// 9.5
template<typename T>
class TreeWithParentNode {
    T data;
    shared_ptr<TreeWithParentNode<T> > left=nullptr, right, parent=nullptr;

public:
    void inorder_travesal(const shared_ptr<TreeWithParentNode<T> > &r) {
        if (!r) return;

        shared_ptr<TreeWithParentNode<T> > prev=nullptr, curr=r, next;
        while (curr) {
            if (!prev || prev->left==curr || prev->right==curr) {
                if (curr->left) {
                    next = curr->left;
                } else {
                    cout << curr->data << endl;
                    next = prev->right ? prev->right : curr->parent;
                }

            } else if (curr->left==prev) {
                cout << curr->data << endl;
                next = curr->right ? curr->right : curr->parent;

            } else {
                next = curr->parent;
            }

            prev=curr;
            curr=next;

        }

    }

    int getHeight(shared_ptr<TreeWithParentNode<T> > &n) {
        int h=0;
        while (n) {
            h++;
            n=n->parent;
        }
        return h;
    }

    shared_ptr<TreeWithParentNode<T> > LCA(shared_ptr<TreeWithParentNode<T> > &root, shared_ptr<TreeWithParentNode<T> > &a,
                                           shared_ptr<TreeWithParentNode<T> > &b) {
        int h_a=getHeight(a);
        int h_b=getHeight(b);
        if (h_b>h_a)
            swap(a, b);

        int diff=abs(h_a-h_b);
        while (diff--) {
            a=a->parent;
        }

        while (a!=b) {
            a=a->parent;
            b=b->parent;
        }
        return a;
    }

    shared_ptr<TreeWithParentNode<T> > LCA_hash(shared_ptr<TreeWithParentNode<T> > &root, shared_ptr<TreeWithParentNode<T> > &a,
                                           shared_ptr<TreeWithParentNode<T> > &b) {
        unordered_set<shared_ptr<TreeWithParentNode<T> > >hash;
        while (a || b) {
            if (a) {
                auto t = hash.emplace(a);
                if (t->second==false)
                    return a;
                a=a->parent;
            }
            if (b) {
                if (hash.emplace(b)->second==false)
                    return b;
                b=b->parent;
            }
        }
        throw invalid_argument("there is no LCA");
    }
};

template<typename T>
class Trie {
    bool isString;
    unordered_map<char, shared_ptr<Trie<T> > > dict;

public:
    void insert(const string &s) {
        unordered_map<char, shared_ptr<Trie<T> > > curr = dict;
        for (auto &c : s) {
            curr.emplace(c, shared_ptr<Trie<T> >(new Trie<T>()));
            curr = curr[c];
        }

    }

    string findPrefix(const string &s) {
        string res;
        unordered_map<char, shared_ptr<Trie<T> > > curr = dict;
        for (auto &c : s) {
            res += c;
            if (curr.find(c) == curr.end())
                return res;
            curr = curr[c];
        }
        return string();
    }
};

template<typename T>
string findPrefix(const vector<string> &dict, const string &s) {
    Trie<T> D;
    for (auto &c : dict) {
        D.insert(c);
    }

    return D.findPrefix(s);
}

struct CompFreq {
    bool operator()(const pair<int, int> &x, const pair<int, int> &y) {
    return x.second != y.second ? x.second > y.second : x.first > y.first;
    }
};

class LogAnalyzer {
    queue<pair<int, int> > Q; // timestamp, ipaddress
    set<pair<int,int>, CompFreq> B; // ipaddress, frequency;
    unordered_map<int, set<pair<int,int>, CompFreq>::iterator > M; //ipaddress, map iterator
    int winSize;
    void popItems(int timestamp);

public:
    LogAnalyzer(int w) : winSize(w) {}
    void add(int ipaddress, int timestamp);
    vector<int> common(int timestamp, int k); // return the k most common visited ipaddress in the time windowsize
};

#include "bst.hpp"

#endif // BST_H
