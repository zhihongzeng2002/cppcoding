#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename T>
void printVector(const vector<T> &A) {
    copy(A.begin(), A.end(), ostream_iterator<T>(cout, " "));
    cout << endl;
}

struct LineSegment {
    int left,right,color, height;
    LineSegment(int l, int r, int c, int h): left(l), right(r), color(c), height(h) {}
};

struct EndPoint2 {
    bool isLeft;
    LineSegment *L;
    int val() {
        return isLeft ? L->left : L->right;
    }
    bool operator<(const EndPoint2 & that ) const {
        return (isLeft ? L->left : L->right) < (that.isLeft ? that.L->left : that.L->right);
    }
};

template<typename T>
struct TreeNode {
    T data;
    unique_ptr<TreeNode<T> > left, right;
    vector<pair<unique_ptr<TreeNode>, double> > edges;
    TreeNode(T &_data, unique_ptr<TreeNode<T> > _l, unique_ptr<TreeNode<T> > _r)
        :data(_data), left(move(_l)), right(move(_r)) {}

    int lowPower() {
        int lowenergy=10, highenergy=2*lowenergy;
        return lowenergy+left.highPower()+right.highPower;
    }
    int highPower() {
        int lowenergy=10, highenergy=2*lowenergy;
        return highenergy+min(left.highPower()+right.highPower, left.lowPower()+right.lowPower);
    }
    int minPower() {
        return min(lowPower(), highPower());
    }
};

template<typename T>
struct BSTNode
{
    T data;
    int size;
    shared_ptr<BSTNode<T> > left, right, parent;
    int order;
    BSTNode(const T _data, shared_ptr<BSTNode<T> > & _left, shared_ptr<BSTNode<T> > & _right)
        : data(_data), left(_left), right(_right), order(-1){}

    void print()
    {
        print(left);
        cout << data << " ";
        print(right);
        cout << endl;
    }

    void print(shared_ptr<BSTNode> &node)
    {
        if (!node) return;

        print(node->left);
        cout << node->data << " ";
        print(node->right);

    }
};

//struct LineSegment
//{
//    int left, right, color, height;
//    LineSegment(int l, int r, int c, int h): left(l), right(r), color(c), height(h) {}
//    bool operator<(const LineSegment & that) const
//    {
//        return left != that.left ? left<that.left : height > that.height;
//    }
//};

struct PointA
{
    int x,y;
    PointA(int _x, int _y): x(_x), y(_y) {}
    PointA(){}
    bool operator==(const PointA & that) const
    {
        return x==that.x && y==that.y;
    }

};

static int _gcd(int x, int y) {
    if (!x || !y) return x==0 ? y: x ;
    if (x==1 || y==1) return 1;
    if (!x&1 && !y&1)
        return _gcd(x>>1, y>>1) <<1;
    else if (!x&1)
        return _gcd(x>>1, y);
    else if (!y&1)
        return _gcd(x, y>>1);
    else
        return _gcd(max(x,y)-min(x,y), min(x,y));
}

//pair<int, int> _gcdPair(int x, int y) {
//    int GCD = _gcd(x, y);
//    return pair<int, int>(x/GCD, y/GCD);
//}

//struct Line {
//    PointA p1, p2;
//    pair<int, int> slope, intercept;

//    Line(PointA _x, PointA _y) : p1(_x), p2(_y) {
//        if (p1.x==p2.x) {
//            slope = pair<int, int>(p2.y-p1.y, 0);
//            intercept = pair<int,int>(p1.y-p2.y, 0);
//        } else {
//            slope = _gcdPair(p2.y-p1.y, p2.x-p1.x);
//            intercept = _gcdPair(p2.x*p1.y-p1.x*p2.y, p2.x-p1.x);
//        }
//    }
//};


#endif // UTILITIES_HPP
