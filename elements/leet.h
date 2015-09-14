#ifndef LEET_H
#define LEET_H

#include <memory>
#include <unordered_set>
#include <string>
#include <vector>
#include "utilities.hpp"
#include <list>
#include <unordered_map>
#include "misc.h"

using namespace std;

class Leet
{
public:
    Leet();

    struct LNode {
        int data;
        shared_ptr<LNode> next;
        LNode(int x) : data(x), next(nullptr) {}
        LNode() {}

    };

    struct TNode {
        int data;
        shared_ptr<TNode> left, right, next, parent;
        TNode(int x): data(x), left(nullptr), right(nullptr), next(nullptr) {}
        TNode(int x, shared_ptr<TNode> _left, shared_ptr<TNode> _right): data(x), left(_left), right(_right) {}

    };

    int lengthLastWord(string S);

    vector<Misc::Interval> insertInterval(const vector<Misc::Interval> &A, Misc::Interval a);
    vector<Misc::Interval> mergeIntervals(vector<Misc::Interval> &A);
    string minimumWindowSubstring(string S, string T);
    string minimumWindowSubstring_sequential(string S, string T);
    void postorder_bt_iterative(shared_ptr<TNode> &n );
    void preorder_bt_iterative(shared_ptr<TNode> &n );
    int maxProductSubarray(const vector<int> A);
    struct GNode {
        int data;
        unordered_set<shared_ptr<GNode> > neighbors;
        GNode(int _data) : data(_data) {}
    };

    shared_ptr<GNode> copyGraph(const shared_ptr<GNode> root);
    shared_ptr<GNode> copyGraph_recursive(const shared_ptr<GNode> root);

    bool isPalindromeInt(int x);
    bool isPalindromeInt_2(int x);
    bool isPalindromeInt_recursive(int x);

    string findLargestPalindromicSubstr(string s);
    string findLargestPalindromicSubstr_nlogn(string s); //nlogn
    int findLargestPalindromicSubstr_DP(string s); //n^2

    // see the regexMatch at arraystring.h
    //‘.’ Matches any single character.
    //‘*’ Matches zero or more of the preceding element.
    bool regexMatch(string p, string s);

    /**
     * @brief wildcardMatching: support "?" any char, and "*" any sequence
     * @param x
     * @param y: pattern string
     * @return
     */
    bool wildcardMatching(string x, string y);

    //Given an array A of integers, find the maximum of j-i subjected to the constraint of A[i] < A[j].
    int distanceMaximum(const vector<int> &A);
    int distanceMaximum_nlogn(const vector<int> &A);
    pair<int, int> distanceMaximum_better(const vector<int> &A);

    /**
     * @brief paintersPartition
     * M[n,k]=min(0<i<A.size())(max(P(i-1,k-1), sum(A(i->A.size()-1))
     * @param A
     * @param k
     * @return
     */
    int paintersPartition(const vector<int> &A, int k);
    // binary search
    int paintersPartition_efficient(const vector<int> & A, int k);

    vector<int> maxSlidingWindow(const vector<int> &A, int w);

    void insertNodeCyclicList(shared_ptr<LNode> & node, int x);
    void insertNodeCyclicList_2(shared_ptr<LNode> & node, int x);
    void printNodeCyclicList(shared_ptr<LNode> n);

    int reverseBit(unsigned x);
    int reverseBit_logn(unsigned x);
//    void reverseBit(unsigned long long &x);

    string longestNonRepeatSubstr(string s);
    string longestNonRepeatSubstr2(string s);

    // assumption x and y exist in the tree
    shared_ptr<TNode> lowestCommonAncestor_BT(shared_ptr<TNode> & root, shared_ptr<TNode> &x, shared_ptr<TNode> &y);
    shared_ptr<TNode> lowestCommonAncestor_BT_parentPointer(shared_ptr<TNode> &x, shared_ptr<TNode> &y);
    // Binary Search Tree
    shared_ptr<TNode> lowestCommonAncestor_BST(shared_ptr<TNode> & root, shared_ptr<TNode> &x, shared_ptr<TNode> &y);

    shared_ptr<TNode> buildTreeFromInorderPreorder(int in[], int pre[], int size);
    shared_ptr<TNode> buildTreeFromInorderPostorder(const vector<int> &in, const vector<int> &post);

    struct RectangleLeet {
        PointA start;
        int width, height;
        RectangleLeet(PointA s, int w, int h) : start(s), width(w), height(h) {}
    };

    bool CheckRectangleOverlap(RectangleLeet &x, RectangleLeet &y);

    int findKsmallestUnion_log(int A[], int m, int B[], int n, int k);
    int findKsmallestUnion_log2(vector<int> &A, vector<int> &B, int k);

    // find the kth smallest in sum of two sorted arrays, which turn to be the same problem below
    // time complexity is klogk by using priority queue
    int findKsmallestSumUnion(vector<int> &A, vector<int> &B, int k);
    // find the kth smallest in the sorted 2D array which the row elements, and column elements are sorted.
    // time complexity is (m+n)
    int kthSmallestinSorted2D(vector<vector<int> > &A, int k);

    int evalReversePolishNotation(const vector<string> &A);

    int maxPointsInLine(const vector<PointA> &A);
    int maxPointsInLine_efficient(const vector<PointA> &A);

    struct lnode {
        int data;
        lnode * next;
    };

    void sortList_nlogn(lnode **head);
    void sortList(shared_ptr<LNode> &head);

    /**
     * @brief candyproblem: There are N children standing in a line. Each child is assigned a rating value.
     *You are giving candies to these children subjected to the following requirements:
     *Each child must have at least one candy.
     *Children with a higher rating get more candies than their neighbors. What is the minimum candies you must give?
     * @param A
     * @return
     */
    int candyproblem(const vector<int> &A);

    class LRUCache {
        int capacity;
        unordered_map<int, pair<list<int>::iterator, int> > table;
        list<int> seq;
        void moveFront(int key);
    public:
        LRUCache(int _capacity) : capacity(_capacity) {}
        int get(int key);
        void set(int key, int value);
        void printSeq() {
            for (auto &x : seq)
                cout << x << " ";
            cout << endl;
        }
    };

    vector<string> grayCode(int n);

    int triangle(vector<vector<int> > &A);
    void pascalTriangle(int n);

    shared_ptr<TNode> arrToTree(const vector<int> &A, int left, int right);
    shared_ptr<TNode> deserializeToTree(const vector<string> &A);
    // for complete tree structure
    shared_ptr<TNode> deserializeToTree_recursive(const vector<string> &A);
    vector<int> treeToArr(shared_ptr<TNode> & root);
    void recoverBST(shared_ptr<TNode> &root);
    void recoverBST_constSpace(shared_ptr<TNode> &root);
    void recoverBST_efficient(shared_ptr<TNode> &root);

    bool interleavingString(string s1, string s2, string s3);

    // color 0,1,2
    void sortColor_onepass_constSpace(vector<int> &A, int pivot);

    double medianSortedArrayUnion(vector<int> &A, vector<int> &B);
    int getKth(vector<int> &A, int aleft, int aright, vector<int> &B, int bleft, int bright, int k);
    string zigzagConvert(string & s, int nrow);
    vector<vector<char> > zigzagConrversion2(string s, int nrow);

    int findLargestContainer(vector<int> &heights);
    int findLargestContainer_N(vector<int> &heights);
    string commonPrefix(vector<string> & S);

//    unordered_set<pair<int, int>, PairHashCode, PairEqual >  twoSum(vector<int> &A, int left, int right, int k);
    void threeSum(vector<int> &A);
    void phoneNumberRepresentation(int digit, string &res);
    shared_ptr<LNode> reverseList_kgroup(shared_ptr<LNode> & head, int k);
    shared_ptr<LNode> buildList(vector<int> &A);
    void printList(shared_ptr<LNode> head);
    shared_ptr<LNode> reverseList_recursive(shared_ptr<LNode> & head);
    shared_ptr<LNode> reverseList_iterative(shared_ptr<LNode> & head);

    int strStr(string stack, string needle);
    vector<int> substringWithAllWords(string s, vector<string> &dict);
    // this implmentation has misunderstanding of problem
    vector<int> substringWithAllWords_efficient(string s, vector<string> &dict);

    pair<int, int> minCoverage_stream(vector<string> &s, vector<string> &dict);
    string longestValidParentheses(string s);
    int longestValidParentheses2(string s);
    int longestValidParentheses3_better(string s);

    void permuteArr(vector<int> &perm, vector<int> & A);
    void nextPermutation(vector<int> &A);

    pair<int, int> findRangeofValue(const vector<int> & A, int k);

    bool validateSudoku(vector<vector<int> > &A);
    bool solveSudoku(vector<vector<int> > &A);

    /**
     * @brief reorderList
     *Given a singly linked list L: L0→L1→…→Ln-1→Ln,
            reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
            You must do this in-place without altering the nodes' values.
     * @param head
     */
    void reorderList(shared_ptr<LNode> & head);

    vector<string> wordBreak(string s, unordered_set<string> &A);
    bool wordBreak_efficient(string s, unordered_set<string> &A);
    void wordBreak_efficient_print(const string s, const unordered_set<string> &D);


    int appearOnce_otherAppearThreeTimes(vector<int> & A);
    int appearOnce_otherAppearThreeTimes_noextraspace(vector<int> & A);
    int appearOnce_otherAppearThreeTimes_mostefficient(const vector<int> &A);

    int gasStation(vector<int> &gas, vector<int> &dist);

    int palindromePartition(string s);
    vector<vector<string> > palindromePartition_allset(string s);
    void surroundedRegion(vector<vector<char> > &A);
    void surroundedRegion_efficient(vector<vector<char> > &A);

    int sumTreeRootToLeaf(shared_ptr<TNode> root);

    int longestConsecutiveSequence(vector<int> &A);

    vector<vector<string> > wordLadder2(string s, string e, unordered_set<string> &D);
    bool validPalindrome(string s);

    int maxProfit_onebuysell(vector<int> &A);
    int maxProfit_twobuysell(vector<int> &A);
    int maxProfit_kbuysell(vector<int> &A, int k); // the result is wrong
    int maxProfit_unlimit(vector<int> &A);

    int numDistinctSubsequence(string s, string t);

    /**
     * @brief Leet::connectLNodeRightNeighbor
     *         1 -> NULL
           /  \
          2 -> 3 -> NULL
         / \  / \
        4->5->6->7 -> NULL
     * @param root
     */
    void connectLNodeRightNeighbor_completeTree(shared_ptr<TNode> & root);
    /**
     * @brief connectLNodeRightNeighbor
     *1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
     * @param root
     */
    void connectLNodeRightNeighbor_anyTree(shared_ptr<TNode> & root);
    void printLNodeRightNeighbor(shared_ptr<Leet::TNode> &root);
    void populateNextRightPointers(shared_ptr<Leet::TNode> &root);
    shared_ptr<TNode> buildTree_LNodeRightNeighbor(const vector<int> &A);
    shared_ptr<TNode> buildTree_LNodeRightNeighbor2(const vector<int> &A);

    void flattenBinaryTree(shared_ptr<TNode> &root);
    vector<vector<int> > pathSum2(shared_ptr<TNode> root, int k);
    int minimumDepthBT(shared_ptr<TNode> root);

    shared_ptr<TNode> convertSortedListToBST(shared_ptr<LNode> &head);
    shared_ptr<TNode> convertSortedArrayToBST(vector<int> &A);
    shared_ptr<TNode> convertPreorderArrayToBST(vector<int> &A);
    shared_ptr<TNode> convertPreorderListToBST(shared_ptr<LNode> &head);

    /**
     * @brief buildTreeFromSerializedArray
     *OJ's Binary Tree Serialization:
        The serialization of a binary tree follows a level order traversal, where '#' signifies a path terminator where no node exists below.
        Here's an example:
           1
          / \
         2   3
            /
           4
            \
             5
    The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}"
     * @param A
     * @return
     */
    shared_ptr<TNode> buildTreeFromSerializedArray(vector<string> &A);
    vector<vector<int> > BSTLeverOrderTraversal_reverse(shared_ptr<TNode> &root);

    int uniqueBST(int n);
    vector<shared_ptr<TNode> > uniqueBST2(int n);

    vector<string> restoreIPAddress(string s);

    void reverseList2(shared_ptr<LNode> &head, int m, int n);
    vector<vector<int> > subset2(vector<int> & A);
    vector<vector<int> > subset2_better(vector<int> & A);
    vector<vector<int> > subset3(vector<int> &A);
    vector<vector<int> > subset3_duplicates(vector<int> A);

    int decodeWays(string s);

    /**
     * @brief scrambleStrings
     *    rgtae
       /    \
      rg    tae
     / \    /  \
    r   g  ta  e
           / \
          t   a
     * @param s0
     * @param s1
     * @return
     */

    bool isScrambleStrings(string s0, string s1);
    int maxRectangle(const vector<vector<bool> > &A);

    int largestRectangleHistogram(const vector<int> &A);
    void removeDuplicates(shared_ptr<LNode> &head);
    void removeDuplicates2(shared_ptr<LNode> &head);
    void removeElem(vector<int> &A, int elem);
    void removeDuplicatesArray(vector<int> &A);
    void reverseNodesKGroup(shared_ptr<LNode> &head, int k);
    void swapNodesInPairs(shared_ptr<LNode> &head);
    bool wordSearch(vector<vector<char> > &A, string word);

    shared_ptr<LNode> mergeKList(const vector<shared_ptr<LNode> > &A);
    vector<string> generateParentheses(int n);

    void plusOne(shared_ptr<LNode> &head);
    vector<vector<int> > combinations(int n, int k);
    vector<vector<int> > combinationSum(vector<int> &A, int k);
    vector<vector<int> > combinationSum2(vector<int> &A, int k);

    vector<vector<int> > permutations(vector<int> &A);
    vector<vector<int> > permutations_k(vector<int> &A, int k);

    // it fail at 2 3 1 2
    int trapRainWater(const vector<int> &A);
    int trapRainWater2(const vector<int> &A);

    int firstMissingPositive(vector<int> &A);

    double powInt(double x, int n);

    string callNumber(int n);

    /**
     * @brief searchSorted2D
     *  [1,   3,  5,  7],
        [10, 11, 16, 20],
        [23, 30, 34, 50]
     * @param A
     * @return
     * O(log(m*n)=logm+logn);
     */
    pair<int, int> searchSorted2D(const vector<vector<int> > &A, int k);
    /**
     * @brief searchSorted2D_2
     *  [1,  3,  5,   7],
        [2,  4,  6,   8],
        [3,  5,  7,   9]
     * @param A
     * @return
     * O(n)
     */
    pair<int, int> searchSorted2D_2(const vector<vector<int> > &A, int k);

    vector<string> textJustify(vector<string> &A, int k);
    int textMessiness(const vector<string> &A, int k);

    string addBinaryStrings(string x, string y);
    bool jumpGame(const vector<int> &A);
    int jumpGame2(const vector<int> &A);

    vector<vector<string> > NQueens(int n);
    string multiplyStrings(string x, string y);
    string multiplyStrings_efficient(string x, string y);
    string multiplyStrings_moreefficient(string x, string y);

    int divideInts(int x, int y);

    // o(nlogn+n)
    vector<vector<int> > sum2(vector<int> &A, int k);
    // o(nlogn+n^2)
    vector<vector<int> > sum3(vector<int> &A, int k);
    // o(nlogn+n^3)
    vector<vector<int> > sum4(vector<int> &A, int k);
    // not complete because of coding complexity. But the time complexity should be n^2logn is better than
    // previous one which is n^3
    vector<vector<int> > sum4_efficient(vector<int> &A, int k);
    int sum2_closest(vector<int> &A, int k);
    int sum3_closest(vector<int> &A, int k);

    int reverseInt_noSpace(int x);

    string convertIntToRoman(int x);
    int convertRomanToInt(string str);

    shared_ptr<LNode> findBeginCyclicList(shared_ptr<LNode> &root);

    int editDist(string x, string y);
    int editDist_efficientSpace(string x, string y);

};

#endif // LEET_H
