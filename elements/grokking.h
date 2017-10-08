#ifndef GROKKING_H
#define GROKKING_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace Grokking
{
    // Array
    vector<int> findMaxInSlidingWindow(vector<int> &A);
    int SearchRotateArray(const vector<int> &A);
    int FindMinCommonNumberInTwoSortedArr(const vector<int> &A, const vector<int> &B);
    void RotateArray(vector<int> &A);
    pair<int, int> FindLowHighIndexofKey(const vector<int> &A, int k);
    void moveZeroToLeft(vector<int> &A);
    void quickSort(vector<int> &A);
    void mergeOverLappingIntervals(vector<pair<int, int> > &A);
    // move all zero on the left, while other elements are stable:
    // solution: two pointers, starting from right (A.size()-1). When it is not zero, swap and move two pointer--, if it is zero, move one pointer.
    void zeroLeftStable(vector<int> &A);

    //List
    struct LNode{
        int data;
        shared_ptr<LNode> next, jump;
        LNode(int _data): data(_data), next(nullptr), jump(nullptr) {}
    };

    void reverseList(shared_ptr<LNode> &A);
    void removeDuplicate(shared_ptr<LNode> &A);
    void deleteNode(shared_ptr<LNode> &A, int key);
    void insertSort(shared_ptr<LNode> &A);
    shared_ptr<LNode> intersect(shared_ptr<LNode> &A, shared_ptr<LNode> &B);
    void SwapNthNodeWithHead(shared_ptr<LNode> &A, int n);
    void MergeSort(shared_ptr<LNode> &A);
    void reverseEvenNodes(shared_ptr<LNode> &A);
    void rotateList(shared_ptr<LNode> &A, int n);
    void reverseKElements(shared_ptr<LNode> &A, int k);
    void addTwoIntegers(shared_ptr<LNode> &A, shared_ptr<LNode>&B);
    shared_ptr<LNode> copyComplexList(shared_ptr<LNode> &A);

    //Math
    vector<int> findKthPermutation(vector<int> &A);
    int integerDivisionMultiplication(int x, int y);
    void pythagoreamTriplets(int limit);
    void printAllSumCombination(int sum);
    int findMissNumber(vector<int> &A);
    int findMissNumber_easy(vector<int> &A);
    int powerInt(int x, int n);
    float squareRoot(float x);

    //string
    vector<string> segmentation(string str);
    void XMLtoTree(string str);
    vector<string> palindromeSubStr(string str);
    bool regularExpress(string s, string e);

    //tree
    struct TNode {
        int data;
        shared_ptr<TNode> left, right, parent;
        TNode(int key, shared_ptr<TNode> &_left, shared_ptr<TNode> &_right): data(key), left(_left), right(_right) {}
    };

    bool twoIdentical(shared_ptr<TNode> &A, shared_ptr<TNode> &B);
    shared_ptr<TNode> minSpanningTree(shared_ptr<TNode> &A);
    void Inorder_iterative(shared_ptr<TNode> &A);
    shared_ptr<TNode> Inorder_successor(shared_ptr<TNode> &root, shared_ptr<TNode> &node);
    shared_ptr<TNode> Inorder_successor_parentPointers(shared_ptr<TNode> &node);
    void connectSibiling(shared_ptr<TNode> &A);
    //    1
    //   / \
    //  2   3
    //     /
    //    4
    //     \
    //      5
    //    The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}"
    shared_ptr<TNode> serialize_to_bst(vector<string> &A);
    vector<string> bst_deserialize(shared_ptr<TNode> &A);
    void deleteZeroSumSubTree(shared_ptr<TNode> &root);

    // graph
    struct GNode {
        int data;
        vector<shared_ptr<GNode> >edges;
        GNode(int _data) : data(_data) {}
    };
    shared_ptr<GNode> cloneGraph(shared_ptr<GNode> &root);
    void wordChaining(vector<string> &S);

    // back tracking
    void boggle_matrix_wordfinding(vector<vector<char> > &A);

}

#endif // GROKKING_H
