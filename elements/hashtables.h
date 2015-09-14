#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include "utilities.hpp"
#include <list>

using namespace std;

class HashTables
{
public:
    HashTables();

    // 12.11
    vector<string> findMajorityWords_general(istringstream &sin, int k);
    // 12.13
    vector<string> kSuspiciousStrings(const vector<string> & S, int k);

    int chessHash(const vector<vector<int> > &B);

    class BNode {
        int computeHashcode() {
            return key+ (left?5*left->hashcode:0)+ (right?7*right->hashcode:0);
        }

    public:
        shared_ptr<BNode> left;
        shared_ptr<BNode> right;
        int hashcode;
        int key;

        BNode(int _key, shared_ptr<BNode> & _left, shared_ptr<BNode> & _right) : key(_key), left(_left), right(_right), hashcode(computeHashcode()) {}
//        BNode() : key(0), left(nullptr), right(nullptr), hashcode(0) {}

//        bool operator==(const BNode & that) const {
//            return left==that.left && right==that.right && key==that.key;
//        }
    };

    struct HashBNode {
        int operator()(const shared_ptr<BNode> & that) const {
            return that->key*3+5*(that->left ? that->left->hashcode : 0) + 7*(that->right ? that->right->hashcode : 0);
        }
    };

    struct EqualBNode {
        bool isEqual(const shared_ptr<BNode> &a, const shared_ptr<BNode> &b) const {
            if (!a && !b) return true;
            if (!a && b || a && !b) return false;
            return a->key == b->key && isEqual(a->left, b->left) && isEqual(a->right, b->right);
        }
        bool operator()(const shared_ptr<BNode> & a, const shared_ptr<BNode> &b) const {
            isEqual(a, b);
        }
    };

    shared_ptr<BNode> buildCannonicTree_helper(
                                 shared_ptr<BSTNode<int> > &n,
                                 unordered_set<shared_ptr<BNode>, HashBNode, EqualBNode > &table);
    vector<shared_ptr<BNode> > buildCannonicTree(vector<shared_ptr<BSTNode<int> > > & nodes);

//    shared_ptr<BNode> toCanonicalNode(shared_ptr<BNode> & node, unordered_map<shared_ptr<BNode>, shared_ptr<BNode>, HashBNode > & table) {
//        shared_ptr<BNode> left(node->left==nullptr ? nullptr : toCanonicalNode(node->left, table));
//        shared_ptr<BNode> right(node->right==nullptr ? nullptr : toCanonicalNode(node->right, table));
//        shared_ptr<BNode> des(new BNode(node->key, left, right));

//        auto it = table.find(node);
//        if (it == table.end()) {
//            table[node] = des;
//            return des;
//        } else
//            return table[node];
//    }

    unordered_set<shared_ptr<BNode>, HashBNode > getCanonicalNode(vector<shared_ptr<BNode> > & src) {
        unordered_set<shared_ptr<BNode>, HashBNode > table;
        for (auto & x : src)
            table.emplace(x);
//            toCanonicalNode(x, table);
        return table;
    }

    template<size_t capacity>
    class LRUCache {
        unordered_map<int, pair<list<int>::iterator, int> > table;
        list<int> data_;
        void moveToFront(int isbn) {
            auto it = table.find(isbn) ;
            data_.erase(it->second.first);
            data_.emplace_front(isbn);
            it->second.first=data_.begin();
        }

    public:
        bool lookup(int isbn, int &price) {
            auto it = table.find(isbn) ;
            if (it == table.end())
                return false;
            price = it->second.second;
            moveToFront(isbn, it);
            return true;
        }

        void insert(int isbn, int price) {
            auto it=table.find(isbn);
            if (it == table.end()) {
                if (data_.size()==capacity) {
                    table.erase(data_.back());
                    data_.pop_back();
                }
                data_.push_front(isbn);
                table[isbn]= pair<list<int>::iterator, int>(data_.begin(), price);
            } else {
                moveToFront(isbn, it);
                it->second.second = price;
            }

        }

        void erase(int isbn) {
            auto it=table.find(isbn);
            if (it==table.end())
                return;
            data_.erase(it->second.first);
            table.erase(it);
        }

    };

    //You are given an array that contains integers. The integers content is such that every integer occurs 3 times in that array leaving one integer that appears only once.
//    Fastest way to find that single integer

    int findIntAppearOnce(vector<int> & arr);

    pair<int, int> find_smallest_subarray_covering_subset(stringstream &A, const vector<string> & Q);
    pair<int, int> find_smallest_subarray_sequentially_covering_subset(stringstream &A, const vector<string> & Q);


    struct hashPoint
    {
        int operator()(const PointA &p) const
        {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };

    static pair<int, int> get_canonical_fractional(int a, int b)
    {
        int gcs =1;// GCD(a, b);
        a /= gcs; b /= gcs;
        return b<0 ? pair<int, int>(-a, -b) : pair<int, int>(a, b);
    }

    struct Line
    {
        pair<int, int> slope;
        pair<int, int> intercept;

        Line(){}
        Line(PointA p0, PointA p1);

        bool operator==(const Line& that) const
        {
            return slope == that.slope && intercept == that.intercept;
        }
    };

    struct hashLine
    {
        int operator()(const Line&line) const
        {
//            hash<int> hashfunction;
            return hash<int>()(line.slope.first) ^ hash<int>()(line.slope.second)
                    ^ hash<int>()(line.intercept.first) ^ hash<int>()(line.intercept.second);
        }
    };

    Line find_line_with_most_points(const vector<PointA> &P);

    struct CompFunc
    {
        bool operator()(const pair<Line, unordered_set<PointA, hashPoint> > & a, const pair<Line, unordered_set<PointA, hashPoint> > & b) const
             {  return a.second.size() < b.second.size();}
    }compobj;


};

template<typename T, typename D>
class HashMap {
    vector<list<pair<T, D> > > A;
    int size, modulu;
    int hashcode(const T &key) {
        return hash<T>()(key)%modulu;
    }
    typename list<pair<T,D> >::iterator find(const T &key, list<pair<T,D> > & L) {
        auto it = L.begin();
        for (; it != L.end(); it++) {
            if ((*it).first == key)
                break;
        }
        return it;
    }
    void resize(){
        vector<list<pair<T, D> > > B(2*A.size());
        int size_b=0;
        modulu=B.size();
        for (auto &a : A) {
            for (auto it = a.begin(); it != a.end(); it++) {
                if (!insert(*it, B))
                    throw length_error("resize error");
                size_b++;
            }
        }
        A=B;
        size=size_b;
    }
    bool insert(const pair<T, D> & x, vector<list<pair<T, D> > > &B) {
        int code = hashcode(x.first);
        auto it = find(x.first, B[code]);
        if (it != B[code].end())
            return false;
        B[code].emplace_back(x);
        return true;
    }

public:
    HashMap(int _capacity) : A(_capacity), size(0), modulu(_capacity) {}
    bool insert(const pair<T, D> &x) {
        if (!insert(x, A))
            return false;
        size++;
        if (size/A.size()>2)
            resize();
        return true;
    }

    bool erase(const T &key) {
        int code = hashcode(key);
        auto it = find(key, A[code]);
        if (it == A[code].end())
            return false;
        A[code].erase(it);
        size--;
    }

    bool lookup(const T &key, D & value) {
        int code = hashcode(key);
        auto it = find(key, A[code]);
        if (it == A[code].end())
            return false;
        value = it->second;
        return true;
    }

    int getsize() {return size; }
};

#endif // HASHTABLES_H
