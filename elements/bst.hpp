#include "bst.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <climits>
#include <set>
#include <map>
#include <stack>
#include <queue>

// see Selftest same problem with better understanding algorithm
template<typename T>
void BST<T>::preorder_iterative(const shared_ptr<BSTNode<T> > &root) {
    if (!root) return;
    stack<shared_ptr<BSTNode<T> > > S;
    S.push(root);

    while (!S.empty()) {
        auto curr = S.top();
        S.pop();
        while (curr) {
            cout << curr->data << " ";
            if (curr->right)
                S.push(curr->right);
            curr = curr->left;
        }
    }
    cout << endl;
}

template<typename T>
void BST<T>::postorder_iterative(const shared_ptr<BSTNode<T> > &root) {
    if (!root) return;
    stack<shared_ptr<BSTNode<T> > > S;
    S.push(root);
    shared_ptr<BSTNode<T> > prev=nullptr;
    while (!S.empty()) {
        auto curr = S.top();
        if (!curr->left && !curr->right || curr->left==prev || curr->right==prev) {
            cout << curr->data << " ";
            S.pop();
        } else {
            if (curr->right)
                S.push(curr->right);
            if (curr->left)
                S.push(curr->left);
        }
        prev = curr;
    }
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::buildBTFromPreOrderArr(const vector<T> &pre)
{
    stack<shared_ptr<BSTNode<T> > > S;
    // for pre order: last to first
    // for post order: first -> last
    for (auto it = pre.crbegin(); it!=pre.crend(); it++) {
        if (!*it)
            S.emplace(nullptr);
        else {
            auto left = S.top();
            S.pop();
            auto right = S.top();
            S.pop();
            S.emplace(new BSTNode<T>(*it, left, right));
        }
    }
    return S.top();
}

template<typename T>
void BST<T>::printInOrderWithParentField_norecursive(const shared_ptr<BSTNode<T> > &root) {
    if (!root) return;
    auto n = root;
    shared_ptr<BSTNode<T> > prev=nullptr, next;
    while (n) {
        // check prev
        if (!prev || prev->left==n || prev->right==n ) {
            if (n->left) {
                next = n->left;
            } else {
                cout << n->data << " ";
                next = n->right ? n->right : n->parent;
            }
        } else if( n->left == prev) {
            cout << n->data << " ";
            next = n->right ? n->right : n->parent;
        } else {
            next = n->parent;
        }
        prev = n;
        n=next;
    }
}

template<typename T>
void BST<T>::printPreOrderWithParentField_norecursive(shared_ptr<BSTNode<T> > &root) {
    auto n = root;
    shared_ptr<BSTNode<T> > prev=nullptr, next;
    while (n) {
        // first time to get here
        if (!prev || prev->left== n || prev->right==n) {
            cout << n->data << " ";
            if (n->left)
                next = n->left;
            else
                next = n->right ? n->right : n->parent;
        } else if (n->left==prev) {
            next = n->right ? n->right : n->parent;
        } else
            next = n->parent;
        prev = n;
        n = next;
    }
}

template<typename T>
void BST<T>::printPostOrderWithParentField_norecursive(shared_ptr<BSTNode<T> > &root) {
    shared_ptr<BSTNode<T> > n= root, prev=nullptr, next;
    while (n) {
        if (!prev || prev->left==n || prev->right==n) {
            if (n->left)
                next=n->left;
            else {
                if (!n->right)
                    cout << n->data << " ";
                next = n->right ? n->right : n->parent;
            }
        } else if (n->left==prev) {
            if (!n->right)
                cout << n->data << " ";
            next = n->right? n->right : n->parent;
        } else {
            cout << n->data << " ";
            next = n->parent;
        }
        prev=n;
        n=next;

    }
}

template<typename T>
void BST<T>::printBST_norecursive(shared_ptr<BSTNode<T> > &n) {
    stack<shared_ptr<BSTNode<T> > > s;
    shared_ptr<BSTNode<T> > curr = n;
    while (curr || !s.empty()) {
        if (curr) {
            s.push(curr);
            curr=s->left;
        } else {
            curr = s.top();
            s.pop();
            cout << curr->data;
            curr = curr->right;
        }
    }
}

template<typename T>
pair<shared_ptr<BSTNode<T> >, shared_ptr<BSTNode<T> > > BST<T>::convertTreeToList_twoPtr(shared_ptr<BSTNode<T> > &root) {
    pair<shared_ptr<BSTNode<T> >, shared_ptr<BSTNode<T> > > res;
    if (!root)
        return res;

    pair<shared_ptr<BSTNode<T> >, shared_ptr<BSTNode<T> > > part1 = convertTreeToList_twoPtr(root->left);
    pair<shared_ptr<BSTNode<T> >, shared_ptr<BSTNode<T> > > part3 = convertTreeToList_twoPtr(root->right);

    if (part1.second) {
        part1.second->right=root;
        root->left=part1.second;
    }
    if (part3.first) {
        root->right=part3.first;
        part3.first->left = root;
    }

    res.first = part1.first ? part1.first : root;
    res.second = part3.second ? part3.second : root;
    return res;

}

template<typename T>
void BST<T>::calc_view_from_above(const vector<LineSegment> &A) {
    if (!A.empty()) return;
    vector<EndPoint2> E;
    for (auto &a : A) {
        E.emplace_back(true, &a);
        E.emplace_back(false, &a);
    }
    sort(E.begin(), E.end());

    int pre=0;
    map<int, LineSegment*> table;
    vector<LineSegment> res;
    for (auto & e : E) {
        if (e.isLeft) {
            if (table.empty())
                pre=e.L->left;
            else if (table.begin()->second->height < e.L->height) {
                res.emplace_back(pre, e.L->left, table.begin()->second->color, table.begin()->second->height);
                pre=e.L->left;
            }
            table.insert(pair<int, LineSegment*>(e.L->height, e.L));
        }
        else {
            if (table.begin()->second->height == e.L->height) {
                res.emplace_back(pre, e.L->right,  table.begin()->second->color, table.begin()->second->height);
                pre=e.L->right;
            }
            table.erase(e.L->height);
        }
    }
//    if (!table.empty())
//        res.emplace_back(pre,table.begin()->second->right,  table.begin()->second->color, table.begin()->second->height);

    // print result
    for (auto &x : res)
        printf("%d, %d, %d, %d\n", x.left, x.right, x.color, x.height);

}

struct TripleData {
    int val, arrIdx, idx;
    bool operator<(const TripleData & that) const {
        return val!=that.val ? val<that.val : arrIdx < that.arrIdx;
    }
    TripleData(int _val, int _arrIdx, int _idx) : val(_val), arrIdx(_arrIdx), idx(_idx) {}
};

template<typename T>
int BST<T>::find_min_dist_sorted_arrays(vector<vector<int> > &arr) {
    if (arr.empty()) return -1;
    set<TripleData> monit;
    int res=numeric_limits<int>::max();

    for (int i=0; i<arr.size(); i++) {
        if (arr[i].empty()) return -1;
         monit.insert(TripleData{arr[i][0], i, 0});
    }

    while (true) {
        res = min(res, monit.cbegin()->val-monit.begin()->val);
        auto it = monit.begin();
        int idx=it->idx;
        int arrIdx=it->arrIdx;
        if (++idx>=arr[arrIdx].size())
            return res;
        TripleData x(arr[arrIdx][idx], arrIdx, idx);
        monit.erase(it);
        monit.insert(x);
    }
}

template<typename T>
void BST<T>::find_nodes_between(unique_ptr<TreeNode<T> > &r, T minv, T maxv, vector<TreeNode<T> *> & res) {
    if (!r) return;
    if (r->data < minv)
        find_nodes_between(r->right, minv, maxv, res);
    else if (r->data > maxv)
        find_nodes_between(r->left, minv, maxv, res);
    else {
        res.push_back(r.get());
        find_nodes_between(r->right, minv, maxv, res);
        find_nodes_between(r->left, minv, maxv, res);
    }
}

// find the first key less than k
template<typename T>
bool find_nodes_between_withSizeField_helper_lessthan(const shared_ptr<BSTNode<T> > &n, int k) {
    auto curr=n; int tmp=0; int num=0;
    while (curr) {
        if (n->data==k) {
//            tmp = curr->left ? curr->left->size : 0;
            tmp = num+(curr->left?curr->left->size:0);
            curr= curr->left;
        }
        if (n->data > k)
            curr=curr->left;
        else {
            num += 1+(curr->left?curr->left->size:0);
            curr = curr->right;
        }
    }
    return tmp==0 ? num : tmp;
}

// find the first key greater than k
template<typename T>
bool find_nodes_between_withSizeField_helper_greatthan(const shared_ptr<BSTNode<T> > &n, int k) {
    auto curr=n; int tmp=0; int num=0;
    while (curr) {
        if (n->data==k) {
            tmp = curr->left ? num + 1+ curr->left->size : num + 1;
            curr= curr->right;
        }
        if (n->data > k)
            curr=curr->left;
        else {
            num += 1+(curr->left?curr->left->size:0);
            curr = curr->right;
        }
    }
    return tmp==0 ? num : tmp;
}

template<typename T>
int BST<T>::find_nodes_between_withSizeField(shared_ptr<BSTNode<T> > &n, T minv, T maxv) {
    // the last less that minv
    int left = find_nodes_between_withSizeField_helper_lessthan(n, minv);
    // the first great than maxv
    int right = find_nodes_between_withSizeField_helper_greatthan(n, maxv);
    return right-left;
}

template<typename T>
bool BST<T>::is_r_s_descendat_ancestro_m(unique_ptr<TreeNode<T> > &r, unique_ptr<TreeNode<T> > &s, unique_ptr<TreeNode<T> > &m) {
    auto * curr_r=r.get(), * curr_s=s.get();

    while (curr_r && curr_r != s.get() && curr_s && curr_s !=r.get()) {
        if (curr_r == m.get() || curr_s==m.get())
            return true;
        curr_r = curr_r->data < s->data ? curr_r->right.get() : curr_r->left.get();
        curr_s = curr_s->data < r->data ? curr_s->right.get() : curr_s->left.get();
    }

    while (curr_r && curr_r != s.get()) {
        if (curr_r == m.get())
            return true;
        curr_r = curr_r->data < s->data ? curr_r->right.get() : curr_r->left.get();
    }
    while (curr_s && curr_s !=r.get()) {
        if (curr_s==m.get())
            return true;
        curr_s = curr_s->data < r->data ? curr_s->right.get() : curr_s->left.get();
    }
    return false;
}

template<typename T>
TreeNode<T> * BST<T>::find_LCA(unique_ptr<TreeNode<T> > &root, unique_ptr<TreeNode<T> > &a, unique_ptr<TreeNode<T> > &b) {
    if (!root) return nullptr;

    if (root->data < min<T>(a->data, b->data))
        return find_LCA(root->right, a, b);
    else if (root->data > max<T>(a->data, b->data))
        return find_LCA(root->left, a, b);
    else
        return root.get();
}

template<typename T>
TreeNode<T> * build_BST_from_preorder_helper(vector<T> &arr, int s, int e) {
    if (s<e) {
        int idx=s+1;
        while (idx<e && arr[idx]<arr[s])
            idx++;
//        auto it = upper_bound(arr.begin()+s, arr.begin()+e, arr[s]);
//        int idx = distance(arr.begin(), it);

        return new TreeNode<T>(arr[s], unique_ptr<TreeNode<T> >(build_BST_from_preorder_helper(arr, s+1, idx)),
                               unique_ptr<TreeNode<T> >(build_BST_from_preorder_helper(arr, idx, e)));
    }
}

template<typename T>
TreeNode<T> * build_BST_from_preorder_helper_fast(vector<T> &arr, int &idx, T minv, T maxv) {
    if (idx>=arr.size() || arr[idx]<minv || arr[idx]>maxv)
        return nullptr;

    int curr=idx;
    idx++;

    return new TreeNode<T>(arr[curr], unique_ptr<TreeNode<T> >(build_BST_from_preorder_helper_fast(arr, idx, minv, arr[curr])),
                           unique_ptr<TreeNode<T> >(build_BST_from_preorder_helper(arr, idx, arr[curr], maxv)));
}

template<typename T>
TreeNode<T> * BST<T>::build_BST_from_preorder(const vector<T> &arr) {
    if (arr.empty()) return nullptr;

    int idx=0;
    return build_BST_from_preorder_helper(arr, idx, numeric_limits<T>::min(), numeric_limits<T>::max());
//    return build_BST_from_preorder_helper(arr, 0, arr.size());
}

template<typename T>
static void find_largest_k_elements_helper(const unique_ptr<TreeNode<T> > & root, int k, vector<T> & res) {
    if (!root || res.size()>=k) return;
    find_largest_k_elements_helper(root->right, k, res);
    if (res.size()<k) {
        res.push_back(root->data);
        find_largest_k_elements_helper(root->left, k, res);
    }
}

template<typename T>
vector<T> BST<T>::find_largest_k_elements(const unique_ptr<TreeNode<T> > &root, int k) {
    vector<T> res;
    find_largest_k_elements_helper(root, k, res);
    return res;
}

template<typename T>
static shared_ptr<BSTNode<T> > convertDLLtoBST_helper(shared_ptr<BSTNode<T> > &head, int s, int e)
{
    if (!head || s>=e) return nullptr;

    shared_ptr<BSTNode<T> > curr=nullptr;
    int mid=s+(e-s)>>1;
    auto left = convertDLLtoBST(head, s, mid);
    curr=head;
    curr->left=left;
    head=head->right;
    curr->right=convertDLLtoBST(head, mid, e);

    return curr;
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::convertDLLtoBST(shared_ptr<BSTNode<T> > &head) {
    if (!head) return nullptr;
    int len=0;
    shared_ptr<BSTNode<T> > curr=head;
    while (curr) {
        len++;
        curr=curr->right;
    }

    return convertDLLtoBST_helper(head, 0, len);
}

template<typename T>
TreeNode<T> * BST<T>::find_k_minBST(const unique_ptr<TreeNode<T> > &root, const T key) {
    if (!root || root->data > key) return nullptr;

    if (root->data==key)
        return root.get();

    if (root->right && key > root->right->data)
        return find_k_minBST(root->right, key);

    return find_k_minBST(root->left, key);
}

template<typename T>
TreeNode<T> * BST<T>::find_first_larger_k_iterative(const unique_ptr<TreeNode<T> > &root, const T key) {
    if (!root) return nullptr;
    auto curr=root.get();
    TreeNode<T> * first=nullptr;
    bool found_k=false;

    while(curr) {
        if (curr->data > key) {
            first = curr;
            curr=curr->left.get();
        } else {
            if (curr->data==key)
                found_k=true;
            curr=curr->right.get();
        }
    }
    return found_k ? first : nullptr;
}

template<typename T>
TreeNode<T>* BST<T>::find_first_equal_k_iterative(const unique_ptr<TreeNode<T> > &root, const T key) {
    if (!root) return nullptr;

    TreeNode<T> * curr=root.get(), *first=nullptr;

    while (curr) {
        if (curr->data==key){
            first=curr;
            curr=curr->left.get();
        } else
            curr=curr->data > key ? curr->left.get() : curr->right.get();
    }
    return first;
}

template<typename T>
TreeNode<T>* BST<T>::find_first_equal_k_recursive(const unique_ptr<TreeNode<T> > &root, const T key) {
    if (!root)
        return nullptr;

    if (root->data==key) {
        auto * node = find_first_equal_k(root->left, key);
        return node ? node : root.get();
    } else
        return root->data > key ? find_first_equal_k(root->left, key): find_first_equal_k(root->right, key);
}

template<typename T>
bool BST<T>::is_BST_constSpace(const unique_ptr<TreeNode<T> > &root) {
    auto * n = root.get();
    T last = numeric_limits<T>::min();
    bool res=true;

    while (n) {
        if (n->left) {
            auto *pre = n->left.get();
            while (pre->right && pre->right.get()!=n)
                pre=pre->right.get();

            if (pre->right) {
                pre->right.release();
                if (n->data <last)
                    res=false;
                last = n->data;
                n=n->right.get();
            } else {
                pre->right.reset(n);
                n=n->left.get();
            }


        } else {
            if (n->data<last)
                res=false;
            last = n->data;
            n =n->right.get();
        }
    }
    return true;
}

template<typename T>
struct QNode {
    TreeNode<T> * node;
    T minv, maxv;

};

template<typename T>
bool BST<T>::is_BST_iterative(const unique_ptr<TreeNode<T> > &root) {
    if (!root) return true;

    queue<QNode<T> > q;
    q.emplace(root.get(), numeric_limits<T>::min(), numeric_limits<T>::max());

    while (!q.empty()) {
        QNode<T> n = q.front();
        q.pop();
        if (n.node->data < n.minv || n.node->data > n.maxV)
            return false;
        if (n.node->left) q.emplace(n.node->left, n.minv, n.node->data);
        if (n.node->right) q.emplace(n.node->right, n.node->data, n.maxv);
    }
    return true;

}

template<typename T>
bool is_BST_recursive_helper(const unique_ptr<TreeNode<T> > &root, T minV, T maxV) {
    if (!root) return true;

    if (root->data<minV || root->data>maxV)
        return false;

    return is_BST_recursive_helper(root->left, minV, root->data)
            && is_BST_recursive_helper(root->right, root->data, maxV);
}

template<typename T>
bool BST<T>::is_BST_recursive(const unique_ptr<TreeNode<T> > &root) {
    return is_BST_recursive_helper(root, numeric_limits<T>::min(), numeric_limits<T>::max());
}

template<typename T>
BST<T>::BST()
{
}

template<typename T>
void printDLL(shared_ptr<BSTNode<T> > & root)
{
    if (root)
    {
        shared_ptr<BSTNode<T> > curr = root;
        while (curr)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
    }
}

template<typename T>
void BST<T>::printTree(shared_ptr<BSTNode<T> > & node)
{
    if (!node) return;
    printTree(node->left);
    cout << node->data << " ";
    printTree(node->right);
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::buildBSTfromVector(const vector<T> & arr, int s, int e)
{
    if (arr.empty() || s>e) return nullptr;
    int m=s+((e-s)>>1);
    shared_ptr<BSTNode<T> > left = buildBSTfromVector(arr, s, m-1);
    shared_ptr<BSTNode<T> > right = buildBSTfromVector(arr, m+1, e);
    shared_ptr<BSTNode<T> > node = shared_ptr<BSTNode<T> >(new BSTNode<T>(arr[m], left, right));

    return node;
}

template<typename T>
void BST<T>::testBSTtoDLL(vector<T> &arr)
{
    shared_ptr<BSTNode<T> > tree = buildBSTfromVector(arr, 0, int(arr.size())-1);
    cout << "Tree:" << endl;
    printTree(tree);
    cout << endl;
    shared_ptr<BSTNode<T> > prevNode=nullptr, listHead=nullptr;
    convertBSTtoDLL(tree, prevNode, listHead);

    cout << "DLL:"<< endl;
    printDLL(listHead);
}

// time complexity O(n)
template<typename T>
void BST<T>::convertBSTtoDLL(shared_ptr<BSTNode<T> > & currNode, shared_ptr<BSTNode<T> > &prevNode, shared_ptr<BSTNode<T> > & listHead)
{
    if (currNode)
    {
        convertBSTtoDLL(currNode->left, prevNode, listHead);
        if (prevNode)
        {
            prevNode->right = currNode;
            currNode->left = prevNode;
        }
        else
        {
            listHead = currNode;
        }
        prevNode = currNode;
        convertBSTtoDLL(currNode->right, prevNode, listHead);
    }
}

/**
 * @brief convertBSTtoList: time complexity is O(n^2)
 * @param node
 * @param isRight
 * @return
 */
template<typename T>
shared_ptr<BSTNode<T> > convertBSTtoList(shared_ptr<BSTNode<T> > & node, bool isRight)
{
    if (!node) return nullptr;

    shared_ptr<BSTNode<T> > left = convertBSTtoList(node->left, false);
    shared_ptr<BSTNode<T> > right = convertBSTtoList(node->right, true);

    node->left = left;
    node->right = right;
    if (!left)
        left->right = node;
    if (!right)
        right->left = node;

    shared_ptr<BSTNode<T> > curr=node;
    if (isRight)
    {
        while (curr->left)
            curr = curr->left;
    }
    else
    {
        while (curr->right)
            curr = curr->right;
    }

    return curr;
}

template<typename T>
void advance_onestep(shared_ptr<BSTNode<T> > & head, shared_ptr<BSTNode<T> > & tail, shared_ptr<BSTNode<T> > &node)
{
    if (head)
    {
        tail->right = node;
        node->left = tail;
    }
    else
    {
        head = node;
    }
    tail = node;

    node=node->right;
}

template<typename T>
shared_ptr<BSTNode<T> > mergeTwoList(shared_ptr<BSTNode<T> > &Alist, shared_ptr<BSTNode<T> > &Blist)
{
    shared_ptr<BSTNode<T> > sortList=nullptr, tail=nullptr;

    while (Alist && Blist)
        advance_onestep(sortList, tail, Alist->data < Blist->data ? Alist : Blist);

    if (Alist)
        advance_onestep(sortList, tail, Alist);
    if (Blist)
        advance_onestep(sortList, tail, Blist);

    return sortList;

}

template<typename T>
int getLength(shared_ptr<BSTNode<T> > & root)
{
    shared_ptr<BSTNode<T> > curr = root;
    int len=0;
    while(curr)
    {
        len++;
        curr = curr->right;
    }
    return len;
}

template<typename T>
shared_ptr<BSTNode<T> > buildBSTfromList(shared_ptr<BSTNode<T> > & node, int s, int e)
{
    if (!node || s>e) return nullptr;
    int m = s + ((e-s)>>1);
    shared_ptr<BSTNode<T> > left = buildBSTfromList(node, s, m-1);
    shared_ptr<BSTNode<T> > curr = node;
    node=node->right;
    curr->left = left;
    curr->right = buildBSTfromList(node, m+1, e);
    return curr;
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::mergeTwoBST(shared_ptr<BSTNode<T> > &A, shared_ptr<BSTNode<T> > &B)
{
    shared_ptr<BSTNode<T> > AlistHead=nullptr, AlistPrev=nullptr, BlistHead=nullptr, BlistPrev=nullptr;
    convertBSTtoDLL(A, AlistPrev, AlistHead);
    convertBSTtoDLL(B, BlistPrev, BlistHead);

    shared_ptr<BSTNode<T> > mergedList = mergeTwoList(AlistHead, BlistHead);
    printDLL(mergedList);

    int len = getLength(mergedList);

    return buildBSTfromList(mergedList, 0, len-1);
}

template<typename T>
void divideVector(const vector<T> &arr, vector<T> & A, vector<T> &B)
{
    int mid = arr.size()>>1;
    for (int i=0; i<arr.size(); i++)
    {
        if (i<=mid)
            A.push_back(arr[i]);
        else
            B.push_back(arr[i]);
    }

}

template<typename T>
void BST<T>::testmergeTwoBST(const vector<T> &arr)
{
    // get two vectors which are used to build two BST
    vector<T> Avect, Bvect;
    divideVector(arr, Avect, Bvect);
    copy(Avect.begin(), Avect.end(), ostream_iterator<int>(cout, " ")); cout << endl;
    copy(Bvect.begin(), Bvect.end(), ostream_iterator<int>(cout, " ")); cout << endl;

    // get the merge result
    shared_ptr<BSTNode<T> > A = buildBSTfromVector(Avect, 0, Avect.size()-1);
    printTree(A);
    cout << endl;
    shared_ptr<BSTNode<T> > B = buildBSTfromVector(Bvect, 0, Bvect.size()-1);
    printTree(B);
    cout << endl;
    shared_ptr<BSTNode<T> > mergeList = mergeTwoBST(A, B);
    // print the result
    printTree(mergeList);

}

struct ArrData
{
    int arrId, index, value;

    ArrData(int _arrId, int _index, int _value)
        :arrId(_arrId), index(_index), value(_value){}

    bool operator<(const ArrData & that) const
    {
        return value != that.value ? value < that.value : arrId < that.arrId;
    }
};

template<typename T>
int BST<T>::findMinDistanceSortedArrays(const vector<vector<int> > &arr)
{
    set<ArrData> headers;
    for (int i=0; i<arr.size(); i++)
        headers.insert(ArrData(i, 0, arr[i][0]));

    int minDist = INT_MAX;
    while(true)
    {
        minDist = std::min(minDist, headers.rbegin()->value - headers.begin()->value);
        auto itr = headers.begin();
        if (itr->index+1 >= arr[itr->arrId].size())
            return minDist;

        ArrData update(itr->arrId, itr->index+1, arr[itr->arrId][itr->index+1]);
        headers.erase(itr);
        headers.insert(update);

    }
}

struct EndPoint
{
    int val;
    shared_ptr<LineSegment> line;
    bool isLeft;

    EndPoint(int v, bool _isLeft, shared_ptr<LineSegment> &_line)
        :val(v), isLeft(_isLeft), line(_line) {}

    bool operator<(EndPoint & that) const
    {
        return val != that.val ? val < that.val : line->height < that.line->height;
    }
};

template<typename T>
vector<shared_ptr<LineSegment> > BST<T>::computeViewFromAbove(vector<shared_ptr<LineSegment> > &arr)
{
    vector<EndPoint> points;
    for (auto t : arr)
    {
        points.push_back(EndPoint(t->left, true, t));
        points.push_back(EndPoint(t->right, false, t));
    }

    sort(points.begin(), points.end());

    vector<shared_ptr<LineSegment> > view;
    map<int, shared_ptr<LineSegment> > table;
    shared_ptr<LineSegment> prev = nullptr;
    for (auto e : points)
    {
        if (e.isLeft)
            table.insert(pair<int, shared_ptr<LineSegment> >(e.line->height, e.line));
        else
        {
            table.erase(e.line->height);
//            if (table.empty())
//                prev=nullptr;
        }

        if (!prev)
        {
            prev = e.line;
        }
        else
        {
            if (prev->height != table.rbegin()->first)
            {
                view.push_back(shared_ptr<LineSegment>(new LineSegment(prev->left, e.val, prev->color, prev->height)));
                prev = shared_ptr<LineSegment>(new LineSegment(e.val, table.rbegin()->second->right, table.rbegin()->second->color, table.rbegin()->second->height));
            }
        }
    }

    if (prev)
    {
        view.push_back(prev);
    }
    return view;
}

pair<int, int> computeHeightDiameter(shared_ptr<TreeEdgeNode> & node)
{
    pair<int, int> maxHeight(0,0);
    int diameter = 0;
    for (auto & e : node->edges)
    {
        auto heightDiameter = computeHeightDiameter(e.first);
        int heightTill = heightDiameter.first+e.second;
        if (heightTill > maxHeight.first)
        {
            maxHeight.second = maxHeight.first;
            maxHeight.first = heightTill;
        }
        else if (heightTill > maxHeight.second)
            maxHeight.second = heightTill;

        diameter = max(diameter, heightDiameter.second);
    }

    return make_pair(maxHeight.first, max(diameter, maxHeight.first+maxHeight.second));
}

template<typename T>
int BST<T>::computeTreeDiameter(shared_ptr<TreeEdgeNode> &node)
{
    return node ? computeHeightDiameter(node).second : 0;
}

template<typename T>
void BST<T>::printPostOrderTraversalWithoutRecursion(shared_ptr<BSTNode<T> > &node)
{
    if (!node) return;

    stack<shared_ptr<BSTNode<T> > > pointers;
    shared_ptr<BSTNode<T> > prev=nullptr, curr=node;
    pointers.push(node);

    while (!pointers.empty())
    {
        curr = pointers.top();
        if (!curr)
            pointers.pop();
        else if (! curr->left && !curr->right )
        {
            // print leave
            cout << curr->data << endl;
            pointers.pop();
        }
        else if (curr->left == prev)
        {
            // left has been visited
            pointers.push(curr->right);
        }
        else if (curr->right == prev)
        {
            cout << curr->data << endl;
            pointers.pop();
        }
        else
        {
            pointers.push(curr->left);
        }

        prev = curr;
    }

    cout << endl;


}

template<typename T>
static shared_ptr<BSTNode<T> > buildTreeHelper(const vector<T> &pre, int pre_s, int pre_e,
                                               const vector<T> &in, int in_s, int in_e) {
    if (pre_e<pre_s && in_e>in_s) {
    auto t = find(in.cbegin()+in_s, in.cend()+in_e, pre[pre_s]);
    int left_tree_length = distance(in.cbegin(), t) - in_s;

    return shared_ptr<BSTNode<T> >(new BSTNode<T>(pre[pre_s],
                                             buildTreeHelper(pre, pre_s+1, pre_s+1+left_tree_length, in, in_s, in_s+left_tree_length),
                                             buildTreeHelper(pre, pre_s+1+left_tree_length, pre_e, in, distance(in.begin(), t)+1, in_e)));

    } else
        return nullptr;
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::buildTreeFromInorderPreorder(const vector<T> &pre, const vector<T> &in) {
    return buildTreeHelper(pre, 0, pre.size(), in, 0, in.size());
}

template<typename T>
static shared_ptr<BSTNode<T> > buildTreeHelper_post(const vector<T> &pre, int pre_s, int pre_e,
                                               const vector<T> &in, int in_s, int in_e) {
    if (pre_e>pre_s && in_e>in_s) {
    auto t = find(in.cbegin()+in_s, in.cend()+in_e, pre[pre_e-1]);
    int left_tree_length = distance(in.cbegin(), t) - in_s;

    return shared_ptr<BSTNode<T> >(new BSTNode<T>(pre[pre_e-1],
                                             buildTreeHelper_post(pre, pre_s, pre_s+left_tree_length, in, in_s, in_s+left_tree_length),
                                             buildTreeHelper_post(pre, pre_s+left_tree_length, pre_e-1, in, distance(in.begin(), t)+1, in_e)));

    }
}

template<typename T>
shared_ptr<BSTNode<T> > BST<T>::buildTreeFromInorderPostorder(const vector<T> &pre, const vector<T> &in) {
    return buildTreeHelper_post(pre, 0, pre.size(), in, 0, in.size());
}


template<typename T>
shared_ptr<BSTNode<T> > BST<T>::reconstruct_preorder(const vector<T> &preorder) {
    stack<shared_ptr<BSTNode<T> > > s;

    for (auto it=preorder.crbegin(); it!=preorder.crend(); it++) {
        if (!*it) {
            s.push(nullptr);
        } else {
            auto l = s.top();
            s.pop();
            auto r = s.top();
            s.pop();
            s.push(shared_ptr<BSTNode<T> >(new BSTNode<T>(*it, l, r)));
        }
    }
    return s.top();

}

template<typename T>
static void print_exterior_left_boundary(const shared_ptr<BSTNode<T> > & n, bool isBoundary) {
    if (n) {
        if (isBoundary || (n->left && n->right) ) {
            cout << n->data << " ";
        }
        print_exterior_left_boundary(n->left, isBoundary);
        print_exterior_left_boundary(n->right, isBoundary && !n->left);
    }
}

template<typename T>
static void print_exterior_right_boundary(const shared_ptr<BSTNode<T> > & n, bool isBoundary) {
    if (n) {
        print_exterior_right_boundary(n->left, isBoundary && !n->right);
        print_exterior_right_boundary(n->right, isBoundary);
        if (isBoundary || (n->left && n->right) ) {
            cout << n->data << " ";
        }
    }
}

// note: the original assumption in the element book is that there is left and right leave at the root. Add the following lines to get rid of the assumption
template<typename T>
void BST<T>::print_exterior_bst(const shared_ptr<BSTNode<T> > &root) {
    if (root) {
        cout << root->data << " ";
        // if root left or right leave is nullptr, go to next layer until both left and right leave are not nullptr
        if (!root->left || !root->right) {
            if (root->left) print_exterior_bst(root->left);
            else
                print_exterior_bst(root->right);
            return;
        }
        print_exterior_left_boundary(root->left, true);
        print_exterior_right_boundary(root->right, true);
    }
}

// binary tree instead of bst. Check find_LCA in Line 342 for bst solution 
template<typename T>
shared_ptr<BSTNode<T> > BST<T>::LCA(shared_ptr<BSTNode<T> > &root, shared_ptr<BSTNode<T> > &a, shared_ptr<BSTNode<T> > &b) {
    if (!root)
        return nullptr;
    if (root==a || root==b)
        return root;

    auto resl=LCA(root->left, a, b);
    auto resr=LCA(root->right, a, b);
    if (resl && resr)
        return root;
    else {
        return resl ? resl : resr;
    }
}

template<typename T>
static void findPathSum_helper(shared_ptr<BSTNode<T> >&root, T sum, vector<shared_ptr<BSTNode<T> > >&path, T partialSum) {
    if (!root) return;

    partialSum += root->data;
    if (partialSum==sum) {
        for (auto &n: path)
            cout << n->data << ",";
        cout << endl;
    }

    path.push_back(root);
    // for any start and end
    // T v=0;
    // for (int i=path.size()-1; i>=0; i--) {
    //     v += path[i]->data;
    //     if (v==sum) { // print
    //         for (int k=i; k<path.size(); k++)
    //             cout << path[i]->data;
    //     }
    //     cout << endl;
    // }

//---------------- for the path from root
    //    if (sum-root->data==0)  {
//        for (auto &x: path)
//            cout << x->data;
//        cout << endl;
//    }

//    findPathSum_helper(root->left, sum-root->data, path);
//    findPathSum_helper(root->right, sum-root->data, path);
//-----------------------------------------

    findPathSum_helper(root->left, sum, path, partialSum);
    findPathSum_helper(root->right, sum, path, partialSum);
    path.pop_back();
}

template<typename T>
list<BSTNode<T> > BST<T>::findPathSum(shared_ptr<BSTNode<T> > &root, T sum) {
    vector<shared_ptr<BSTNode<T> > > path;
    findPathSum_helper(root, sum, path, 0);
}

void LogAnalyzer::popItems(int timestamp) {
    while (!Q.empty()) {
        auto x = Q.front();
        if (timestamp-x.second<winSize)
            break;
        Q.pop();
        auto it = M.find(x.first);
        auto itb = it->second;
        int freq = itb->second-1;
        int key = itb->first;
        B.erase(itb);
        M.erase(x.first);
        if (freq) {
            B.insert(pair<int,int>(key, freq));
            auto t = B.find(pair<int,int>(key, freq));
            M[x.first]=t;
        }
    }
}

void LogAnalyzer::add(int ipaddress, int timestamp) {
    popItems(timestamp);

    // add new item
    Q.push(pair<int, int>(ipaddress, timestamp));
    if (M.find(ipaddress) == M.end()) {
        B.insert(pair<int,int>(ipaddress, 1));
        auto it = B.find(pair<int,int>(ipaddress, 1));
        M.emplace(ipaddress, it);
    } else {
        auto it=M.find(ipaddress)->second;
        int ip = it->first;
        int freq = it->second+1;
        B.erase(it);
        B.insert(pair<int,int>(ip, freq));
        auto t = B.find(pair<int, int>(ip, freq));
        M[ipaddress]=t;
    }
}

vector<int> LogAnalyzer::common(int timestamp, int k) {
    popItems(timestamp);
    if (k>B.size() || k<0)
        throw invalid_argument("k is too larger than the size of elements or k<0");
    vector<int> res;
    int count=0;
    for (auto i : B) {
        res.push_back(i.first);
        if (++count>=k)
            break;
    }
    return res;
}
