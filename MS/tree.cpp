#include "tree.h"
#include <queue>
#include <stack>
#include <limits.h>

void Tree::printDFSChildren(shared_ptr<TreeNode> &node)
{
    if (!node) return;

    cout << char(node->value) << " ";
    cout << endl;
    for (int i=0; i<node->children.size(); i++)
    {
        printDFSChildren(node->children[i]);
    }
    cout << endl;
}

/**
 * @brief Tree::deserializeTree
 *Given below is a tree/trie
A
| \ \
B c D
|    \
e	 F
a<b<e<>>c<>d<f<>>>
above string represents the following trie/tree (visualize) and assume that
there exisits a serialize method that performs above.
Now, write a deserialize method so that above string to an object model of the following
TreeNode
TreeNode[] children

 * @param arr
 * @param index
 */
shared_ptr<TreeNode> Tree::deserializeTree(string arr, int &index)
{
    if (arr.empty() || index==arr.size() ) return nullptr;

    char ch=arr[index];
    cout << ch << " ";
    index++;
    if (ch=='<')
        return deserializeTree(arr, index);
    else if (ch=='>')
        return nullptr;
    else
    {
        shared_ptr<TreeNode> node(new TreeNode(int(ch)));
        while (true)
        {
            shared_ptr<TreeNode> child=deserializeTree(arr, index);
            if (child) node->children.push_back(child);
            else break;
        }
        return node;
    }
}

static void printLeftNode(shared_ptr<TreeNode> & node)
{
    if (!node || (!node->left && !node->right)) return;

    cout << node->value << " ";
    printLeftNode(node->left);
}

static void printRightNode(shared_ptr<TreeNode> &node)
{
    if (!node || (!node->left && !node->right)) return;
    printRightNode(node->right);
    cout << node->value << " ";
}

static void printLeaveNode(shared_ptr<TreeNode> & node)
{
    if (!node) return;
    if (!node->left && !node->right)
    {
        cout << node->value << " ";
        return;
    }

    printLeaveNode(node->left);
    printLeaveNode(node->right);
}

void Tree::printTreeFrame()
{
    if (!rootNode) return;
    //
    cout << rootNode->value << endl;
    if (rootNode->left) printLeftNode(rootNode->left);
    cout << endl;
    printLeaveNode(rootNode);
    cout << endl;
    if (rootNode->right) printRightNode(rootNode->right);
    cout << endl;
}

void Tree::printSpiralTree()
{
    if (!rootNode) return;

    stack<shared_ptr<TreeNode> > s0;
    stack<shared_ptr<TreeNode> > s1;
    s0.push(rootNode);

    while (!s0.empty())
    {
        stack<shared_ptr<TreeNode> > temp=s1;
        s1=s0;
        s0=temp;
        while (!s1.empty())
        {
            shared_ptr<TreeNode> node=s1.top();
            s1.pop();
            cout << node->value << " ";
            if (node->left) s0.push(node->left);
            if (node->right) s0.push(node->right);
        }
        cout << endl;
    }
}

void Tree::printTreeWithLevel()
{
    if (!rootNode) return;

    vector<shared_ptr<TreeNode> > currentQ;
    currentQ.push_back(rootNode);

    while (!currentQ.empty())
    {
        vector<shared_ptr<TreeNode> > preQ=currentQ;
        currentQ.clear();
        for (int i=0; i<preQ.size(); i++)
        {
            shared_ptr<TreeNode> node=preQ[i];
            cout << node->value << " ";
            if (node->left) currentQ.push_back(node->left);
            if (node->right) currentQ.push_back(node->right);
        }
        cout << endl;
    }

}

static int checkBalanceTree_core(shared_ptr<TreeNode> &node)
{
    if (!node) return 0;

    int leftHeight=checkBalanceTree_core(node->left);
    int rightHeight=checkBalanceTree_core(node->right);

//    cout << leftHeight << " " << rightHeight << endl;

    if (leftHeight==-1 || rightHeight==-1) return -1;
    else if (abs(leftHeight-rightHeight)>1) return -1;
    else
        return max(leftHeight, rightHeight)+1;

}

bool Tree::checkBalanceTree2()
{
    if (!rootNode) return true;

    int height=checkBalanceTree_core(rootNode);
    if (height==-1) return false;
    else
        return true;
}

void Tree::printStreamBSTree(shared_ptr<TreeNode> &nodeptr)
{
    if (!nodeptr) return;
    printStreamBSTree(nodeptr->left);
    cout << nodeptr->value << ":" << nodeptr->leftcount << endl;
    printStreamBSTree(nodeptr->right);

}

void Tree::buildBSTreeWithStream(shared_ptr<TreeNode> &nodeptr, int x)
{
    if (!nodeptr)
    {
        nodeptr = shared_ptr<TreeNode>(new TreeNode(x));
        return;
    }

    if (x<=nodeptr->value)
    {
        if (!nodeptr->left) nodeptr->left=shared_ptr<TreeNode>(new TreeNode(x));
        else
            buildBSTreeWithStream(nodeptr->left, x);
        nodeptr->leftcount++;
    }
    else
    {
        if (!nodeptr->right) nodeptr->right=shared_ptr<TreeNode>(new TreeNode(x));
        else
            buildBSTreeWithStream(nodeptr->right, x);
    }
}

int Tree::getRankOfStreamBSTree(shared_ptr<TreeNode> &nodeptr, int x)
{
    if (!nodeptr) return -1;
    if (x==nodeptr->value) return nodeptr->leftcount;
    if (x<nodeptr->value)
    {
        return getRankOfStreamBSTree(nodeptr->left, x);
    }
    else
    {
        int rank=getRankOfStreamBSTree(nodeptr->right, x);
        if (rank==-1) return -1;
        return nodeptr->leftcount+1+rank;
    }
}

shared_ptr<TreeNode> Tree::convertTreeToList2_main(shared_ptr<TreeNode> rootptr)
{
    return convertTreeToList2(rootptr, true);
}

shared_ptr<TreeNode> Tree::convertTreeToList2(shared_ptr<TreeNode> rootptr, bool isRight)
{
    if (!rootptr) return shared_ptr<TreeNode>();

    shared_ptr<TreeNode> leftEnd, rightStart;
    if (rootptr->left)
    {
        leftEnd=convertTreeToList2(rootptr->left, false);
        leftEnd->right=rootptr;
        rootptr->left=leftEnd;
    }

    if (rootptr->right)
    {
        rightStart=convertTreeToList2(rootptr->right, true);
        rootptr->right=rightStart;
        rightStart->left=rootptr;
    }

    shared_ptr<TreeNode> currentNode=rootptr;
    if (isRight)
    {
        while(currentNode->left)
            currentNode=currentNode->left;
        return currentNode;
    }
    else
    {
        while (currentNode->right)
            currentNode=currentNode->right;
        return currentNode;
    }

}

void Tree::findSumPath(const shared_ptr<TreeNode> &node, const int sum, vector<int> &path)
{
    if (!node ) return;
    path.push_back(node->value);
    int tmp=sum;
    int count=0;
    for (int i=path.size()-1; i>=0; i--, count++)
    {
        tmp -= path.at(i);
        if (!tmp)
        {
            for (size_t j=path.size()-1-count; j<path.size(); j++)
            {
                cout << path.at(j) << '-';
            }
            cout << endl;
        }
    }
    vector<int> c1(path), c2(path);
    if (node->left) findSumPath(node->left, sum, c1);
    if (node->right) findSumPath(node->right, sum, c2);
}

void Tree::findSumPath_better(const shared_ptr<TreeNode> &node, const int sum, vector<int> &path)
{
    if (!node ) return;
    path.push_back(node->value);

    int x=sum-node->value;
    if (x==0)
    {
        for (int i=0; i<path.size(); i++)
            cout << path[i] << endl;
    }
    else
    {
        findSumPath_better(node->left, x, path);
        findSumPath_better(node->right, x, path);
    }
    path.pop_back();
}

bool Tree::findSubTree(shared_ptr<TreeNode> &t1, shared_ptr<TreeNode> &t2)
{
    if (!t2) return true;
    if (!t1) return false;

    if (t1->value != t2->value)
        if (matchTree(t1, t2)) return true;

    return findSubTree(t1->left, t2) && findSubTree(t1->right, t2);
}

bool Tree::matchTree(shared_ptr<TreeNode> &t1, shared_ptr<TreeNode> &t2)
{
    if (!t2) return true;
    if (!t1) return false;
    if (t1->value != t2->value) return false;
    return matchTree(t1->left, t2->left) && matchTree(t1->right, t2->right);

}

bool Tree::getPathToNode(shared_ptr<TreeNode> &node, const int x, list<shared_ptr<TreeNode> > &path)
{
    if (!node) return false;
    path.push_back(node);

    if (node->value == x) return true;

    // go to next level
    bool findFlag=getPathToNode(node->left, x, path) || getPathToNode(node->right, x, path);

    if (!findFlag)
    path.pop_back();

    return findFlag;
}

shared_ptr<TreeNode> Tree::findCommonNode(list<shared_ptr<TreeNode> > & path1, list<shared_ptr<TreeNode> > & path2)
{
    list<shared_ptr<TreeNode> >::iterator itr1=path1.begin(), itr2=path2.begin();
    shared_ptr<TreeNode> commonNode=nullptr;
    while (itr1 != path1.end() && itr2 != path2.end())
    {
        if ((*itr1)->value == (*itr2)->value)
            commonNode = *itr1;
        else
            break;

        itr1++;
        itr2++;

    }
    return commonNode;

}

void Tree::findFirstCommonNodeWithAdditionalSpace(const int x, const int y)
{
    list<shared_ptr<TreeNode> > pathx, pathy;
    getPathToNode(rootNode, x, pathx);
    getPathToNode(rootNode, y, pathy);
    shared_ptr<TreeNode> commonNode = findCommonNode(pathx, pathy);
    if (commonNode) cout << "The value of the common node = " << commonNode->value << endl;
    else cout << "No common node" << endl;

}

bool Tree::findNode(shared_ptr<TreeNode> &node, const int x)
{
    if (!node) return false;
    if (node->value == x) return true;
    return findNode(node->left, x) || findNode(node->right, x);

}

void Tree::findFirstCommonAncestor(shared_ptr<TreeNode> node, const int x, const int y)
{
    if (!node) return;
    if (findNode(node->left, x) && findNode(node->left, y)) return findFirstCommonAncestor(node->left, x, y);
    else if (findNode(node->right, x) && findNode(node->right, y)) return findFirstCommonAncestor(node->right, x, y);
    else
    {
        cout << "FCA=" << node->value;
    }
}

static bool findTreeNode(shared_ptr<TreeNode> &node, int x)
{
    if (!node) return false;
    if (node->value==x) return true;

    return findTreeNode(node->left, x) || findTreeNode(node->right, x);
}

shared_ptr<TreeNode> Tree::findFirstCommonAncestor2(shared_ptr<TreeNode> node, const int x, const int y)
{
    if (!node) return nullptr;

    if (node->value == x && node->value==y) return node;
    else if (node->value==x || node->value==y)
        return node;

    bool findx=findTreeNode(node->left, x);
    bool findy=findTreeNode(node->left, y);

    cout << node->value << ":" << findx << "," << findy << endl;

    if (findx != findy) return node;

    shared_ptr<TreeNode> childNode = findx ? node->left: node->right;
    return findFirstCommonAncestor2(childNode, x, y);
}

vector<list<shared_ptr<TreeNode> > > Tree::getLevelLists(){
    vector<list<shared_ptr<TreeNode> > > result;
    if (!rootNode) return result;

    list<shared_ptr<TreeNode> > myList;
    myList.push_back(rootNode);
    result.push_back(myList);
    int level=0;
    while(true)
    {
        list<shared_ptr<TreeNode> > levelList;
        list<shared_ptr<TreeNode> > prelevelList=result.at(level);
        for (list<shared_ptr<TreeNode> >::iterator itr=prelevelList.begin(); itr != prelevelList.end(); itr++)
        {
            shared_ptr<TreeNode> node = *itr;
            if (node->left) levelList.push_back(node->left);
            if (node->right) levelList.push_back(node->right);
        }
        if (!levelList.empty()) result.push_back(levelList);
        else
            break;
        level++;
    }

    return result;
}

void Tree::printLevelLists(vector<list<shared_ptr<TreeNode> > > levelLists)
{
    if (levelLists.empty()) return;
    for (size_t i=0; i< levelLists.size(); i++)
    {
        cout << "Level " << i << ":";
        list<shared_ptr<TreeNode> > levelList = levelLists.at(i);
        for (list<shared_ptr<TreeNode> >::iterator itr=levelList.begin(); itr != levelList.end(); itr++)
        {
            cout << (*itr)->value << ' ';
        }
        cout << endl;

    }

}

int Tree::getTreeDepth(shared_ptr<TreeNode> node)
{
    if (!node) return 0;

    return max(getTreeDepth(node->left), getTreeDepth(node->right))+1;
//    if (node->left && node->right) return
//    else if (!node->left && !node->right) return 1;
//    else if (!node->left) return getTreeDepth(node->right)+1;
//    else return getTreeDepth(node->left)+1;
}

int Tree::getTreeDepth_2(shared_ptr<TreeNode> node)
{
    if (!node) return 0;

    int leftDep=getTreeDepth(node->left);
    int rightDep=getTreeDepth(node->right);

    return leftDep>rightDep ? leftDep+1 : rightDep+1;
}

void Tree::mirrorBST_iterative(shared_ptr<TreeNode> node)
{
    if (!node) return;
    queue<shared_ptr<TreeNode> > myQueue;
    myQueue.push(node);

    while (myQueue.size())
    {
        shared_ptr<TreeNode> cur = myQueue.front();
        myQueue.pop();

        shared_ptr<TreeNode> temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;

        if (cur->left) myQueue.push(cur->left);
        if (cur->right) myQueue.push(cur->right);
    }
}

void Tree::mirrorBST_recursive(shared_ptr<TreeNode> node)
{
    if (!node) return;
    shared_ptr<TreeNode> temp = node->left;
    node->left = node->right;
    node->right = temp;

    if (node->left) mirrorBST_recursive(node->left);
    if (node->right) mirrorBST_recursive(node->right);
}

/** verify whether a sequence is post-order traversal of binary search tree
 * @param seq seqence of number
 * @param length the length of seqeunce
 * return true if the sequence is traversal result of BST, otherwise false;
 */
bool Tree::verifySequenceOfBST(int *seq, int length)
{
    if (!seq || length<=0) return false;

    int node=seq[length-1];
    int i;
    for (i=0; i<length-1; i++)
    {
        if (seq[i]>node) break;
    }

    for (int j=i; j<length-1; j++)
    {
        if (seq[j]<node) return false;
    }

    bool flag=true;
    if (i>0) flag=verifySequenceOfBST(seq, i);

    if (flag && i<length-1) flag=verifySequenceOfBST(seq+i, length-i-1);

    return flag;


}

void Tree::BDS()
{
    if (!rootNode) return;
    queue<shared_ptr<TreeNode> > myQueue;
    myQueue.push(rootNode);

    while (myQueue.size())
    {
        shared_ptr<TreeNode> curNode = myQueue.front();
        myQueue.pop();
        cout << curNode->value << " ";
        if (curNode->left) myQueue.push(curNode->left);
        if (curNode->right) myQueue.push(curNode->right);
    }
    cout << endl;
}

Tree::Tree(int * numArray, const size_t length)
{
    if (!numArray) return;
    rootNode=convertArrayToTree(numArray, 0, length-1);
}

shared_ptr<TreeNode> Tree::convertArrayToTree(int *numArray, int start, int end)
{
    if (start>end) return nullptr;

    size_t middle = (start+end)/2;
    shared_ptr<TreeNode> curNode(new TreeNode(numArray[middle]));

    curNode->left=convertArrayToTree(numArray, start, middle-1);
    curNode->right=convertArrayToTree(numArray, middle+1, end);

    return curNode;
}

void Tree::findPath(shared_ptr<TreeNode> curNode, const int targetNum, list<int> & path, int & curSum)
{
    if (!curNode) return;

    path.push_back(curNode->value);
    curSum += curNode->value;

    if (curSum==targetNum && !curNode->left && !curNode->right)
    {
        for (list<int>::iterator itr=path.begin(); itr != path.end(); itr++)
            cout << *itr << '\t';

        cout << endl;
    }

    if (curNode->left)
        findPath(curNode->left, targetNum, path, curSum);
    if (curNode->right)
        findPath(curNode->right, targetNum, path, curSum);

    path.pop_back();
    curSum -= curNode->value;

}

void Tree::inorder(shared_ptr<TreeNode> & curNode)
{
    if (!curNode) return;
    inorder(curNode->left);
    cout << curNode->value << "->";
    inorder(curNode->right);
}

void Tree::preorder(shared_ptr<TreeNode> & curNode)
{
    if (!curNode) return;
    cout << curNode->value << "->";
    preorder(curNode->left);
    preorder(curNode->right);
}

void Tree::postorder(shared_ptr<TreeNode> & curNode)
{
    if (!curNode) return;
    postorder(curNode->left);
    postorder(curNode->right);
    cout << curNode->value << "->";
}

void Tree::printList()
{
    if (!rootNode) return;
    shared_ptr<TreeNode> root = rootNode;
    cout << root->value << "->";
    while (root->right)
    {
        cout << root->value << "->";
        root = root->right;
    }
    cout << endl;

}

shared_ptr<TreeNode> Tree::convertTreeToList(shared_ptr<TreeNode> & root, bool asRight)
{
    if (!root) return nullptr;

    shared_ptr<TreeNode> tail = convertTreeToList(root->left, false);

    shared_ptr<TreeNode> head = convertTreeToList(root->right, true);

    tail->right = root;
    root->left = tail;
    root->right = head;
    head->left = root;

    shared_ptr<TreeNode> curNode = root;
    if (asRight)
        while (curNode->left) curNode = curNode->left;
    else
        while (curNode->right) curNode = curNode->right;

    return curNode;
}

shared_ptr<TreeNode> Tree::buildTree(const int start, const int end)
{
    if (start>end) return nullptr;

    int middle = start+(end-start)/2;
    shared_ptr<TreeNode> curPtr(new TreeNode(middle));
    curPtr->left = buildTree(start, middle-1);
    curPtr->right = buildTree(middle+1, end);

    return curPtr;
}

void Tree::printTree(shared_ptr<TreeNode> & root)
{
    if (!root) return;
    printTree(root->left);
    cout << root->value << "->" ;
    printTree(root->right);
}

// check binary seach tree // wrong
//bool Tree::isBST(shared_ptr<TreeNode> node, int &lastValue)
//{
//    if (!node) return true;

//    bool flag=true;
//    if (node->left) flag = isBST(node->left, lastValue);

//    if (!flag || lastValue >= node->value) return false;

//    lastValue = node->value;

//    if (node->right) flag = isBST(node->right, lastValue);

//    return flag;

//}
bool Tree::isBST(shared_ptr<TreeNode> &node, int minV, int maxV)
{
    if (!node) return true;

    if (node->value>maxV || node->value<=minV) return false;

    return isBST(node->left, minV, node->value) && isBST(node->right, node->value, maxV);
}

bool Tree::isBST_main(shared_ptr<TreeNode> &node)
{
    return isBST(node, INT_MIN, INT_MAX);
}

bool Tree::isBalancedBST(shared_ptr<TreeNode> &node, int &depth)
{
    if (!node)
    {
        depth=0;
        return true;
    }
    int leftDepth, rightDepth;
    if (isBalancedBST(node->left, leftDepth) && isBalancedBST(node->right, rightDepth))
    {
        int diff=leftDepth-rightDepth;
        if (diff>1 || diff<-1) return false;
        depth = 1+ (leftDepth > rightDepth ? leftDepth : rightDepth);
        return true;
    }
    else
        return false;
}

/** ???? See shared_ptr<TreeNode> convertTreeToList(shared_ptr<TreeNode> &root, bool asRight);
 * @brief Tree::convertTreeToList_inorder
 * @param treeptr
 * @param listptr
 */
void Tree::convertTreeToList_inorder(shared_ptr<TreeNode> &treeptr, shared_ptr<TreeNode> &listptr)
{
    if (!treeptr) return;

    if (treeptr->left)
        convertTreeToList_inorder(treeptr->left, listptr);

    treeptr->left=listptr;
    if (listptr)
        listptr->right = treeptr;

    listptr=treeptr;

    if (treeptr->right)
        convertTreeToList_inorder(treeptr->right, listptr);
}

shared_ptr<TreeNode> Tree::convertTreeToList_inorder_main(shared_ptr<TreeNode> &rootptr)
{
    if (!rootptr) return nullptr;

    shared_ptr<TreeNode> listptr(nullptr);

    convertTreeToList_inorder(rootptr, listptr);

    while (listptr->left)
        listptr=listptr->left;

    return listptr;
}
