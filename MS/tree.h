#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <memory>
#include <list>
#include <vector>

using namespace std;

struct TreeNode{
    int value;
    int leftcount;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    vector<shared_ptr<TreeNode> > children;

    TreeNode(const int k): value(k), leftcount(0), left(nullptr), right(nullptr) {}
    TreeNode(): value(0), leftcount(0), left(nullptr), right(nullptr) {}
};

class Tree
{
public:
    Tree(const int start, const int end)
    {
        rootNode = buildTree(start, end);
    }
    Tree(){}

    void findSumPath_better(const shared_ptr<TreeNode> &node, const int sum, vector<int> &path);
    void printDFSChildren(shared_ptr<TreeNode> & node);
    shared_ptr<TreeNode> deserializeTree(string arr, int & index);
    bool checkBalanceTree2();
    void printTreeWithLevel();
    void printSpiralTree();
    void printTreeFrame();
    void printStreamBSTree(shared_ptr<TreeNode> & nodeptr);
    void buildBSTreeWithStream(shared_ptr<TreeNode> & nodeptr, int x);
    int getRankOfStreamBSTree(shared_ptr<TreeNode> & nodeptr, int x);
    shared_ptr<TreeNode> convertTreeToList2_main(shared_ptr<TreeNode> rootptr);
    shared_ptr<TreeNode> convertTreeToList2(shared_ptr<TreeNode> rootptr, bool isRight);

    bool getPathToNode(shared_ptr<TreeNode> &node, const int x, list<shared_ptr<TreeNode> > &path);
    shared_ptr<TreeNode> findCommonNode(list<shared_ptr<TreeNode> > & path1, list<shared_ptr<TreeNode> > & path2);
    void findSumPath(const shared_ptr<TreeNode> &node, const int sum, vector<int> &path);
    void findFirstCommonAncestor(shared_ptr<TreeNode> node, const int x, const int y);
    shared_ptr<TreeNode> findFirstCommonAncestor2(shared_ptr<TreeNode> node, const int x, const int y);

    void findFirstCommonNodeWithAdditionalSpace(const int x, const int y);
    vector<list<shared_ptr<TreeNode> > > getLevelLists();
    void printLevelLists(vector<list<shared_ptr<TreeNode> > > levelLists);
    Tree(int * numArray, const size_t length);
    void printTree(){printTree(rootNode); cout << endl;}
    shared_ptr<TreeNode> getRootNode(){ return rootNode; }
    shared_ptr<TreeNode> convertTreeToList(shared_ptr<TreeNode> &root, bool asRight);
    void convertTreeToList_inorder(shared_ptr<TreeNode> &treeptr, shared_ptr<TreeNode> &listptr);
    shared_ptr<TreeNode> convertTreeToList_inorder_main(shared_ptr<TreeNode> & rootptr);
//    list<shared_ptr<TreeNode> > convertTreeToList()
//    {
//        list<shared_ptr<TreeNode> > nodeList;
//        convertTreeToList(nodeList, rootNode, false);
//        return nodeList;
//    }
    bool findSubTree(shared_ptr<TreeNode> &t1, shared_ptr<TreeNode> &t2);
    void printList();
    void BDS();
    void inorder(){ inorder(rootNode); cout << endl;}
    void preorder(){ preorder(rootNode); cout << endl;}
    void postorder(){ postorder(rootNode); cout << endl;}
    void findPath(shared_ptr<TreeNode> curNode, const int targetNum, list<int> & path, int & curSum);
    static bool verifySequenceOfBST(int * seq, int length);
    void mirrorBST_recursive(shared_ptr<TreeNode> node);
    void mirrorBST_iterative(shared_ptr<TreeNode> node);
    int getTreeDepth(shared_ptr<TreeNode> node);
    int getTreeDepth_2(shared_ptr<TreeNode> node);
    bool isBST(shared_ptr<TreeNode> & node, int minV, int maxV);
    bool isBST_main(shared_ptr<TreeNode> & node);
    bool isBalancedBST(shared_ptr<TreeNode> &node, int &depth);


private:
    shared_ptr<TreeNode> rootNode;
    shared_ptr<TreeNode> buildTree(const int start, const int end);
    void printTree(shared_ptr<TreeNode> & curNode);
//    void printList(shared_ptr<TreeNode> & curNode);
    void inorder(shared_ptr<TreeNode> & curNode);
    void preorder(shared_ptr<TreeNode> & curNode);
    void postorder(shared_ptr<TreeNode> & curNode);
    shared_ptr<TreeNode> convertArrayToTree(int * numArray, int start, int end);
    bool findNode(shared_ptr<TreeNode> &node, const int x);
    bool matchTree(shared_ptr<TreeNode> &t1, shared_ptr<TreeNode> &t2);


};


#endif // TREE_H
