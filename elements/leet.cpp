#include "leet.h"
#include <queue>
#include <map>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <stack>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>

Leet::Leet()
{
}

int Leet::lengthLastWord(string S) {
    int k=0, pre=0;
    for (int i=0; i<S.size(); i++) {
        if (S[i]==' ') {
            if (i-1>=0 && S[i-1] != ' ')
                pre=k;
            k=0;
        }
        else
            k++;
    }
    return S[S.size()-1]==' '? pre : k;
}

vector<Misc::Interval> Leet::insertInterval(const vector<Misc::Interval> &A, Misc::Interval a) {
    unordered_set<int> eraseList;
    for (int i=0; i<A.size(); i++) {
        Misc::Interval x = A[i];
        if (x.high>=a.low && x.low<=a.high) {
            a.low = min(a.low, x.low);
            a.high = max(a.high, x.high);
            eraseList.insert(i);
        }
    }
    vector<Misc::Interval> ret;
    ret.push_back(a);
    for (int i=0; i<A.size(); i++) {
        if (eraseList.find(i)!=eraseList.end())
            ret.push_back(A[i]);
    }
    return ret;
}

vector<Misc::Interval> Leet::mergeIntervals(vector<Misc::Interval> &A) {
    sort(A.begin(), A.end(), [](const Misc::Interval &a, const Misc::Interval &b){ return a.low <b.low;});
vector<Misc::Interval> ret;
if (A.empty())
return ret;
Misc::Interval curr;
for (int i=0; i<A.size(); i++) {
    auto x=A[i];
    if (i==0)
        curr=x;
    else {
        if (x.low<curr.high && x.high>curr.high)
            curr.high=x.high;
        else {
            ret.push_back(curr);
            curr=x;
        }

    }
}
ret.push_back(curr);
return ret;
}

string Leet::minimumWindowSubstring(string S, string T) {
    list<int> L;
    unordered_map<char, list<int>::iterator > M;
    for (auto &c : T)
        M[c]=L.end();

    pair<int, int> ret(-1, -1);
    for (int i=0; i<S.size(); i++) {
        char c=S[i];
        if (M.find(c)!=M.end()) {
            auto it = M.find(c);
            if (it->second != L.end()){
                L.erase(it->second);
            }
            L.push_back(i);
            M[S[i]]=--L.end();

            if (L.size()==M.size() && (ret.first ==-1 || i-L.front()<ret.second-ret.first)) {
                ret={L.front(), L.back()};
            }
        }
    }
    if (ret.first!=-1)
        return S.substr(ret.first, ret.second-ret.first+1);
    else
        return string();
}

string Leet::minimumWindowSubstring_sequential(string S, string T) {
    vector<int> L(T.size(), -1);
    unordered_map<char, int> M;
    vector<int> D(T.size(), INT_MAX);

    for (int i=0; i<T.size(); i++)
        M[T[i]]=i;

    pair<int, int> ret(-1, -1);
    for (int i=0; i<S.size(); i++) {
        char c = S[i];
        auto it = M.find(c);
        if (it!=M.end()) {
            if (it->second==0) {
                D[0]=1;
//                copy(D.begin(), D.end(), ostream_iterator<int>(cout, " "));
//                cout << endl;
            }
            else if (D[it->second-1] != INT_MAX) {
                D[it->second] = D[it->second-1] + i-L[it->second-1];
//                copy(D.begin(), D.end(), ostream_iterator<int>(cout, " "));
//                cout << "L" << endl;
//                copy(L.begin(), L.end(), ostream_iterator<int>(cout, " "));
//                cout << endl;
            }
            else
                continue;

            L[it->second]=i;
            if (it->second==T.size()-1 && (ret.first==-1 || D.back()<ret.second-ret.first+1)) {
                ret={i-D.back()+1, i};
//                cout << i << " " << ret.first << " " << ret.second << " " << D.back() << endl;
//                cin.get();
            }
        }

    }
    if (ret.first != -1)
        return S.substr(ret.first, ret.second-ret.first+1);
    else
        return string();
}

void Leet::postorder_bt_iterative(shared_ptr<TNode> &n) {
    if (!n) return;
    stack<shared_ptr<TNode> > S;
    S.push(n);

    shared_ptr<TNode> prev=nullptr;
    while (!S.empty()) {
        auto curr = S.top();
        if (!prev || prev->left == curr || prev->right == curr) {
            if (curr->left)
                S.push(curr->left);
            else if (curr->right)
                S.push(curr->right);
            else {
                cout << curr->data << " ";
                S.pop();
            }

        } else if (curr->left==prev) {
            if (curr->right)
                S.push(curr->right);
            else {
                cout << curr->data << " ";
                S.pop();
            }

        } else if (curr->right==prev) {
            cout << curr->data << " ";
            S.pop();
        }
        prev=curr;
    }
}

void Leet::preorder_bt_iterative(shared_ptr<TNode> &n) {
    if (!n) return;
    stack<shared_ptr<TNode> > S;
    S.push(n);

    while (S.empty()) {
        auto curr=S.top();
        S.pop();
        cout << curr->data << " ";

        if (curr->right)
            S.push(curr->right);
        if (curr->left)
            S.push((curr->left));
    }

//    shared_ptr<TNode> prev=nullptr;
//    while (!S.empty()) {
//        auto curr = S.top();
//        cout << curr->data << " ";
//        if (!prev || prev->left == curr || prev->right == curr) {
//            if (curr->left) {
//                S.push(curr->left);
//            }
//            else if (curr->right)
//                S.push(curr->right);
//            else {
//                S.pop();
//            }

//        } else if (curr->left==prev) {
//            if (curr->right)
//                S.push(curr->right);
//            else {
//                S.pop();
//            }

//        } else {
////            cout << curr->data << " ";
//            S.pop();
//        }
//        prev=curr;
//    }
}

int Leet::maxProductSubarray(const vector<int> A) {
    if (A.empty())
        throw invalid_argument("empty array");
    int maxv=A[0];
    int minv=A[0];
    int overal=A[0];

    for (int i=1; i<A.size(); i++) {
        int maxtmp = maxv;
        int mintmp = minv;
        maxv = max(A[i], max(maxtmp*A[i], mintmp*A[i]));
        minv = min(A[i], min(maxtmp*A[i], mintmp*A[i]));
        overal = max(maxv, overal);
    }
    return overal;
}

shared_ptr<Leet::GNode> Leet::copyGraph(const shared_ptr<GNode> root) {
    if (!root)
        return nullptr;

    shared_ptr<GNode> copyroot(new GNode(root->data));
    queue<shared_ptr<GNode> > q;
    q.push(root);
    unordered_map<shared_ptr<GNode>, shared_ptr<GNode> > table;
    table[root]=copyroot;

    while(!q.empty()) {
        shared_ptr<GNode> curr = q.front();
        q.pop();
        shared_ptr<GNode> copycurr=table[curr];

        for (auto &t: curr->neighbors) {
            if (table.find(t) == table.end()) {
                shared_ptr<GNode> copyneighbor(new GNode(t->data));
                table[t]=copyneighbor;
                q.push(t);
            }
            copycurr->neighbors.insert(table[t]);
        }
    }
    return copyroot;
}

void copyGraph_recursive_helper(const shared_ptr<Leet::GNode> &root,
                                unordered_map<shared_ptr<Leet::GNode>, shared_ptr<Leet::GNode> > &table) {
    shared_ptr<Leet::GNode> node(new Leet::GNode(root->data));
    table[root]=node;
    for (auto & e: root->neighbors) {
        if (table.find(e) != table.end()) {
            copyGraph_recursive_helper(e, table);
        }
        node->neighbors.emplace(table[e]);
    }
}

shared_ptr<Leet::GNode> Leet::copyGraph_recursive(const shared_ptr<GNode> root) {
    if(!root) return nullptr;
    unordered_map<shared_ptr<GNode>, shared_ptr<GNode> > table;
    copyGraph_recursive_helper(root, table);
    return table[root];
}

static int getDigit(int x, int digit) {
    int tmp = x % int(pow(10, digit+1));
    return tmp / pow(10, digit);
}

bool Leet::isPalindromeInt(int x) {
    if (x<0) return false;
    if (x<10) return true;

    int right=0;
    int left=log10(x);
    while (right<left) {
//        cout << right << " " << left << ": ";
        int digitR = getDigit(x, right);
        int digitL = getDigit(x, left);
        if (digitL != digitR)
            return false;
        right++;
        left--;
    }
    return true;
}

bool Leet::isPalindromeInt_2(int x) {
    if (!x)
        return true;
    if (x<0) return isPalindromeInt_2(-x);
    int h = floor(log10(x));
//    cout << floor(log10(x)) << " " << ceil(log10(x)) << endl;
    int l=0;
    while (l<h) {
        int digitH =int(x/pow(10,h)) % 10;
        int digitL =int(x/pow(10,l)) % 10;
        if (digitH != digitL)
            return false;
        l++;
        h--;
    }
    return true;
}

static bool isPalindromeInt_recursive_helper(int x, int &y) {
    if (x<0) return false;
    if (!x) return true;
    if (isPalindromeInt_recursive_helper(x/10, y) && x%10== y%10) {
        y /= 10;
        return true;
    } else
        return false;
}

bool Leet::isPalindromeInt_recursive(int x) {
    return isPalindromeInt_recursive_helper(x, x);
}

string palindromStr_helper(string &s, int left, int right) {
//    string seven;
    while(left>=0 && right<s.size()) {
        if (s[left]!=s[right])
            break;
        else
//            seven = s[left]+seven+s[right];
        left--;
        right++;
    }
    left++;
    right--;
    if (left<=right)
        return s.substr(left, right-left+1);
    else
        return string();
}

string palindromStr(string &s, int i) {
    if (i==0) return s.substr(0,1);
    string seven = palindromStr_helper(s, i-1, i);
    string sodd=palindromStr_helper(s, i-1, i+1);
    return seven.size()>sodd.size() ? seven: sodd;

}

string Leet::findLargestPalindromicSubstr(string s) {
    if (s.size()<=1) return s;

    string res;
    for (int i=1; i<s.size(); i++) {
        string temp = palindromStr(s, i);
        if (temp.size()>res.size())
            res=temp;
    }
    return res;

}

static string getPalindrome(const string &str, int left, int right) {
    while (left>=0 && right<str.size() && str[left]==str[right])
    {
        left--; right++;
    }
    left++;
    right--;
    if (left<=right)
        return str.substr(left, right-left+1);
    else
        return string();
}

static string findLargestPalindromicSubstr_nlogn_merge(const string &str, int m) {
    int left=m-1, right=m+1;
    string odd = getPalindrome(str, left, right);
    left=m; right=m+1;
    string even = getPalindrome(str, left, right);
    return odd.size()>even.size() ? odd : even;
}

static string findLargestPalindromicSubstr_nlogn_helper(const string &str, int s, int e) {
    if (s==e) return str.substr(s,1);

    int m = s + ((e-s)>>1);
    string left = findLargestPalindromicSubstr_nlogn_helper(str, s, m);
    string right = findLargestPalindromicSubstr_nlogn_helper(str, m+1, e);
    string middle = findLargestPalindromicSubstr_nlogn_merge(str, m);
    int maxv=max(left.size(), max(right.size(), middle.size()));
    if (maxv==left.size())
        return left;
    else if (maxv==right.size())
        return right;
    else
        return middle;
}

string Leet::findLargestPalindromicSubstr_nlogn(string s) {
    return findLargestPalindromicSubstr_nlogn_helper(s, 0, s.size()-1);
}

static int findLargestPalindromicSubstr_DP_helper(string &s, int i, int j, vector<vector<int> > &M) {
//    cout <<i << " " << j << endl;
//    for (auto &m : M) {
//        copy(m.begin(), m.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//    }
    if (M[i][j]!=-1)
        return M[i][j];
    if (s[i]==s[j]) {
        if (i+1==j)
            return 2;
        else
            return findLargestPalindromicSubstr_DP_helper(s, i+1, j-1, M)+2;
    }
    else
        return max(findLargestPalindromicSubstr_DP_helper(s, i+1, j, M),
                   findLargestPalindromicSubstr_DP_helper(s, i, j-1, M));
}

int Leet::findLargestPalindromicSubstr_DP(string s) {
    vector<vector<int> > M(s.size(), vector<int>(s.size(), -1));
    for (int i=0; i<s.size(); i++)
        M[i][i]=1;
    return findLargestPalindromicSubstr_DP_helper(s, 0, s.size()-1, M);
}

int Leet::distanceMaximum(const vector<int> &A) {
    if (A.size()<=1)
        throw invalid_argument("there is only one element");

    stack<pair<int, int> > q;
    for (int i=0; i<A.size(); i++) {
        if (q.empty() || q.top().first>A[i]) {
             cout << A[i] << " " << i << endl;
            q.push(pair<int, int>(A[i], i));
        }
    }

    pair<int, int> res(0,0);
    int maxD=0;

    for (int i=A.size()-1; i>=1; i--) {
        while (!q.empty() && A[i]>q.top().first) {
            int dist = i-q.top().second;
            if (dist>maxD) {
                maxD=dist;
                res=pair<int, int>(q.top().second, i);
            }
            q.pop();
        }
    }
     cout << maxD << " " << res.first << " " << res.second << endl;
    return maxD;
}

pair<int, int> Leet::distanceMaximum_better(const vector<int> &A) {
    vector<int> left(A.size(),0), right(A.size(), 0);
    for (int i=0; i<A.size(); i++)
        left[i] = i==0 ? i : A[i]<A[left[i-1]] ? i : left[i-1];
    for (int i=A.size()-1; i>=0; i--)
        right[i] = i==A.size()-1 ? i : A[i]>A[right[i+1]] ? i : right[i+1];
    pair<int, int> ret(-1, -1);
    for (int i=0; i<A.size(); i++)
        if (A[right[i]]>A[left[i]] && right[i]-left[i]>ret.second-ret.first)
            ret=pair<int, int>(left[i], right[i]);
    return ret;
}

static bool compFunc(const pair<int,int> &x, const pair<int, int> &y) {
    return x.first < y.first;
}

int Leet::distanceMaximum_nlogn(const vector<int> &A) {
    if (A.size()<=1)
        throw invalid_argument("there is only one element");
    vector<pair<int, int> > arr;
    for (int i=0; i<A.size(); i++)
        arr.emplace_back(A[i], i);

    sort(arr.begin(), arr.end(), compFunc);

    int maxIndex=0;
    int maxD=0;
    for (int i=arr.size()-1; i>=0; i--) {
        if (arr[i].second>maxIndex)
            maxIndex=arr[i].second;
        if (arr[i].first < A[maxIndex] && maxD < maxIndex-arr[i].second) {
            maxD = maxIndex-arr[i].second;
             cout << "update:" << arr[i].second << " " << maxIndex << " " << maxD << " " << arr[i].first << " " << A[maxIndex] << endl;
        }
    }
     cout << endl;
    return maxD;


}

static int sumA(const vector<int> &A, int from, int to) {
    int sum=0;
    for (int i=from; i<=to; i++)
        sum+=A[i];
    return sum;
}

static int paintersPartition_helper(const vector<int> &A, int n, int k, vector<vector<int> > &table, vector<int> & sumTable) {
//    if (n==0)
//        return 0;
    if (n==1)
        return A[0];
    if (k==1)
        return sumTable[n-1];
    if (table[n][k])
        return table[n][k];

    int best=INT_MAX;
    for (int i=1; i<n; i++) {
        best = min(best, max(paintersPartition_helper(A, i, k-1, table, sumTable), sumTable[n-1]-sumTable[i-1]));
    }
    table[n][k]=best;
    return best;
}

// Best(A, n, k) = min(Best(A, i, k-1), sum(A(i, n))
int Leet::paintersPartition(const vector<int> &A, int k) {
    if (A.empty())
        return 0;
    if (A.size()==1)
        return A[0];
    if (k<0)
        throw invalid_argument("no painter");

    vector<vector<int> > table(A.size()+1, vector<int>(k+1, 0));
    vector<int> sumTable(A.size(), 0);
    sumTable[0]=A[0];
    for (int i=1; i<A.size(); i++)
        sumTable[i] = sumTable[i-1]+A[i];
    return paintersPartition_helper(A, A.size(), k, table, sumTable);

}

static int calcNumPainter(const vector<int> &A, int paintTime) {
    int num=1;
    int sum=0;
    for (int i=0; i<A.size(); i++) {
        sum+=A[i];
        if (sum>paintTime) {
            sum = A[i];
            num++;
        }
    }
    return num;
}

int Leet::paintersPartition_efficient(const vector<int> &A, int k) {
    int lo = *max_element(A.begin(), A.end());
    int hi = std::accumulate(A.begin(), A.end(), 0);

    while (lo<hi) {
        int mid = lo+((hi-lo)>>1);
        int numPainter = calcNumPainter(A, mid);
        if (numPainter<=k)
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

vector<int> Leet::maxSlidingWindow(const vector<int> &A, int w) {
    if (A.size()<w)
        throw invalid_argument("A size is smaller that window size");
    queue<int> q;
    queue<int> seq;

    for (int i=0; i<w ; i++) {
        cout << i << "---" << A[i] << endl;
        seq.push(A[i]);
        if (q.empty()) {
            q.push(A[i]);
            continue;
        }

        while(!q.empty() && A[i]>q.back()) {
            q.pop();
        }
        q.push(A[i]);
    }
    cout << seq.size() << " " << q.size() << endl;

    vector<int> B;
    B.push_back(q.front());
    for (int i=w; i<A.size(); i++) {
        if (seq.front()==q.front()) {
            q.pop();
        }
        seq.pop();
        seq.push(A[i]);

        while(!q.empty() && A[i]>q.back()) {
            q.pop();
        }
        q.push(A[i]);
        B.push_back(q.front());
        cout << i << "->" << q.front() << endl;
    }
    return B;


}

void Leet::insertNodeCyclicList(shared_ptr<LNode> &node, int x) {
    if (!node) {
        node=shared_ptr<LNode>(new LNode(x));
        return;
    }

    shared_ptr<LNode> prev = node;
    shared_ptr<LNode> curr = node->next;
    while (curr) {
        if (x>=prev->data && x<=curr->data) break;
        if (curr->data<prev->data && (x<=curr->data || x>=prev->data)) break;

        prev= curr;
        curr=curr->next;
    }
    shared_ptr<LNode> xnode(new LNode(x));
    prev->next=xnode;
    xnode->next=curr;
}

void Leet::insertNodeCyclicList_2(shared_ptr<LNode> &node, int x) {
    shared_ptr<LNode> newNode(new LNode(x));
    if (!node){
        node = newNode;
    }

    shared_ptr<LNode> curr=node, prev=node;
    while (curr && prev->data<=curr->data) {
        prev=curr;
        curr=curr->next;
    }
    if (x<curr->data && x>prev->data){
        prev->next = newNode;
        newNode->next = curr;
    }

    if (x>node->data) {
        curr=node;
        prev=curr;
    }
    while (curr && curr->data <x) {
        prev=curr;
        curr->next;
    }
    prev->next = newNode;
    newNode->next = curr;
}

void Leet::printNodeCyclicList(shared_ptr<LNode> n) {
    while (n) {
        cout << n->data << " ";
        n=n->next;
    }
    cout << endl;
}

static void reverseBit_helper(unsigned &x, int i, int j) {
    int biti=(x>>i) &1;
    int bitj=(x>>j) &1;
    if (biti ^ bitj) {
        x ^= (1<<i) | (1<<j);
    }
}

int Leet::reverseBit(unsigned x) {
    int n = sizeof(x) * 8;
    for (int i=0; i<n/2; i++) {
        reverseBit_helper(x, i, n-1-i);
    }
    return x;
}

int Leet::reverseBit_logn(unsigned x) {
    x = (x&0x55555555)<<1 | (x&0xAAAAAAAA) >>1;
    x = (x&0x33333333)<<2 | (x&0xCCCCCCCC) >>2;
    x = (x&0x0F0F0F0F)<<4 | (x&0xF0F0F0F0) >>4;
    x = (x&0x00FF00FF)<<8 | (x&0xFF00FF00) >> 8;
    x = (x&0x0000FFFF)<<16| (x&0xFFFF0000) >> 16;
    return x;
}

static int reverseBit_16(unsigned y) {
    unsigned x=y;
    for (int i=0; i<8; i++) {
        reverseBit_helper(x, i, 16-1-i);
    }
    return x;
}

//void Leet::reverseBit(unsigned long long &x) {
//    x = reverseBit_16((x>> 48) & 0xFFFF)
//            | (reverseBit_16((x>>32) & 0xFFFF) << 16)
//            | (reverseBit_16((x>>16) & 0xFFFF) << 32)
//            | (reverseBit_16(x & 0xFFFF) << 48);

//}

string Leet::longestNonRepeatSubstr(string s) {
    if (s.size()<=1) return s;

    string best=s.substr(0,1);
//    string curr=best;
    vector<bool> table(256, false);
    table[s[0]]=true;
    int left=0;
    int i=1;
    for (; i<s.size(); i++) {
        if (!table[s[i]]) {
            table[s[i]]=true;

        } else {
            if (i-left >best.size())
                best=s.substr(left, i-left);

            while (s[left]!=s[i]) {
                table[s[left]]=false;
                left++;
            }
            left++;
        }
    }
    if (i-left >best.size())
        best=s.substr(left, i-left);
    return best;

}

string Leet::longestNonRepeatSubstr2(string s) {
    vector<bool> table(256, false);
    int left=0;
    string ret;
    for (int i=0; i<s.size(); i++) {
        if (table[s[i]]) {
            while (s[left]!=s[i]) {
                table[s[left]]=false;
                left++;
            }
            left++;
        }
        table[s[i]]=true;
        if (ret.size()<i-left+1)
            ret = s.substr(left, i-left+1);
    }
    return ret;
}

shared_ptr<Leet::TNode> Leet::lowestCommonAncestor_BT(shared_ptr<TNode> &root, shared_ptr<TNode> &x,
                                                        shared_ptr<TNode> &y) {
    if (!root || !x || !y)
        return nullptr;
    if (root==x || root==y)
        return root;
    shared_ptr<TNode> left = lowestCommonAncestor_BT(root->left, x, y);
    shared_ptr<TNode> right = lowestCommonAncestor_BT(root->right, x, y);

    if (!left)
        return right;
    else if (!right)
        return left;

        return root;
}

static int getDepth(shared_ptr<Leet::TNode> &x) {
    int d=0;
    while (x) {
        d++;
        x=x->parent;
    }
    return d;
}

shared_ptr<Leet::TNode> Leet::lowestCommonAncestor_BT_parentPointer(shared_ptr<TNode> &x, shared_ptr<TNode> &y) {
    int dx = getDepth(x);
    int dy = getDepth(y);
    if (dy>dx) {
        swap(dx, dy);
        swap(x, y);
    }
    int diff = dx-dy;
    for (int i=0; i<diff; i++)
        x=x->parent;
    while (x && y) {
        if (x==y)
            break;
        x=x->parent;
        y=y->parent;
    }
    return x;
}

shared_ptr<Leet::TNode> Leet::lowestCommonAncestor_BST(shared_ptr<TNode> &root, shared_ptr<TNode> &x, shared_ptr<TNode> &y) {
    if (!root || !x || !y)
        return nullptr;
    if (x->data > root->data && y->data > root->data)
        return lowestCommonAncestor_BST(root->left, x, y);
    else if (x->data < root->data && y->data < root->data)
        return lowestCommonAncestor_BST(root->right, x, y);
    else
        return root;
}

static shared_ptr<Leet::TNode> buildTreeFromInorderPreorder_helper(int in[], int pre[], int size, int offset,
                                                                unordered_map<int, int> &table) {
    if (size==0) return nullptr;
    int i=table[pre[0]]-offset;
    shared_ptr<Leet::TNode> root(new Leet::TNode(pre[0]));
    root->left = buildTreeFromInorderPreorder_helper(in, pre+1, i, offset, table);
    root->right = buildTreeFromInorderPreorder_helper(in+i+1, pre+i+1, size-i-1, offset+i+1, table);
    return root;

}

shared_ptr<Leet::TNode> Leet::buildTreeFromInorderPreorder(int in[], int pre[], int size) {
    unordered_map<int, int> table;
    for (int i=0; i<size; i++) {
        table.emplace(in[i], i);
    }
    return buildTreeFromInorderPreorder_helper(in, pre, size, 0, table);
}

static shared_ptr<Leet::TNode> buildTreeFromInorderPostorder_helper(const vector<int> &in, int in_s, int in_e,
                                                                    const vector<int> &post, int post_s, int post_e,
                                                                    unordered_map<int, int> &table) {
    if (in_s>=in_e || post_s>=post_e)
        return nullptr;

//    auto it = find(in.cbegin()+in_s, in.cbegin()+in_e, post[post_e-1]);
//    auto x = distance(in.cbegin(), it) - in_s;
    int x = table[post[post_e-1]]-in_s;

    shared_ptr<Leet::TNode> root(new Leet::TNode(post[post_e-1]));
    root->left = buildTreeFromInorderPostorder_helper(in, in_s, in_s+x, post, post_s, post_s+x, table);
    root->right = buildTreeFromInorderPostorder_helper(in, in_s+x+1, in_e, post, post_s+x, post_e-1, table);

}

shared_ptr<Leet::TNode> Leet::buildTreeFromInorderPostorder(const vector<int> &in, const vector<int> &post) {
    unordered_map<int, int> table; // that is to reduce find time in in_array
    for (int i=0; i<in.size(); i++)
        table.emplace(in[i], i);
    return buildTreeFromInorderPostorder_helper(in, 0, in.size(), post, 0, post.size(), table);
}

bool Leet::CheckRectangleOverlap(RectangleLeet &a, RectangleLeet &b) {
    return (a.start.x+a.width >= b.start.x || b.start.x+b.width >= a.start.x)
            && (a.start.y+a.height >= b.start.y || b.start.y+b.height >= a.start.y);
}

int Leet::findKsmallestUnion_log(int A[], int m, int B[], int n, int k) {
    int i=((k-1)*m/(m+n));
    int j=k-1-i;

    int Ai_1= i==0?INT_MIN: A[i-1];
    int Bj_1= j==0?INT_MIN: B[j-1];
    int Ai = i==m? INT_MAX: A[i];
    int Bj = j==n? INT_MAX: B[j];
    cout << m << " " << n << " " << i << " " << j << " " << k << endl;

    if (Ai>Bj_1 && Ai<Bj)
        return Ai;
    if (Bj>Ai_1 && Bj<Ai)
        return Bj;

    if (Ai<Bj)
        return findKsmallestUnion_log(A+i+1, m-i-1, B, n, k-i-1);
    else // (Bj<Ai)
        return findKsmallestUnion_log(A, m, B+j+1, n-j-1, k-j-1);

}

static int findKsmallestUnion_log2_helper(vector<int> &A, int a_s, int a_e, vector<int> &B, int b_s, int b_e, int k) {
//    cout <<a_s << " " << a_e << "-" << b_s << " " << b_e << " =" << k << endl;
    if (k<0 || A.empty() || B.empty())
        throw invalid_argument("A, B empty or k<0");
    if (k==0)
        return A[a_s]<B[b_s]?A[a_s] : B[b_s];

    if (a_s>a_e)
        return B[k-1];
    if (b_s>b_e)
        return A[k-1];
    int i = (k-1)*(a_e-a_s+1)/(a_e-a_s+1+b_e-b_s+1);
    int j = k-1-i;
    int ai = a_s +i;
    int bj = b_s+j;
//    cout <<a_s << " " << a_e << "-" << b_s << " " << b_e << " =" << k <<"=====" << i << " " << j << endl;

    int A0 = (ai==0) ? INT_MIN : A[ai-1];
    int B0 = (bj==0) ? INT_MIN : B[bj-1];
    int A1 = (ai==A.size()) ? INT_MAX : A[ai];
    int B1 = bj==B.size() ? INT_MAX : B[bj];

    if (B0<A1 && A1<B1)
        return A1;
    if (A0<B1 && B1<A1)
        return B1;

    if (A1<B1)
        return findKsmallestUnion_log2_helper(A, a_s+i+1, a_e, B, b_s, b_e, k-i-1);
    else
        return findKsmallestUnion_log2_helper(A, a_s, a_e, B, b_s+j+1, b_s, k-j-1);

}

int Leet::findKsmallestUnion_log2(vector<int> &A, vector<int> &B, int k) {
    if (k>A.size()+B.size())
        throw invalid_argument("k is larger than the union size");
    if (A.empty())
        return B[k-1];
    if (B.empty())
        return A[k-1];

    return findKsmallestUnion_log2_helper(A, 0, A.size()-1, B, 0, B.size()-1, k);

}

struct VectorComp {
    bool operator()(const vector<int> &x, const vector<int> &y) {
        return x.back() > y.back();
    }
};

struct PairHashCode2 {
    int operator()(const pair<int, int> &x) const {
        return hash<int>()(x.first) ^ hash<int>()(x.second);
    }
};

struct PairEqual2 {
    bool operator() (const pair<int, int> &x, const pair<int, int> &y) const {
        return x.first==y.first && x.second == x.second;
    }
};

int Leet::findKsmallestSumUnion(vector<int> &A, vector<int> &B, int k) {
    if (A.empty() || B.empty() || k<=0 || k>A.size()*B.size())
        throw invalid_argument("A, B empty or k<0 or k>A.size()*B.size()");
    unordered_set<pair<int,int>, PairHashCode2, PairEqual2 > table;
    priority_queue<vector<int>, vector<vector<int> >, VectorComp> q;
    q.push({0,0, A[0]+B[0]});
    table.emplace(0,0);
    for (int i=0; i<k-1; i++) {
        auto tmp = q.top();
        q.pop();
//        cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << q.size() << endl;
        if (tmp[0]+1<A.size() && table.find(pair<int, int>(tmp[0]+1, tmp[1]))==table.end()) {
//            cout << "push: " << A[tmp[0]+1]+B[tmp[1]] << endl;
            q.push({tmp[0]+1, tmp[1], A[tmp[0]+1]+B[tmp[1]]});
        table.emplace(tmp[0]+1, tmp[1]);
        }
        if (tmp[1]+1 < B.size() && table.find(pair<int, int>(tmp[0], tmp[1]+1))==table.end()) {
//            cout << "push: " << A[tmp[0]]+B[tmp[1]+1] << endl;
            q.push({tmp[0], tmp[1]+1, A[tmp[0]]+B[tmp[1]+1]});
            table.emplace(tmp[0], tmp[1]+1);
        }
    }
    auto x = q.top();
    return x.back();
}

static bool is_number(const string &s) {
    return !s.empty() && s!="+" && s!="-" && s!="*" && s!="/";
}

int Leet::evalReversePolishNotation(const vector<string> &A) {
    stack<int> table;

    for (int i=0; i<A.size(); i++) {
        cout << A[i] << " table " << table.size() << endl;
        if (is_number(A[i])) {
            table.push(stoi(A[i]));
        } else {
            int x=table.top();
            table.pop();
            int y=table.top();
            table.pop();

            if (A[i]=="+")
                table.push(x+y);
            else if (A[i]=="-")
                table.push(y-x);
            else if (A[i]=="*")
                table.push(y*x);
            else if (A[i]=="/")
                table.push(y/x);
            else
                throw invalid_argument("invalid operator");
        }
    }
    return table.top();

}

static int GCD(int x, int y) {
    if (x==0 || y==0) return max(x, y);
    if (x&1==0 && y&1==0)
        return (GCD(x>>1, y>>1))<<1;
    if (x&1==0 && y&1 !=0)
        return GCD(x>>1, y);
    if (x&1!=0 && y&1==0)
        return GCD(x, y>>1);
    else
        return GCD(min(x, y), abs(x-y));
}

struct Line {
    pair<int, int> k, b;
    Line(const PointA &p0, const PointA &p1) {
        int t0=p1.x-p0.x;
        if (t0==0) {
            k= pair<int,int>(1,0);
            b = pair<int, int>(p0.x, 0);
            return;
        }
        int t1=p1.y-p0.y;
        int t2=p0.y*p1.x-p1.y*p0.x;
        int gcd0=GCD(t0, t1);
        int gcd1=GCD(t2, t0);
        k = t0<0 ? pair<int, int>(-t1/gcd0, -t0/gcd0) : pair<int, int>(t1/gcd0, t0/gcd0);
        b = t0<0 ? pair<int, int>(-t2/gcd1, -t0/gcd1) : pair<int, int>(t2/gcd1, t0/gcd1);
    }
    bool operator==(const Line &l1) const {
        return k==l1.k && b==l1.b;
    }
};

struct LineHash {
    int operator()(const Line & l0) const {
        return hash<int>()(l0.k.first) ^ hash<int>()(l0.k.second) ^ hash<int>()(l0.b.first) ^ hash<int>()(l0.b.second);
    }
};

struct PointHash {
    int operator()(const PointA &x) const {
        return hash<int>()(x.x) ^ hash<int>()(x.y);
    }
};

static bool Comp(const pair<Line, unordered_set<PointA, PointHash> > & x, const pair<Line, unordered_set<PointA, PointHash> > &y) {
    return x.second.size() < y.second.size();
}


int Leet::maxPointsInLine(const vector<PointA> &A) {
    if (A.size()<=1)
        throw invalid_argument("the vector size is less than 2");
    unordered_map<Line, unordered_set<PointA, PointHash>, LineHash> table;

    for (int i=0; i<A.size()-1; i++)
        for (int j=i+1; j<A.size(); j++)
        {
            Line x(A[i], A[j]);
            table[x].emplace(A[i]);
            table[x].emplace(A[j]);
        }
    auto itr = max_element(table.begin(), table.end(), Comp);
    return itr->second.size();
}

int Leet::maxPointsInLine_efficient(const vector<PointA> &A) {
    int res=0;
    for (int i=0;i<A.size()-1; i++) {
        int maxNum=1;
        unordered_map<double, int> table;
        int duplicates=1;
        for (int j=i+1; j<A.size(); j++) {
            if (A[i].x==A[j].x && A[i].y==A[j].y) {
                duplicates++;
                continue;
            }
            double slope = numeric_limits<double>::infinity();
            if (A[i].x!=A[j].x) {
                slope=fabs(double(A[i].y-A[j].y)/(A[i].x-A[j].x));
            }

            if (table.find(slope)==table.end())
                table[slope]=2;
            else
                table[slope]++;
            if (table[slope]>maxNum)
                maxNum=table[slope];
        }
        if (duplicates+maxNum>res)
            res=duplicates+maxNum;

    }
    return res;
}

static void splitList(Leet::lnode *head, Leet::lnode**a, Leet::lnode **b) {
    if (!head || !head->next) {
        *a=head;
        *b=nullptr;
    }
    Leet::lnode *slow=head, *fast=head;

    while (fast!=nullptr) {
        fast=fast->next;
        if (fast!=nullptr) {
            fast=fast->next;
            slow=slow->next;
        }
    }
    *a=head;
    *b=slow->next;
    slow->next=nullptr;
}

static Leet::lnode * mergeList(Leet::lnode *a, Leet::lnode *b) {
    if (!a) return b;
    if (!b) return a;

    Leet::lnode * res=nullptr;
    if (a->data <= b->data) {
        res=a;
        res->next=mergeList(a->next, b);
    } else {
        res=b;
        res->next=mergeList(a, b->next);
    }

    return res;
}

void Leet::sortList_nlogn(lnode **head) {
    Leet::lnode *ref = *head;
    if (!ref || !ref->next)
        return;

    lnode * a, *b;

    splitList(*head, &a, &b);
    sortList_nlogn(&a);
    sortList_nlogn(&b);

    *head=mergeList(a, b);
}

static void merge_helper(shared_ptr<Leet::LNode> & head, shared_ptr<Leet::LNode> & tail, shared_ptr<Leet::LNode> &node) {
    head?tail->next=node : head=node;
    tail=node;
    node=node->next;
}

static shared_ptr<Leet::LNode> mergeList2(shared_ptr<Leet::LNode> & h1, shared_ptr<Leet::LNode> & h2) {
    shared_ptr<Leet::LNode> head=nullptr, tail=nullptr;
    while(h1 && h2) {
        merge_helper(head, tail, h1->data<h2->data? h1 : h2);
    }
    if (h1)
        tail->next = h1;
    if (h2)
        tail->next = h2;
    return head;
}

void Leet::sortList(shared_ptr<LNode> &head) {
    if (!head || !head->next)
        return;
    shared_ptr<LNode> slow=head, fast=head;
    while (fast) {
        fast=fast->next;
        if (fast) {
            fast=fast->next;
            slow=slow->next;
        }
    }
    shared_ptr<LNode> mid;
    if (head->next==slow) {
        mid=slow;
        head->next=nullptr;
    } else {
        mid=slow->next;
        slow->next=nullptr;
    }
    sortList(head);
    sortList(mid);
    head = mergeList2(head, mid);
}

int Leet::candyproblem(const vector<int> &A) {
    vector<int> candys(A.size(), 1);
    for (int i=1; i<A.size(); i++)
    {
        if (A[i]>A[i-1])
            candys[i]=candys[i-1]+1;
    }
    for (int i=A.size()-2; i>=0; i--) {
        if (A[i]>A[i+1] && candys[i]<=candys[i+1])
            candys[i]=candys[i+1]+1;
    }
    return accumulate(candys.begin(), candys.end(), 0);
}

void Leet::LRUCache::moveFront(int key) {
    seq.erase(table[key].first);
    seq.push_front(key);
    table[key].first=seq.begin();
}

int Leet::LRUCache::get(int key) {
    if (table.find(key)==table.end())
        return -1;
    moveFront(key);
    return table[key].second;
}

void Leet::LRUCache::set(int key, int value) {
    if (table.find(key) != table.end()) {
        moveFront(key);
        return;
    }

    if (table.size()==capacity) {
        table.erase(seq.back());
        seq.pop_back();

    }
        seq.push_front(key);
        table[key]={seq.begin(), value};
}

vector<string> Leet::grayCode(int n) {
    if (n<=0)
        throw invalid_argument("input is zero or less than zero");
    vector<string> ret;
    ret.push_back(string());

    for (int i=0;i<n; i++) {
        auto clone = ret;
        reverse(clone.begin(), clone.end());
        for (int k=0; k<ret.size(); k++)
            ret[k].push_back('0');
        for (int k=0; k<clone.size(); k++)
            clone[k].push_back('1');
        ret.insert(ret.end(), clone.begin(), clone.end());
    }
    copy(ret.begin(), ret.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    return ret;


//    if (n==1) {
//        vector<string>res;
//        res.push_back("0");
//        res.push_back("1");
//        return res;
//    }

//    vector<string> code = grayCode(n-1);
//    vector<string> reverseCode = code;
//    for (int i=0; i<reverseCode.size()/2; i++)
//        swap(reverseCode[i], reverseCode[code.size()-1-i]);

//    for (auto &x : code)
//      x = "0"+x;
//    for (auto &x : reverseCode)
//      x ="1"+x;

//    code.insert(code.end(), reverseCode.begin(), reverseCode.end());
//    return code;
}

static void triangle_helper(vector<vector<int> > &A, int y, int x, int sum, int &minV) {
    sum += A[y][x];

    if (y==A.size()-1) {
        minV=min(sum, minV);
        return;
    }

    triangle_helper(A, y+1, x, sum, minV);
    if (x-1>=0)
        triangle_helper(A, y+1, x-1, sum, minV);
    if (x+1<A[y+1].size())
        triangle_helper(A, y+1, x+1, sum, minV);
}

/**
 * @brief Leet::triangle
 * using DFS is better coding:
 * @param A
 * @return
 */
int Leet::triangle(vector<vector<int> > &A) {
    int minV = INT_MAX;
    triangle_helper(A, 0, 0, 0, minV);
    return minV;
//    if (A.empty() || A[0].empty())
//        throw invalid_argument("empty array");
//    auto D=A;
//    for (int i=1; i<D.size(); i++) {
//        for (int j=0; j<D[i].size(); j++) {
//            int m=INT_MAX;
//            if (j>=0 && j<D[i-1].size())
//                m=D[i-1][j];
//            if (j-1>=0)
//                m = min(m, D[i-1][j-1]);
//            if (j+1<D[i-1].size())
//                m=min(m, D[i-1][j+1]);
//            D[i][j]=A[i][j]+m;
//        }
//    }
//    int i=A.size()-1;
//    int ret=INT_MAX;
//    for (int j=0; j<A[i].size(); j++)
//        ret=min(ret, D[i][j]);
//    return ret;
}

void Leet::pascalTriangle(int n) {
    if (!n) return;
    vector<int> table(n, 0);
    table[0]=1;
    for (int i=1; i<n; i++) {
        for (int j=i; j>=0; j--)
            table[j]=(j-1<0 ? 0: table[j-1])+table[j];
    }
    copy(table.begin(), table.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
//    return table;

    // get all rows
//    if (!n) return ;
//    vector<vector<int> > D(n);
//    for (int i=0; i<n; i++)
//        D[i]=vector<int>(i+1, 0);

//    D[0][0]=1;
//    cout << D[0][0] << endl;
//    for (int i=1; i<n; i++) {
//        for (int j=0; j<D[i].size(); j++) {
//            D[i][j]=(j-1>=0 ? D[i-1][j-1]:0) + (j<D[i-1].size()?D[i-1][j]:0);
//        }
//        copy(D[i].begin(), D[i].end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//    }
}

static void swapTreeNode(shared_ptr<Leet::TNode> &big, shared_ptr<Leet::TNode> &small) {
    int temp=big->data;
    big->data = small->data;
    small->data = temp;
}

static shared_ptr<Leet::TNode> recoverBST_helper(shared_ptr<Leet::TNode> & root,
                                                 bool leftFirst, int minV, int maxV) {
    if (!root) return nullptr;
    if (root->data > maxV || root->data < minV)
        return root;
    if (leftFirst) {
        shared_ptr<Leet::TNode> left = recoverBST_helper(root->left, leftFirst, minV, root->data);
        if (left)
            return left;
        shared_ptr<Leet::TNode> right = recoverBST_helper(root->right, leftFirst, root->data, maxV);
        if (right)
            return right;
    }
    else {
        shared_ptr<Leet::TNode> right = recoverBST_helper(root->right, !leftFirst, root->data, maxV);
        if (right)
            return right;
        shared_ptr<Leet::TNode> left = recoverBST_helper(root->left, !leftFirst, minV, root->data);
        if (left)
            return left;
    }
}

void Leet::recoverBST(shared_ptr<TNode> &root) {
    if (!root) return;

    shared_ptr<TNode> big = recoverBST_helper(root, true, INT_MIN, INT_MAX);
    cout << "big=" << big->data << endl;
    shared_ptr<TNode> small = recoverBST_helper(root, false, INT_MIN, INT_MAX);
    cout << "small=" << small->data << endl;
    swapTreeNode(big, small);
}

void Leet::recoverBST_constSpace(shared_ptr<TNode> &root) {
    auto curr=root;
    shared_ptr<TNode> prev(new TNode(INT_MIN));
    vector<shared_ptr<TNode> > errorNode;
    while (curr) {
        if (curr->left) {
            auto tmp = curr->left;
            while (tmp->right && tmp->right !=curr )
                tmp=tmp->right;
            if (tmp->right==curr) {
                tmp->right=nullptr;
                if (curr->data < prev->data) {
                    errorNode.push_back(prev);
                    errorNode.push_back(curr);
                }
                cout << curr->data << " ";
                curr=curr->right;
            } else {
                tmp->right = curr;
                curr=curr->left;
            }
        } else {
            if (curr->data < prev->data){
                errorNode.push_back(prev);
                errorNode.push_back(curr);
            }
            cout << curr->data << " ";
            curr=curr->right;
        }
    }
    if (errorNode.size()==2)
        swap(errorNode[0]->data, errorNode[1]->data);
    else if (errorNode.size()==4)
        swap(errorNode[0]->data, errorNode[3]->data);
    return;
}

static void recoverBST_efficient_helper(shared_ptr<Leet::TNode> &curr, shared_ptr<Leet::TNode> & prev, shared_ptr<Leet::TNode> &first, shared_ptr<Leet::TNode> &second) {
    if (!curr)return;
    recoverBST_efficient_helper(curr->left, curr, first, second);
    if (curr->data<prev->data) {
        if (!first)
            first = prev;
        else {
            second = curr;
            return;
        }
    }
    recoverBST_efficient_helper(curr->right, curr, first, second);
}

// observation: inorder visit, find curr>prev, and first mistake is prev, and second mistake is curr;
void Leet::recoverBST_efficient(shared_ptr<TNode> &root) {
    if (!root) return;
    shared_ptr<TNode> first=nullptr, second=nullptr, prev=nullptr;
    recoverBST_efficient_helper(root, prev, first, second);
    int tmp = first->data;
    first->data=second->data;
    second->data = tmp;
}

bool interleavingString_helper(string s1, int i, string s2, int j, string s3, int k, vector<vector<bool> > &table) {
    if (k==s3.size())return true;
    if (table[i][j]==false)
        return false;

    if (i<s1.size() && s1[i]==s3[k] && interleavingString_helper(s1, i+1, s2, j, s3, k+1, table))
        return true;
    if (j<s2.size() && s2[j]==s3[k] && interleavingString_helper(s1, i, s2, j+1, s3, k+1, table))
        return true;
    table[i][j]=false;
    return false;
}

bool Leet::interleavingString(string s1, string s2, string s3) {
    if (s3.size()!=s1.size()+s2.size())return false;
    vector<vector<bool> > table(s1.size()+1, vector<bool>(s2.size()+1, true));
    return interleavingString_helper(s1, 0, s2, 0, s3, 0, table);
}

shared_ptr<Leet::TNode> Leet::arrToTree(const vector<int> &A, int left, int right) {
    if (left>right)
        return nullptr;
    int mid=left+((right-left)>>1);
    cout << "mid=" << A[mid] << endl;
    return shared_ptr<TNode>(new TNode(A[mid], arrToTree(A, left, mid-1), arrToTree(A, mid+1, right)));
}

vector<int> Leet::treeToArr(shared_ptr<TNode> &root) {
    vector<int> res;
    if (!root) return res;
    if (root->left) {
        vector<int> lefttree = treeToArr(root->left);
        res.insert(res.begin(), lefttree.begin(), lefttree.end());
    }
    res.push_back(root->data);
    cout << "root=" << root->data << endl;
    if (root->right){
        vector<int> righttree = treeToArr(root->right);
        res.insert(res.end(), righttree.begin(), righttree.end());
    }
    return res;
}

shared_ptr<Leet::TNode> Leet::deserializeToTree(const vector<string> &A) {
    if (A.empty()) return nullptr;
    queue<shared_ptr<Leet::TNode> > q;
    shared_ptr<Leet::TNode> root=shared_ptr<Leet::TNode>(new Leet::TNode(stoi(A[0])));
    q.push(root);
    int index=1;

    while (!q.empty() ) {
        shared_ptr<Leet::TNode> node = q.front();
        q.pop();
        if (index<A.size() && A[index++]!="#") {
            node->left = shared_ptr<Leet::TNode>(new Leet::TNode(stoi(A[index])));
            q.push(node->left);
        }
        if (index<A.size()&& A[index++]!="#") {
            node->right = shared_ptr<Leet::TNode>(new Leet::TNode(stoi(A[index])));
            q.push(node->right);
        }
    }
    return root;
}

static shared_ptr<Leet::TNode> deserializeToTree_recursive_helper(const vector<string> &A, int idx) {
    if (A[idx]=="#") {
        return nullptr;
    }
    shared_ptr<Leet::TNode> n(new Leet::TNode(stoi(A[idx])));
    n->left = deserializeToTree_recursive_helper(A, idx*2+1);
    n->right = deserializeToTree_recursive_helper(A, idx*2+2);
    return n;
}

// this is only work for complete tree;
shared_ptr<Leet::TNode> Leet::deserializeToTree_recursive(const vector<string> &A) {
    if (A.empty()) return nullptr;
    return deserializeToTree_recursive_helper(A, 0);
}


void Leet::sortColor_onepass_constSpace(vector<int> &A, int pivot) {
    int left=0, mid=0;
    int right=A.size()-1;

    while (mid<right) {
        if (A[mid]==pivot)
            mid++;
        else if (A[mid]<pivot) {
            swap(A[left], A[mid]);
            left++;
            mid++;
        } else {
            swap(A[right], A[mid]);
            right--;
//            mid++;
        }
    }

}

int Leet::getKth(vector<int> &A, int aleft, int aright, vector<int> &B, int bleft, int bright, int k) {
    printf("%d, %d, %d, %d, %d\n", k, aleft, aright, bleft, bright);
    if (k>A.size()+B.size() || k<0 )
        throw invalid_argument("k is too larger or negative or A/B is out of range ");
    if (aleft>aright)
        return B[k+bleft-1];
    else if (bleft>bright)
        return A[k+aleft-1];
    else if (k==0)
        return A[aleft]<B[bleft] ? A[aleft]:B[bleft];

    int alen=aright-aleft+1;
    int blen=bright-bleft+1;
    int i=(k-1)*alen/(alen+blen);
    int j=k-i-1;
    cout << i << " j=" << j << endl;
    int Ai0 = i==0? INT_MIN:A[i-1+aleft];
    int Ai = i==alen? INT_MAX : A[i+aleft];
    int Bj0 = j==0? INT_MIN:B[j-1+bleft];
    int Bj = j==blen? INT_MAX : B[j+bleft];
//    printf("AB:%d, %d, %d, %d\n", Ai0, Ai, Bj0, Bj);
    if (Bj0<Ai && Ai<Bj) {
            return Ai;
    }
    else if (Ai0<Bj && Bj<Ai) {
            return Bj;
    }
    cout << Ai << ",," << Bj << endl;
    if (Ai<Bj) {
        return getKth(A, aleft+i+1, aright, B, bleft, bright, k-i-1);
    }
    else {
        return getKth(A, aleft, aright, B, bleft+j+1, bright, k-j-1);
    }

}

double medianSortedArr(vector<int> &A) {
    if (A.size() & 1)
        return A[(A.size()+1)>>1];
    else {
        return double(A[(A.size()+1)>>1]+A[((A.size()+1)>>1)+1])/2;
    }
}

double Leet::medianSortedArrayUnion(vector<int> &A, vector<int> &B) {
//    if (A.empty())
//        return medianSortedArr(B);
//    else if (B.empty())
//        return medianSortedArr(A);

    int total=A.size()+B.size();
    int x = findKsmallestUnion_log2(A, B, (total)>>1);
    int y = getKth(A, 0, A.size()-1, B, 0, B.size()-1, (total+1)>>1);
    cout << "x=" << x << " y=" <<y << endl;
    if (total & 1 )
        return x;
    else {
//        return double(x+getKth(A, 0, A.size()-1, B, 0, B.size()-1, (total>>1)-1))/2;
        return double(x+findKsmallestUnion_log2(A, B, ((total)>>1)-1))/2;
    }

}

string Leet::zigzagConvert(string &s, int nrow) {
    int ncol=s.length()*2/nrow;
//    cout << nrow << " " << ncol << endl;
    vector<vector<char> > A(nrow, vector<char>(ncol, ' '));

//    int index=0;
    for (int j=0, index=0; j<ncol && index<s.length(); j++) {
        if (j%(nrow-1)==0) {
            for (int i=0; i<nrow; i++) {
//                cout << i << " " << j << " " << s[index]<< endl;
                A[i][j]=s[index++];
            }
        } else {
//            cout << j << endl;
//                cout << nrow-1-j%(nrow-1) << " " << j << " " << s[index]<< endl;
            A[nrow-1-j%(nrow-1)][j]=s[index++];
        }
    }

    string res;
//    cout << "res =" << endl;
    for (int i=0; i<nrow; i++)
        for (int j=0; j<ncol; j++){
//            cout << i << " " << j << " " << A[i][j] << endl;
            if (A[i][j] != ' ')
                res.push_back(A[i][j]);
        }
    return res;
}

vector<vector<char> > Leet::zigzagConrversion2(string s, int nrow) {
    int i=0, idx=0, spaceNum=0;
    string tmp;
    while (i<s.size()) {
        if (spaceNum==0) {
            tmp.append(s.substr(i, nrow));
            i+=nrow;
            spaceNum=nrow-2;
        } else {
            tmp.append(string(spaceNum,' '));
            tmp.push_back(s[i++]);
            tmp.append(string(nrow-spaceNum-1, ' '));
            spaceNum--;
        }
    }
    int ncol=max(1, (int)tmp.size()/nrow);
    vector<vector<char> > ret(nrow, vector<char>(ncol, ' '));
    idx=0;
    for (int i=0;i<ncol; i++)
        for (int j=0; j<nrow; j++) {
            ret[j][i]=tmp[idx++];
        }
    for (auto &t : ret) {
        copy(t.begin(), t.end(), ostream_iterator<char>(cout, " "));
        cout << endl;
    }
    return ret;
}

int Leet::findLargestContainer(vector<int> &heights) {
    if (heights.size()<2)
        throw invalid_argument("less than 2 lines");

    vector<pair<int, int> > lefts;
    lefts.emplace_back(0, heights[0]);
    int maxV=INT_MIN;
    for (int i=1; i<heights.size(); i++) {
        for (auto & t : lefts) {
            int area = (i-t.first) * min(heights[i], t.second);
            maxV = max(area, maxV);

            if (heights[i]>lefts.back().second)
                lefts.emplace_back(i, heights[i]);
        }
    }
    return maxV;
}

int Leet::findLargestContainer_N(vector<int> &heights) {
    int maxV=INT_MIN;
    int left=0, right=heights.size()-1;

    while (left <right) {
        maxV = max(maxV, (right-left)*min(heights[left], heights[right]));
        if (heights[left] < heights[right])
            left++;
        else
            right--;
    }
    return maxV;
}

class TrieNode {
    char c;
    int count;
    unordered_map<char, shared_ptr<TrieNode> > children;
public:
    TrieNode(char _c) : c(_c), count(1) {}
    void insert(string s) {
        if (s.empty()) return;
        auto it = children.find(s[0]);
        if ( it== children.end()) {
            children.emplace(s[0], shared_ptr<TrieNode>(new TrieNode(s[0])));
            it = children.find(s[0]);
        } else
            it->second->count++;
        it->second->insert(s.substr(1));
    }

    string comPrefix(int _count) {
        string res;
        if (count >= _count && children.size()==1) {
            char t = c;
            res.push_back(t);
            res += children.begin()->second->comPrefix(_count);
        }
        return res;
    }

};

class LTrie {
    shared_ptr<TrieNode> root;

public:
    void insert(string &s) {
        root->insert(s);
    }

    string comPrefix(int count) {
        return root->comPrefix(count);
    }
};

string Leet::commonPrefix(vector<string> &S) {
    if (S.empty()) return string();
    string res = S[0];
    for (auto &x : S) {
        for (int i=0; i<res.size() && i<x.size(); i++) {
            if (res[i]!=x[i]) {
                res = res.substr(0, i);
                break;
            }
        }
    }
    return res;
}

struct PairHashCode {
    int operator()(const pair<int, int> &x) const {
        return hash<int>()(x.first) ^ hash<int>()(x.second);
    }
};

struct PairEqual {
    bool operator()(const pair<int,int> &x, const pair<int, int> &y) const {
        return x.first==y.first && x.second==y.second;
    }
};

struct VectorHashCode {
    int operator()(const vector<int> &x) const {
        int code=0;
        for (auto &t: x)
            code ^= hash<int>()(t);
        return code;
    }
};

struct VectorEqual {
    bool operator()(const vector<int> &x, const vector<int> &y) const {
        if (x.size() !=y.size()) return false;
        for (int i=0; i<x.size(); i++)
        {
            if (x[i]!=y[i])
                return false;
        }
        return true;
    }
};

unordered_set<pair<int, int>, PairHashCode, PairEqual > twoSum(vector<int> &A, int left, int right, int k) {
    unordered_set<pair<int, int>, PairHashCode, PairEqual > res;
    while (left < right) {
        if (A[left]+A[right]==k) {
            res.emplace(A[left], A[right]);
            left++;
            right--;
        }
        else if (A[left]+A[right]<k)
            left++;
        else
            right--;
    }
    return res;
}

void Leet::threeSum(vector<int> &A) {
    sort(A.begin(), A.end());
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    unordered_set<vector<int>, VectorHashCode, VectorEqual > res;
    for (int i=0; i<=A.size()-3; i++) {
//        cout << i << ":" << A[i] << endl;
        unordered_set<pair<int, int>, PairHashCode, PairEqual > t = twoSum(A, i+1, A.size()-1, -A[i]);
        if (!t.empty()) {
            for (auto &y : t) {
                vector<int> x;
                x.emplace_back(A[i]);
                x.emplace_back(y.first);
                x.emplace_back(y.second);
                res.emplace(x);
            }
        }
    }
    for (auto &x:res) {
        copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}

void Leet::phoneNumberRepresentation(int digit, string & res) {
    if (digit==0) {
        string x=res;
        reverse(x.begin(), x.end());
        cout << x << endl;
        return;
    }
    vector<string> table;
    table.emplace_back(" ");
    table.emplace_back("*");
    table.emplace_back("abc");
    table.emplace_back("def");
    table.emplace_back("ghi");
    table.emplace_back("jkl");
    table.emplace_back("mno");
    table.emplace_back("pqrs");
    table.emplace_back("tuv");
    table.emplace_back("wxyz");

    int x = digit % 10;
//    cout << "digit=" << digit << "x=" << x << endl;
    for (int i=0; i<table[x].size(); i++) {
        res.push_back(table[x][i]);
        phoneNumberRepresentation(digit/10, res);
        res.pop_back();
    }

}

shared_ptr<Leet::LNode> Leet::buildList(vector<int> &A) {
    if (A.empty())
        return nullptr;
    shared_ptr<LNode> head(new LNode(A[0]));
    shared_ptr<LNode> curr=head;
    for (int i=1; i<A.size(); i++) {
        curr->next=shared_ptr<LNode>(new LNode(A[i]));
        curr=curr->next;
    }
    return head;
}

void Leet::printList(shared_ptr<LNode> head) {
    shared_ptr<LNode> curr=head;
    while (curr) {
        cout << curr->data << " ";
        curr= curr->next;
    }
    cout << endl;
}

shared_ptr<Leet::LNode> Leet::reverseList_recursive(shared_ptr<Leet::LNode> & head) {
    if (!head || !head->next)
        return head;
    shared_ptr<Leet::LNode> node = reverseList_recursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return node;
}

shared_ptr<Leet::LNode> Leet::reverseList_iterative(shared_ptr<Leet::LNode> & head) {
    if (!head || !head->next)
        return head;
    shared_ptr<Leet::LNode> curr=head, prev=nullptr;
    while (curr) {
        shared_ptr<LNode> temp = curr->next;
        curr->next = prev;
        prev=curr;
        curr=temp;
    }
    return prev;
}

shared_ptr<Leet::LNode> Leet::reverseList_kgroup(shared_ptr<LNode> &head, int k) {
    if (k<0)
        throw invalid_argument("k is negative");
    if (k==1 || !head || !head->next)
        return head;

    shared_ptr<LNode>curr=head, next=nullptr;
    int i=0;
    for (; i<k-1 && curr; i++) {
        curr=curr->next;
    }
    if (!curr)
        return head;

    next = curr->next;
    curr->next=nullptr;

    shared_ptr<LNode> newhead = reverseList_iterative(head);
    shared_ptr<LNode> tail = newhead;
    while (tail->next)
        tail=tail->next;
    tail->next=reverseList_kgroup(next, k);

    return newhead;
}

int Leet::strStr(string stack, string needle) {
    if (stack.empty() || needle.empty() || stack.size()<needle.size())
        return -1;
    int kBase=26, kMod=997;

    int needlecode=0, scode=0;
    int power2=1;
    for (int i=0; i<needle.size(); i++) {
        needlecode = (needlecode*kBase+needle[i]) % kMod;
        scode = (scode*kBase+stack[i]) % kMod;
        power2 = i ? (kBase *power2) % kMod : 1;
    }
    for (int i=needle.size(); i<stack.size(); i++) {
        if (needlecode==scode && !stack.compare(i-needle.size(), needle.size(), needle))
            return i-needle.size();
        scode -= (power2 * stack[i-needle.size()]) %kMod;
        if (scode < 0)
            scode += kMod;
        scode = (scode * kBase + stack[i] ) % kMod;
    }

    if (needlecode==scode && !stack.compare(stack.size()-needle.size(), needle.size(), needle))
        return stack.size()-needle.size();
    return -1;
}

// it could use only unordered_map<string>table, and every time find match and erase it from table
static bool match(string &s, unordered_map<string, bool> table) {
    int slen=table.begin()->first.length();
//    int nmatch=0;
    for (int i=0; i<s.size(); i+=slen) {
        string x=s.substr(i, slen);
        auto it = table.find(x);
        if (it == table.end())
            return false;

        if (it->second)
            return false;
        else {
            it->second=true;
//            nmatch++;
        }
    }
//    cout << s.length() << " " << nmatch << " " << table.size() << endl;
    return true;
}

vector<int> Leet::substringWithAllWords(string s, vector<string> &dict) {
    if (dict.empty() || s.empty())
        throw invalid_argument("empty string or dict");
    unordered_map<string, bool> table;
    for (auto & x : dict) {
        table.emplace(x, false);
    }
    int len=dict.size()*dict[0].length();

    vector<int> res;
    for (int i=0; i<s.size(); i++) {
        string x = s.substr(i, len);
        if (x.length()<len)
            break;
        if (match(x, table))
            res.push_back(i);
    }
    return res;
}

vector<int> Leet::substringWithAllWords_efficient(string s, vector<string> &D) {
    vector<int> ret;
    if (s.empty() || D.empty() || s.size()<D.size()*D[0].size())
        return ret;
    list<pair<int, string> > L;
    unordered_map<string, list<pair<int, string> >::iterator > M;

    for (auto d: D)
        M[d]=L.end();

    for (int i=0; i<s.size(); i++) {
        string t=s.substr(i, D[0].size());
        cout << t << endl;
        if (M.find(t)==M.end())
            continue;

        if (M[t]==L.end()) {
            if (!L.empty() && L.back().first!=i-1) {
                L.clear();
                for (auto d: D)
                    M[d]=L.end();
            }
        } else {
            int k=M[t]->first;
            while (!L.empty() && L.front().first!=k) {
                M[L.front().second]=L.end();
                L.pop_front();
            }
            L.pop_front();
        }
        L.emplace_back(pair<int, string>(i, t));
        M[t]=--L.end();

        if (L.size()==M.size())
            ret.emplace_back(L.front().first);
    }
    return ret;
}

pair<int, int> Leet::minCoverage_stream(vector<string> & s, vector<string> &dict) {
    list<int> loc;
    unordered_map<string, list<int>::iterator > table;
    for (auto & x : dict) {
        table[x]=loc.end();
    }

    int index=0;
    pair<int, int> res{-1, -1};
    while (index<s.size()) {
        auto it = table.find(s[index]);
        if (it != table.end()) {
            if (it->second != loc.end()) {
                loc.erase((it->second));
            }
                loc.push_back(index);
                it->second = --loc.end();
        }
        if (loc.size() == table.size()) {
            if (res==pair<int, int>(-1, -1) || index-loc.front() < res.second-res.first)
                res = pair<int, int>(loc.front(), index);
        }

        index++;
    }
    return res;

}

string Leet::longestValidParentheses(string s) {
    cout << s << endl;
    stack<char> q;
    pair<int, int> res(-1, -1);
    int left=0;
    for (int i=0; i<s.size(); i++) {
        if (s[i]=='('){
            q.push(s[i]);
        } else if (s[i]==')') {
            if (!q.empty() && q.top()=='(') {
                q.pop();
                if (res==pair<int, int>(-1, -1) || res.second-res.first < i-left)
                    res=pair<int, int>(left, i);
            } else {
                left=i+1;
            }

        }
    }
    return s.substr(res.first, res.second-res.first+1);
}

int Leet::longestValidParentheses2(string s) {
    int curr=0, ret=0, cont=0;
    for (auto &c: s) {
        if (c=='(')
            curr++;
        else {
            curr--;
            if (curr<0) {
                ret=max(ret, cont);
                cont=0;
                curr=0;
            } else
                cont+=2;
        }
    }
    ret=max(cont, ret);
    return ret;
}

int Leet::longestValidParentheses3_better(string A) {
    int curr=0, ret=0, prev=0;
    for (int i=0; i<A.size(); i++) {
        char a=A[i];
        if ( a!= '(' && a!= ')')
            throw invalid_argument("invalid string");
        if (a=='(') {
            curr++;
            prev=i;
        }
        else {
            if (prev>=0 && A[prev]=='(') {
                curr++;
                prev--;
                ret = max(ret, curr);
            } else {
                curr=0;
            }
        }
    }
    return ret;
}

void Leet::permuteArr(vector<int> &perm, vector<int> &A) {
    for (int i=0; i<A.size(); i++) {
        if (perm[i]>=0) {
            int a = i;
            int temp = A[i];
            do {
                int next_a= perm[a];
                int next_temp=A[next_a];
                A[next_a]=temp;
                perm[a] -= perm.size();
                a=next_a;
                temp=next_temp;
//                copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//                cout << endl;
            } while (a != i);
        }
    }

    int size=perm.size();
    for_each(perm.begin(), perm.end(), [size](int &x){ x+=size;});

}

void reverseArr(vector<int> &A, int left, int right) {
    while(left<right) {
        swap(A[left], A[right]);
        left++;
        right--;
    }
}

void Leet::nextPermutation(vector<int> &A) {
    if (A.size()<2)
        return;
    int i=A.size()-2;
    for (; i>=0; i--) {
        if (A[i]<A[i+1])
            break;
    }
    if (i<0) {
        reverse(A.begin(), A.end());
//        reverseArr(A, 0, A.size()-1);
        return;
    }
    int j=A.size()-1;
    for (; j>i; j--)
        if (A[j]>A[i])
            break;
    swap(A[i], A[j]);
    reverse(A.begin()+i+1, A.end());
//    reverseArr(A, i+1, A.size()-1);
}

int findRangeofValue_helper(const vector<int> &A,int k, bool moveLeft) {
    int left=0, right=A.size()-1;
    int res=-1;
    while(left<=right) {
        int mid = left + ((right-left)>>1);
        if (A[mid]<k)
            left=mid+1;
        else if (A[mid]>k)
            right=mid-1;
        else {
            res=mid;
            if (moveLeft)
                right=mid-1;
            else
                left=mid+1;
        }

    }
    return res;
}

pair<int, int> Leet::findRangeofValue(const vector<int> &A, int k) {
    int left = findRangeofValue_helper(A, k, true);
    int right = findRangeofValue_helper(A, k, false);
    return pair<int, int>(left, right);
}

bool isValide09(int x, vector<int> & table) {
    if (x<0 || x>9)
        return false;
    if (x==0)
        return true;
    if (table[x])
        return false;
    else {
        table[x]=1;
        return true;
    }

}

bool Leet::validateSudoku(vector<vector<int> > &A){
    vector<int> table(A.size()+1, 0);
    for (int i=0; i<A.size(); i++) {
        table=vector<int>(A.size()+1, 0);
        for (int j=0; j<A.front().size(); j++) {
            if (!isValide09(A[i][j], table)) {
                return false;
            }
        }
    }
    for (int i=0; i<A.front().size(); i++) {
        table=vector<int>(A.size()+1, 0);
        for (int j=0; j<A.size(); j++) {
            if (!isValide09(A[j][i], table))
                return false;
        }
    }
    int size = sqrt(A.size());
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            table=vector<int>(A.size()+1, 0);
            for (int y=0; y<size; y++)
                for (int x=0; x<size; x++){
                    if (!isValide09(A[i*size+y][j*size+x], table))
                    return false;
                }
        }
    }
    return true;
}

static bool validateStep_sudoku(vector<vector<int> > &A, int x, int y, int val) {
    for (int i=0; i<A.size(); i++) {
        if (A[y][i]==val)
            return false;
    }
    for (int i=0; i<A.size(); i++) {
        if (A[i][x]==val)
            return false;
    }
    int size = sqrt(A.size());
    int regY=y/size;
    int regX=x/size;
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++) {
            if (A[regY*size+i][regX*size+j]==val)
                return false;
        }
    return true;
}

static bool solveSudoku_helper(vector<vector<int> > &A, int x, int y) {
//    cout << x << y << endl;
//    cin.get();
    if (x==A.size()) {
        x=0;
        y++;
        if (y==A.size())
            return true;
    }

    if (A[y][x]!=0)
        return solveSudoku_helper(A, x+1, y);

    for (int i=1; i<=A.size(); i++) {
        if (!validateStep_sudoku(A, x, y, i))
            continue;
        A[y][x]=i;
        if (solveSudoku_helper(A, x+1, y))
            return true;
    }
    A[y][x]=0;
    //    cout << x << y << endl;
    //    cin.get();
    return false;
}

bool Leet::solveSudoku(vector<vector<int> > &A) {
    if (!validateSudoku(A))
        return false;
    if (!solveSudoku_helper(A, 0, 0))
        return false;

    for (int i=0; i<A.size(); i++) {
        copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return true;
}

static void appendNode(shared_ptr<Leet::LNode> &head, shared_ptr<Leet::LNode>& tail, shared_ptr<Leet::LNode> &node) {
    head ? tail->next = node : head=node;
    tail = node;
}

static void appendNode_advance(shared_ptr<Leet::LNode> &head, shared_ptr<Leet::LNode>& tail, shared_ptr<Leet::LNode> &node) {
    appendNode(head, tail, node);
    node=node->next;}


void Leet::reorderList(shared_ptr<LNode> &head) {
    if (!head || !head->next)
        return;
    // find the middle
    shared_ptr<LNode> slow=head, fast=head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    shared_ptr<LNode> bhead = slow->next;
    slow->next=nullptr;

    // reverse the latter halp
    bhead = reverseList_iterative(bhead);
    printList(head);
    printList(bhead);

    // merge two list
    shared_ptr<LNode> curr=head, bcurr=bhead, newHead, tail;
    while (curr && bcurr) {
        appendNode_advance(newHead, tail, curr);
        appendNode_advance(newHead, tail, bcurr);
    }
    if (curr)
        appendNode(newHead, tail, curr);
    if (bcurr)
        appendNode(newHead, tail, bcurr);

    head=newHead;
    printList(head);
}

static void wordBreak_helper(string &s, int index, string &curr, unordered_set<string> & dict, vector<string> &res,
                             vector<bool> &table){
    if (index==s.size()) {
        cout << curr << endl;
        res.push_back(curr);
        return;
    }

    for (int i=1; i<=s.size()-index; i++) {
        if (table[index+i]) {
            string x=s.substr(index, i);
            string currbackup=curr;
            if (dict.find(x) != dict.end()) {
                int before=res.size();
                curr += " " + x;
                //            cout << curr << ", next idx=" << index+i << ", range=" << s.size()-index-i << endl;
                wordBreak_helper(s, index+i, curr, dict, res, table);
                if (before==res.size())
                    table[index+i]=false;
            }
            curr=currbackup;
        }
    }
}

vector<string> Leet::wordBreak(string s, unordered_set<string> &A){
    vector<string> res;
    if (s.empty())
        return res;
    string curr;
    vector<bool> table(s.size()+1, true);
    wordBreak_helper(s, 0, curr, A, res, table);
    return res;
}

bool Leet::wordBreak_efficient(string s, unordered_set<string> &A) {
    vector<bool> table(s.length()+1, false);
    table[0]=true;
    for (int i=1; i<=s.size(); i++) {
        for (int j=0; j<i; j++)
            if (table[j] && A.find(s.substr(j, i-j))!=A.end()) {
                table[i]=true;
                break;
            }
    }
    return table.back();
}

void Leet::wordBreak_efficient_print(const string s, const unordered_set<string> &D) {
    if (s.empty()) return;
    vector<int> table(s.size()+1, 0);
    table[0]=1;
    for (int i=1; i<=s.size(); i++)
        for (int j=0; j<i; j++) {
            if (table[j]!=0 && D.find(s.substr(j, i-j)) != D.end()) {
                table[i]=i-j;
                break;
            }
        }
    if (table.back()==0) return;
    vector<string> ret;
    int idx=s.size();
    while (idx>0) {
        int size=table[idx];
        ret.push_back(s.substr(idx-size, size));
        idx -=size;
    }
    reverse(ret.begin(), ret.end());
    copy(ret.begin(), ret.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

int Leet::appearOnce_otherAppearThreeTimes(vector<int> &A) {
    vector<int> bit(32,0);

    for (auto &x: A) {
        for (int i=0; i<32; i++) {
            int shift=x>>i;
            if (shift == 0)
                break;
            bit[i]+=shift & 1;
        }
    }
    int res=0;
    for (int i=0; i<32; i++)
        res |= ((bit[i]%3) << i);
    return res;
}

int Leet::appearOnce_otherAppearThreeTimes_noextraspace(vector<int> &A) {
    int res=0;
    for (int i=0; i<32; i++) {
        int bit=0;
        for (auto &x: A) {
            if(x>>i & 1)
                bit++;
        }
        res |= (bit %3 ) << i;
    }
    return res;
}

int Leet::appearOnce_otherAppearThreeTimes_mostefficient(const vector<int> &A) {
    int ones=0, twos=0, threes=0;
    for (auto &a :A) {
        twos |= ones & a;
        ones ^= a;
        threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }
    return ones;
}

int Leet::gasStation(vector<int> &gas, vector<int> &dist) {
    int carry=0;
    pair<int, int> res(0, 0);
    for (int i=1; i<=gas.size(); i++) {
        carry += gas[i-1]-dist[i-1];
        if (carry<res.second) {
            res=pair<int, int>(i, carry);
        }
    }
    return carry<0?-1:res.first%gas.size(); // mod is for the first station (res.first=gas.size())
}

bool isPalindromeStr(string s) {
    int i=0, j=s.size()-1;
    while (i<j ) {
        if (s[i]!=s[j])
            return false;
        i++;j--;
    }
    return true;
}

int Leet::palindromePartition(string s) {
    vector<pair<int, int> > table(s.size()+1, pair<int,int>(INT_MAX, -1));
    table[0]=pair<int,int>(0, 0);
    for (int i=1; i<=s.size(); i++)
        for (int j=0; j<i; j++) {
            if (table[j].first!=INT_MAX &&table[j].first+1<table[i].first && isPalindromeStr(s.substr(j, i-j))) {
                table[i]=pair<int,int>(table[j].first+1, i-j);
            }
        }
    if (table.back().first==INT_MAX) return -1;
    vector<string> ret;
    int idx=s.size();
    while (idx>0) {
        int size=table[idx].second;
        ret.push_back(s.substr(idx-size, size));
        idx -= size;
    }
    reverse(ret.begin(), ret.end());
    copy(ret.begin(), ret.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    return table.back().first;
}

static vector<vector<string> > palindromePartition_allset_helper(string &s, int idx) {
    vector<vector<string> > ret;
    if (idx=s.size()) {
        ret.emplace_back(vector<string>());
        return ret;
    }
    for (int i=1; i<=s.size()-idx; i++) {
        string t = s.substr(idx, i);
        if (isPalindromeStr(t)) {
            auto A = palindromePartition_allset_helper(s, idx+i);
            for (auto &a:A) {
                vector<string> x;
                x.push_back(t);
                x.insert(x.end(), a.begin(), a.end());
                ret.push_back(x);
            }
        }
    }
    return ret;

}

vector<vector<string> > Leet::palindromePartition_allset(string s) {
    return palindromePartition_allset_helper(s, 0);
}

static bool touchBoundary(vector<vector<char> > &A, int y, int x, vector<vector<bool> > &table) {
    if (y<0 || y>=A.size() || x<0 || x>=A.size())
        return true;
    table[y][x]=true;
    vector<pair<int, int> > L = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
    for (auto &d : L) {
        int i =y+d.first;
        int j= x+d.second;
        if (!table[i][j] && touchBoundary(A, i, j, table))
                return true;
    }
    return false;
}

static void flip(vector<vector<char> > &A, int y, int x) {
    vector<pair<int, int> > L = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
    A[y][x]='X';
    for (auto &d: L) {
        int i =y+d.first;
        int j= x+d.second;
        if (A[i][j]=='O')
            flip(A, i, j);
    }
}

static void checkflip(vector<vector<char> > &A, int y, int x, vector<vector<bool> > &table) {

    if (!touchBoundary(A, y, x, table))
        flip(A, y, x);
}

void Leet::surroundedRegion(vector<vector<char> > &A) {
    vector<vector<bool> > table(A.size(), vector<bool>(A.front().size(), false));
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A.size(); j++)
            if (A[i][j]=='X')
                table[i][j]=true;

    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A.size(); j++)
            if (A[i][j]=='O')
                checkflip(A, i, j, table);
}

static bool isValide02(const vector<vector<char> > &A, int y, int x) {
    return y>=0 && y<A.size() && x>=0 && x<A.front().size() && A[y][x]=='O';
}

void Leet::surroundedRegion_efficient(vector<vector<char> > &A) {
    queue<pair<int, int> > Q;

    int rows=A.size(), cols=A.front().size();
    for (int i=0; i<A.size(); i++) {
        if (A[i][0]=='O')
            Q.push(make_pair(i, 0));
        if (A[i][cols-1]=='O')
            Q.push(make_pair(i, cols-1));
    }
    for (int i=0; i<cols; i++) {
        if (A[0][i]=='O')
            Q.push(make_pair(0,i));
        if (A[rows-1][i]=='O')
            Q.push(make_pair(rows-1, i));
    }

    vector<pair<int, int> > D = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
    while (!Q.empty()) {
        auto t = Q.front();
        Q.pop();
        A[t.first][t.second]='Y';
        for (auto &d : D) {
            int y=t.first+d.first;
            int x=t.second+d.second;
            if (isValide02(A, y, x))
                Q.push(make_pair(y, x));
        }
    }
    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++) {
            if (A[i][j]=='O')
                A[i][j]='X';
            else if (A[i][j]=='Y')
                A[i][j]='O';
        }
}

void sumTreeRootToLeaf_helper(shared_ptr<Leet::TNode> root, int &sum, int path) {
    if (!root) {
        return;
    }
    path += root->data;
    if (!root->left && !root->right) {
        sum+=path;
        return;
    }
    sumTreeRootToLeaf_helper(root->left, sum, path);
    sumTreeRootToLeaf_helper(root->right, sum, path);

}

int Leet::sumTreeRootToLeaf(shared_ptr<TNode> root) {
    int sum=0, path=0;
    sumTreeRootToLeaf_helper(root, sum, path);
    return sum;
}

int Leet::longestConsecutiveSequence(vector<int> &A){
    unordered_set<int> table;
    for (auto &x : A) {
        table.emplace(x);
    }

    int maxLen=0;
    for (auto &x : A) {
        int len=1;
        auto curr = x;
        while (table.find(--curr) != table.end()) {
            len++;
            table.erase(curr);
        }
        curr=x;
        while (table.find(++curr) != table.end()) {
            len++;
            table.erase(curr);
        }
        maxLen=max(maxLen, len);
    }

    return maxLen;
}

void wordLadder2_helper(string a, unordered_set<string> &D, vector<string> &Q, unordered_map<string, vector<string> >&prev) {
    for (int i=0; i<a.size(); i++)  {
        string s = a;
        for (char k='a'; k<='z'; k++) {
            s[i]=k;
            if (D.find(s) != D.end()) {
                Q.emplace_back(s);
                D.erase(s);
                prev[s].emplace_back(a);
            }
        }
    }
}

vector<string> getPath(string s, unordered_map<string, vector<string> > &prev) {
    vector<string> ret;
    while (prev.find(s) != prev.end()) {
        ret.push_back(s);
        s=prev[s].front();
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<vector<string> > savePath(unordered_map<string, vector<string> > &prev, string e) {
    vector<vector<string> > ret;
    vector<string> A = prev[e];
    for (auto &a : A)
        ret.emplace_back(getPath(a, prev));
    return ret;
}

static void wordLadder2_print(string s, string e, unordered_map<string, string> & prev) {
    string t=e;
    vector<string>seq;
    while (t!=s) {
        seq.emplace_back(t);
        t=prev[t];
    }
    seq.emplace_back(s);
    reverse(seq.begin(), seq.end());
    copy(seq.begin(), seq.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

/**
 * @brief Leet::wordLadder2
 * // maybe use only queue<string> Q while record current, and hashmap for path
 * if only need single path, hashmap can be <current, previoutOne>
 * for multiple path, use hashmap <current, vector<vector<string> >
 * don't forget we need erase the dictionay to mark we have visited before
 * @param s
 * @param e
 * @param D
 * @return
 */
vector<vector<string> > Leet::wordLadder2(string s, string e, unordered_set<string> &D) {
    vector<vector<string> > ret;
    if (s.size()!=e.size())
        return ret;
    D.emplace(e);

    unordered_map<string, string> prev;
    queue<string> Q;
    Q.emplace(s);
    D.erase(s);

    while (!Q.empty()) {
        auto t = Q.front();
        Q.pop();
        if (t==e) {
            wordLadder2_print(s, e, prev);
//            D.emplace(e);
            continue;
        }
        for (int i=0; i<t.size(); i++)
            for (char j='a'; j<='z'; j++) {
                string x=t;
                x[i]=j;
                if (D.find(x) != D.end()) {
//                    cout << x << " " << t << endl;
                    if (x==e) {
                        prev[x]=t;
                        wordLadder2_print(s, e, prev);
                        break;
                    }
                    D.erase(x);
                    prev[x]=t;
                    Q.emplace(x);
                }
            }
    }
    return ret;
//    unordered_map<string, vector<string> > prev;
//    vector<vector<string> > Q(2);
//    int flag=0;
//    D.erase(s);
//    Q[flag].emplace_back(s);

//    while (!Q[flag].empty()) {
//        Q[1-flag].clear();
//        for (int i=0; i<Q[flag].size(); i++) {
//            if (Q[flag][i]==e){
//                return savePath(prev, e);
//            }
//            wordLadder2_helper(Q[flag][i], D, Q[1-flag], prev);
//        }
//        flag=1-flag;
//    }
    return vector<vector<string> >();
}

bool Leet::validPalindrome(string s) {
    if (s.empty()) return true;
    int i=0, j=s.size()-1;
    while (i<j) {
        while (i<j && i<s.size() && !isalpha(s[i]))
            i++;
        while (i<j && j<s.size() && !isalpha(s[j]))
            j--;
        if (i<j && tolower(s[i])!=tolower(s[j]))
            return false;
        i++;
        j--;
    }
    return true;
}

int Leet::maxProfit_onebuysell(vector<int> &A) {
    int minV=A[0], maxProfit=INT_MIN;
    for (int i=1; i<A.size(); i++) {
        maxProfit=max(maxProfit, A[i]-minV);
        minV = min(minV, A[i]);
    }
    return maxProfit;
}

int Leet::maxProfit_twobuysell(vector<int> &A) {
    if (A.size()<2)
        throw invalid_argument("A size is less than 2");
    vector<int> forward(A.size(), INT_MIN);
    int minV=A[0];
    for (int i=1; i<A.size(); i++) {
        forward[i]=max(forward[i-1], A[i]-minV);
        minV = min(A[i], minV);
    }
    vector<int> backward(A.size(), INT_MIN);
    int maxV=A.back();
    for (int i=A.size()-2; i>=0; i--) {
        backward[i]=max(backward[i+1], maxV-A[i]);
        maxV = max(A[i], maxV);
    }

    int maxProfit=INT_MIN;
    for (int i=1; i<A.size()-2; i++) {
        maxProfit=max(maxProfit, forward[i]+backward[i+1]);
    }
    return maxProfit;

}

/**
 * @brief Leet::maxProfit_kbuysell
 * B(j, i) = -A[i]+max(S(j-1, i'));
 * S(j, i) = A[i]+max(B(j, i'))
 * @param A
 * @param k
 * @return
 */
int Leet::maxProfit_kbuysell(vector<int> &A, int k) {
    vector<int> table(k<<1, INT_MIN);

    for (int i=0; i<A.size(); i++) {
        vector<int> table2(table);
        for (int j=0, sign=-1; j<table.size() && j<=i; j++, sign *= -1) {
            int diff = sign* A[i] + j==0 ? 0 : table2[j-1];
            table[j] = max(diff, table2[j]);
        }
    }
    table.back();
//    vector<int> buy0(k, INT_MIN);
//    vector<int> sell0(k, INT_MIN);

//    for (int i=0; i<A.size(); i++) {
//        vector<int> buy(buy0);
//        vector<int> sell(sell0);
//        for (int j=0; j<k && j<=i; j++) {
//            int x = -A[i] + j==0? 0:sell[j-1];
//            buy0[j] = max(x, buy[j]);
//            x = A[i] + buy[j];
//            sell0[j] = max(x, sell[j]);
//        }
//    }
//    return sell0.back();
}

int Leet::maxProfit_unlimit(vector<int> &A) {
    if (A.empty())
        return 0;
    int profit=0, buy=A.front();

    for (int i=1; i<A.size()-1 ; i++) {
        if (A[i-1]<=A[i] && A[i]>A[i+1]){
            profit += A[i]-buy;
            buy=A[i+1];
        } else if (A[i-1]>=A[i] && A[i]<A[i+1])
            buy=A[i];
    }
    if (A.back()>buy)
        profit += A.back()-buy;

    return profit;
}

/**
 * @brief Leet::numDistinctSubsequence
 * @param s: search long string
 * @param t: target
 * @return
 */
int Leet::numDistinctSubsequence(string s, string t) {
    vector<vector<int> > D(s.size()+1, vector<int>(t.size()+1, 0)) ;
    for (int i=0; i<s.size(); i++)
        D[i][0]=1;

    for (int i=1; i<=s.size(); i++)
        for (int j=1; j<=t.size(); j++)
            D[i][j]=D[i-1][j]+(s[i-1]==t[j-1]?D[i-1][j-1]:0);
    for (auto &d : D) {
        copy(d.begin(), d.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    cout << D.back().back() << endl;
//    vector<vector<int> > D(t.size()+1, vector<int>(s.size()+1, 0));
//    for (int i=0; i<=t.size(); i++)
//        D[i][0]=0;
//    for (int i=0; i<=s.size(); i++)
//        D[0][i]=1;
//    for (int i=1; i<=t.size(); i++) {
//        for (int j=1; j<=s.size(); j++)
//            D[i][j]=D[i][j-1]+(t[i-1]==s[j-1]? D[i-1][j-1] : 0);
//        copy(D[i].begin(), D[i].end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//    }
    return D.back().back();
}

void Leet::connectLNodeRightNeighbor_completeTree(shared_ptr<TNode> &root) {
    if (!root) return;
    shared_ptr<TNode> next=root;

    while (next) {
        shared_ptr<TNode> curr=next;
        next = curr->left;
        shared_ptr<TNode> prev=nullptr;
        while (curr->right) {
            if (prev)
                prev->next = curr->left;
            curr->left->next = curr->right;
            prev = curr->right;
            curr=curr->next;
        }
    }
}

void Leet::printLNodeRightNeighbor(shared_ptr<Leet::TNode> &root) {
    queue<shared_ptr<Leet::TNode> > q;
    q.push(root);
    while (!q.empty()) {
        shared_ptr<Leet::TNode> node=q.front();
        q.pop();
        cout << node->data << " right=";
        if (node->next)
            cout << node->next->data << endl;
        else
            cout << "null" << endl;

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    cout << endl;
}

void advanceNode(shared_ptr<Leet::TNode> & head, shared_ptr<Leet::TNode> &tail, shared_ptr<Leet::TNode> & node) {
    head ? tail->next = node : head = node;
    tail = node;
}

void Leet::populateNextRightPointers(shared_ptr<Leet::TNode> &root) {
    auto head = root;
    shared_ptr<Leet::TNode> tail=nullptr;
    while (head) {
        auto node = head;
        head =nullptr;
        tail = nullptr;
        while (node) {
            if (node->left) advanceNode(head, tail, node->left);
            if (node->right) advanceNode(head, tail, node->right);
            node=node->next;
        }
    }
}

void moveNext(shared_ptr<Leet::TNode> & head, shared_ptr<Leet::TNode> &tail, shared_ptr<Leet::TNode> &node) {
    if (node) {
        head ? tail->next = node : head = node;
        tail = node;
    }
}

void Leet::connectLNodeRightNeighbor_anyTree(shared_ptr<TNode> &root) {
    if (!root) return;
    shared_ptr<TNode> next=root;

    while (next) {
        shared_ptr<TNode> curr=next;
        shared_ptr<TNode> tail=nullptr;
        next=nullptr;
        while (curr) {
//            cout << curr->data << " next=";
//            if (curr->next)
//                cout << curr->next->data << endl;
//            else
//                cout << "null" << endl;
            moveNext(next, tail, curr->left);
            moveNext(next, tail, curr->right);
            curr=curr->next;
        }
    }
}

static shared_ptr<Leet::TNode> buildTreeRecursive(const vector<int> &A, int left, int right) {
    if (left>right)
        return nullptr;
    int mid=left + ((right-left)>>1);
    shared_ptr<Leet::TNode> root(new Leet::TNode(A[mid]));
    root->left = buildTreeRecursive(A, left, mid-1);
    root->right = buildTreeRecursive(A, mid+1, right);
    return root;
}

shared_ptr<Leet::TNode> Leet::buildTree_LNodeRightNeighbor(const vector<int> &A) {
    if (A.empty())
        return nullptr;
    shared_ptr<TNode> root=buildTreeRecursive(A, 0, A.size()-1);
    return root;
}

shared_ptr<Leet::TNode> Leet::buildTree_LNodeRightNeighbor2(const vector<int> &A) {
    if (A.empty())
        return nullptr;
    queue<shared_ptr<TNode> > q;
    shared_ptr<TNode> root(new TNode(A[0]));
    q.push(root);
    int index=1;
    while (!q.empty() && index<A.size()) {
        shared_ptr<TNode> node = q.front();
        q.pop();
        node->left = shared_ptr<TNode>(new TNode(A[index++]));
        q.push(node->left);
        if (index<A.size()) {
            node->right = shared_ptr<TNode>(new TNode(A[index++]));
            q.push(node->right);
        }
    }
    return root;
}

void Leet::flattenBinaryTree(shared_ptr<TNode> &root) {
    if (!root) return;
    if (root->left) flattenBinaryTree(root->left);
    if (root->right) flattenBinaryTree(root->right);
    auto tmp = root->right;
    root->right = root->left;
    root->left = nullptr;
    auto node = root, prev=root;
    while (node) {
        prev=node;
        node=node->right;
    }
    prev->right=tmp;


}

static void pathSum2_helper(shared_ptr<Leet::TNode> node, int k, vector<int> &curr, vector<vector<int> > &ret) {
    if (!node){
        return;
    }
    curr.push_back(node->data);
    int sum=k-node->data;
    if (!node->left && !node->right && sum==0) {
        ret.push_back(curr);
    }
    if (node->left) pathSum2_helper(node->left, k-node->data, curr, ret);
    if (node->right) pathSum2_helper(node->right, k-node->data, curr, ret);
    curr.pop_back();

}

vector<vector<int> > Leet::pathSum2(shared_ptr<TNode> root, int k) {
    int sum=0;
    vector<vector<int> > ret;
    vector<int> curr;
    pathSum2_helper(root, k, curr, ret);
    return ret;
}

static void minimumDepthBT_helper(shared_ptr<Leet::TNode> &node, int depth, int &minDepth) {
    if (!node) {
        minDepth = min(minDepth, depth);
        return;
    }

    minimumDepthBT_helper(node->left, depth+1, minDepth);
    minimumDepthBT_helper(node->right, depth+1, minDepth);
}

// there
int Leet::minimumDepthBT(shared_ptr<TNode> root) {
    int minDepth=-1;
    minimumDepthBT_helper(root, -1, minDepth);
    return minDepth;
}

shared_ptr<Leet::TNode> convertSortedListToBST_helper(shared_ptr<Leet::LNode> & node, int s, int e) {
    if (s>=e)
        return nullptr;
    int m = s+((m-e)>>1);
    auto left = convertSortedListToBST_helper(node, s, m);
    shared_ptr<Leet::TNode> root(new Leet::TNode(node->data));
    node=node->next;
    root->left=left;
    root->right=convertSortedListToBST_helper(node, m, e);
    return root;
}

shared_ptr<Leet::TNode> Leet::convertSortedListToBST(shared_ptr<LNode> &head) {
    if (!head) return nullptr;
    auto curr=head;
    int k=0;
    while (curr) {
        k++;
        curr=curr->next;
    }
    return convertSortedListToBST_helper(head, 0 , k);
}

shared_ptr<Leet::TNode> convertSortedArrayToBST_helper(vector<int> &A, int s, int e) {
    if (s>=e)
        return nullptr;
    int m=s+((e-s)>>1);
    auto left = convertSortedArrayToBST_helper(A, s, m);
    shared_ptr<Leet::TNode> root(new Leet::TNode(A[m]));
    root->left = left;
    root->right = convertSortedArrayToBST_helper(A, m+1, e);
    return root;
}

shared_ptr<Leet::TNode> Leet::convertSortedArrayToBST(vector<int> &A) {
    return convertSortedArrayToBST_helper(A, 0, A.size());
}

shared_ptr<Leet::TNode> convertPreorderArrayToBST_helper(vector<int> &A, int idx, int minv, int maxv) {
    if (idx==A.size() || A[idx]<minv || A[idx]>maxv)
        return nullptr;
    int curr=A[idx];
    idx++;
    return shared_ptr<Leet::TNode>(new Leet::TNode(curr, convertPreorderArrayToBST_helper(A, idx, minv, curr),
                                                   convertPreorderArrayToBST_helper(A, idx, curr, maxv)));
}

shared_ptr<Leet::TNode> Leet::convertPreorderArrayToBST(vector<int> &A) {
    int idx=0;
    return convertPreorderArrayToBST_helper(A, idx, INT_MIN, INT_MAX);
}

shared_ptr<Leet::TNode> convertPreorderListToBST_helper(shared_ptr<Leet::LNode> &node, int minv, int maxv) {
    if (!node || node->data<minv || node->data>maxv)
        return nullptr;
    int curr=node->data;
    shared_ptr<Leet::TNode> root(new Leet::TNode(curr));
    node=node->next;
    root->left = convertPreorderListToBST_helper(node, minv, curr);
    root->right = convertPreorderListToBST_helper(node, curr, maxv);
    return root;
}

shared_ptr<Leet::TNode> Leet::buildTreeFromSerializedArray(vector<string> &A) {
    if (A.empty())return nullptr;
    queue<shared_ptr<TNode> > Q;
    shared_ptr<TNode> n(shared_ptr<TNode>(new TNode(stoi(A[0]))));
    Q.push(n);
    int idx=1;
    while (!Q.empty() && idx<A.size()) {
        auto top = Q.front();
        Q.pop();
        if (A[idx]!="#") {
            top->left=shared_ptr<TNode>(new TNode(stoi(A[idx])));
            Q.push(top->left);
        }
        idx++;
        if (A[idx]!="#") {
            top->right=shared_ptr<TNode>(new TNode(stoi(A[idx])));
            Q.push(top->right);
        }
        idx++;
    }
    return n;
}

shared_ptr<Leet::TNode> Leet::convertPreorderListToBST(shared_ptr<LNode> &head) {
    return convertPreorderListToBST_helper(head, INT_MIN, INT_MAX);
}

vector<vector<int> > Leet::BSTLeverOrderTraversal_reverse(shared_ptr<TNode> &root) {
    if (!root) return vector<vector<int> >();
    queue<shared_ptr<TNode> > Q;
    Q.push(root);
    vector<vector<int> > ret;
    while (!Q.empty()) {
        auto prev= Q;
        vector<int> tmp;
        while (!prev.empty()) {
            auto top = prev.front();
            prev.pop();
            tmp.push_back(top->data);
            if (top->left)
                Q.push(top->left);
            if (top->right)
                Q.push(top->right);
        }
        ret.push_back(tmp);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

static void restoreIPAddress_helper(string &s, int index, vector<string> &curr, vector<string> &res) {
    if (index==s.size() ) {
        if (curr.size()==4) {
            string str(curr[0]);
            for (int i=1; i<4; i++)
                str += "." +curr[i];
            res.push_back(str);
        }
        return;
    }
    if (curr.size()>=4) {
        return;
    }

    for (int i=1; i<=3 && index+i<=s.size(); i++) {
        string str = s.substr(index, i);
        if (str[0] != '0' && stoi(str) <256) {
            curr.push_back(str);
//            cout << __LINE__ << ":" << index << "," << i << "," << s.size() << "," << curr.size() << endl;
//            copy(curr.begin(), curr.end(), ostream_iterator<string>(cout, " "));
//            cout << endl;
            restoreIPAddress_helper(s, index+i, curr, res);
            curr.pop_back();
        }
    }
}

static int uniqueBST_helper(int s, int e) {
    if (s>=e) return 1;
    int ret=0;
    for (int i=s; i<=e; i++) {
        int left= uniqueBST_helper(s, i-1);
        int right=uniqueBST_helper(i+1, e);
        ret += left*right;
        cout << i << " " << left << " " << right << " " << ret << endl;
    }
    return ret;
}

int Leet::uniqueBST(int n) {
    if (!n) return 0;
    return uniqueBST_helper(1, n);
}

static vector<shared_ptr<Leet::TNode> > uniqueBST2_helper(int s, int e) {
    vector<shared_ptr<Leet::TNode> > ret;
    if (s>e) {
        ret.push_back(nullptr);
        return ret;
    }

    for (int i=s; i<=e; i++) {
        vector<shared_ptr<Leet::TNode> >left, right;
        left = uniqueBST2_helper(s, i-1);
        right = uniqueBST2_helper(i+1, e);

        for (auto &x : left)
            for (auto &y : right) {
                shared_ptr<Leet::TNode> n(new Leet::TNode(i));
                n->left = x;
                n->right = y;
                ret.push_back(n);
            }
    }

}

vector<shared_ptr<Leet::TNode> > Leet::uniqueBST2(int n) {
    return uniqueBST2_helper(1, n);
}

vector<string> Leet::restoreIPAddress(string s) {
    if (s.empty() || s.size()>12) {
        cout << "string size=" << s.size() << endl;
        throw invalid_argument("the size must be 1-12");
    }

    vector<string> res;
    vector<string> curr;
    restoreIPAddress_helper(s, 0, curr, res);
    copy(res.begin(), res.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    return res;
}

void reverseList2_helper(shared_ptr<Leet::LNode> &head, shared_ptr<Leet::LNode> &tail) {
    shared_ptr<Leet::LNode> curr=head, prev=nullptr;
    tail=head;
    while (curr) {
        auto next = curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    head=prev;
}

void Leet::reverseList2(shared_ptr<LNode> &head, int m, int n) {
    if (!head || m<0 || n<0)
        throw invalid_argument("invalid input");

    auto prev=head, curr=head;
    if (n>m)
        swap(m, n);
    int k=0;
    auto start1=head;
    while (curr && k<m) {
        k++;
        prev=curr;
        curr=curr->next;
    }
    if (!curr)
        throw invalid_argument("invalid reverse node");

    auto start2=curr;
    auto tail1 = prev;
    tail1->next = nullptr;
    while (curr && k<n) {
        k++;
        prev=curr;
        curr=curr->next;
    }
    auto start3=curr;
    auto tail2 = prev;
    tail2->next=nullptr;

    bool isHead=false;
    if (start1==start2)
        isHead=true;

    reverseList2_helper(start2, tail2);

    if (isHead)
        head=start2;
    else
        tail1->next = start2;

    if (start3==nullptr)
        return;
    else
        tail2->next=start3;
}

static vector<int> subset2_helper(const vector<int> &A, int k){
    vector<int> ret;
    int m=0;
    while (k) {
        if (k&1)
            ret.push_back(A[m]);
        m++;
        k=k>>1;
    }
    return ret;
}

struct HashCode_subset2 {
    size_t operator()(const vector<int> &A) const {
        int ret=0;
        for (auto &a : A)
            ret ^= hash<int>()(a);
        return ret;
    }
};

vector<vector<int> > Leet::subset2(vector<int> &A) {
    sort(A.begin(), A.end());

    vector<vector<int> > ret;
    unordered_set<vector<int>, HashCode_subset2> S;
    for (int i=0; i<(1<<A.size()); i++) {
        auto x = subset2_helper(A, i);
//        copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//        ret.push_back(x);
        S.insert(subset2_helper(A, i));
    }
    for( auto &x: S) {
        copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        ret.push_back(x);
    }
    return ret;
}

vector<vector<int> > subset2_better_helper(const map<int, int> &M, int k) {
    vector<vector<int> > ret;
    ret.push_back(vector<int>());
    auto m=M.begin();
    while (k) {
        if (k&1) {
            vector<vector<int> > A;
            vector<int> B;
            for (int i=0; i<m->second; i++) {
                B.push_back(m->first);
                A.push_back(B);
            }
            vector<vector<int> > next;
            for (int i=0; i<ret.size(); i++) {
                for (int j=0; j<A.size(); j++) {
                    auto tmp = ret[i];
                    tmp.insert(tmp.end(), A[j].begin(), A[j].end());
                    next.push_back(tmp);
                }
            }
            ret=next;
//            for (auto &a: ret) {
//                copy(a.begin(), a.end(), ostream_iterator<int>(cout, "-"));
//                cout << endl;
//            }
        }
        m++;
        k=k>>1;
    }
    return ret;
}

vector<vector<int> > Leet::subset2_better(vector<int> &A) {
    map<int, int> M;
    vector<vector<int> > ret;
    for (auto &a : A)
        M[a]++;
    for (int i=0; i<(1<<M.size()); i++) {
        auto x=subset2_better_helper(M, i);
        ret.insert(ret.end(), x.begin(), x.end());
    }
    for (auto &a : ret) {
        copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

vector<vector<int> > Leet::subset3(vector<int> &A) {
    vector<vector<int> > ret;
    vector<int> curr;
    ret.push_back(curr);

    for (int i=0; i<A.size(); i++) {
        auto tmp(ret);
        for (auto &t : tmp){
            t.push_back(A[i]);
            ret.push_back(t);
        }
    }
    for (auto &t : ret) {
        copy(t.begin(), t.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

vector<vector<int> > Leet::subset3_duplicates(vector<int> A) {
    sort(A.begin(), A.end());
    vector<vector<int> > ret;
    ret.push_back(vector<int>());
    int k=1;
    for (int i=0; i<A.size(); i++) {
        auto tmp(ret);
        int idx=0;
        if (i!=0 && A[i]==A[i-1])
            idx=tmp.size()-k;
        k=0;
        for (int j=idx; j<tmp.size(); j++) {
            auto &x=tmp[j];
            tmp[j].push_back(A[i]);
            ret.push_back(tmp[j]);
            k++;
        }
    }
    for (auto &t : ret) {
        copy(t.begin(), t.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

int Leet::decodeWays(string s) {
    vector<int> D(s.size()+1, 0);
    D[0]=1;
    for (int i=1; i<=D.size(); i++) {
        for (int j=1; j<3; j++) {
            if (j==1)
                D[i] += i-j>=0 ? D[i-j] :0 ;
            if (j==2 && i-j>=0) {
                string x= s.substr(i-j, j);
                if (x>="10" && x<="26" )
                    D[i] += i-j>=0 ? D[i-j] :0 ;
            }

        }
    }
    return D.back();
}

bool isanagram(string s0, string s1) {
    unordered_map<char, int> M;
    for (auto &c : s0)
        M[c]++;
    for (auto &c : s1){
        M[c]--;
        if (M[c]<0)
            return false;
    }
    for (auto &x : M) {
        if (x.second != 0)
            return false;
    }
    return true;
}

bool Leet::isScrambleStrings(string s0, string s1) {
    if (s0.empty() && s1.empty() || s0==s1) return true;
    if (s0.size()!=s1.size() || !isanagram(s0, s1))
        return false;

    for (int i=1; i<s0.size(); i++){
        string x0=s0.substr(0, i), x1=s0.substr(i, s0.size()-i);
        string y0=s1.substr(0, i), y1=s1.substr(i, s1.size()-i);
        string y3=s1.substr(0, s1.size()-i), y4=s1.substr(s1.size()-i, i);
        if (isScrambleStrings(x0, y0) && isScrambleStrings(x1, y1))
            return true;
        if (isScrambleStrings(x0, y1) && isScrambleStrings(x1, y0))
            return true;
        if (isScrambleStrings(x0, y4) && isScrambleStrings(x1, y3))
            return true;
    }
    cout << s0 << " " << s1 << endl;
    return false;

//    if (s1.length()!=s0.length())
//        return false;
//    if (s0.empty() || s0==s1)
//        return true;

//    string x1=s1, x0=s0;
//    sort(x0.begin(),x0.end());
//    sort(x1.begin(), x1.end());
//    if (x1 != x0)
//        return false;

//    for (int i=1; i<s0.size(); i++) {
//        if (isScrambleStrings(s0.substr(0, i), s1.substr(0, i)) && isScrambleStrings(s0.substr(i), s1.substr(i)))
//            return true;
//        else if (isScrambleStrings(s0.substr(0, i), s1.substr(s1.size()-i)) && isScrambleStrings(s0.substr(i), s1.substr(0, s1.size()-i)))
//            return true;
//    }
//    return false;
}

int maxRectangle_helper(const vector<int> &A) {
    if (A.empty()) return 0;
    vector<int> left(A.size(), 0);
    for (int i=1; i<A.size(); i++) {
        if (A[i]<A[i-1])
            left[i]=left[i-1];
        else
            left[i]=i;
    }
    vector<int> right(A.size(), A.size()-1);
    for (int i=A.size()-2; i>=0; i--) {
        if (A[i]<A[i+1])
            right[i]=right[i+1];
        else
            right[i]=i;
    }
    int maxv=INT_MIN;
    for (int i=0; i<A.size(); i++) {
        maxv = max(maxv, A[i]*(right[i]-left[i]+1));
    }
    return maxv;

}

int Leet::maxRectangle(const vector<vector<bool> > &A) {
    vector<vector<int> > D(A.size(), vector<int>(A.front().size(), 0));

    for (int i=A.size()-1; i>=0; i--)
        for (int j=A[i].size()-1; j>=0; j--) {
            if (A[i][j]) {
                D[i][j]= i+1<A.size() ? D[i+1][j]+1 : 1;
            }
        }

    int ret=0;
    for (auto &d: D)
        ret = max(ret, maxRectangle_helper(d));

    return ret;
}

void advance2(shared_ptr<Leet::LNode> &head, shared_ptr<Leet::LNode> &tail, shared_ptr<Leet::LNode> &node) {
    head ? tail->next = node : head = node;
    tail = node;
}

void Leet::removeDuplicates(shared_ptr<LNode> &head) {
    if (!head) return;
    shared_ptr<LNode> curr=head, newhead=nullptr, tail=nullptr, prev=nullptr;
    while (curr){
        if (!prev || curr->data!=prev->data)
            advance2(newhead, tail, curr);
        curr=curr->next;
    }
    head=newhead;
}

void Leet::removeDuplicates2(shared_ptr<LNode> &head)
{
    printList(head);
    if (!head || !head->next) return;
    shared_ptr<LNode> newHead=nullptr, tail=nullptr, prev;
    auto curr=head;
    int k=0;
    while (curr) {
        if (prev) {
            if (curr->data != prev->data) {
                if (k==1)
                    advance2(newHead, tail, prev);
                k=1;
            } else
                k++;
        } else {
            k++;
        }
        prev=curr;
        curr=curr->next;
    }
    tail->next=nullptr;
    if (k==1)
        advance2(newHead, tail, prev);
    head=newHead;
    printList(head);
}

void Leet::removeElem(vector<int> &A, int elem) {
    int k=0;
    for (int i=0; i<A.size(); i++){
        if (A[i]!=elem) {
            A[k]=A[i];
            k++;
        }
    }
    A.resize(k);
}

void Leet::removeDuplicatesArray(vector<int> &A) {
    if (A.size()<=1) return;
    int k=0;
    for (int i=1; i<A.size(); i++) {
        if (A[i]!=A[k]) {
            A[++k]=A[i];
        }
    }
    A.resize(++k);
}

pair<shared_ptr<Leet::LNode>, shared_ptr<Leet::LNode> > reverseList_helper(shared_ptr<Leet::LNode> head) {
    auto curr=head;
    shared_ptr<Leet::LNode> prev=nullptr;
    while (curr) {
        auto next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return {prev, head};
}

void Leet::reverseNodesKGroup(shared_ptr<LNode> &head, int k) {
    shared_ptr<LNode> curr=head, prev=nullptr, left=head, shortTail=nullptr;
    int m=0;
    while (curr) {
        m++;
        prev=curr;
        curr=curr->next;
        if (m%k==0) {
            prev->next=nullptr;
            auto newList=reverseList_helper(left);

            if (shortTail==nullptr)
                head=newList.first;
            else
                shortTail->next=newList.first;
            shortTail=newList.second;

            prev=newList.second;
            prev->next=curr;
            left=curr;
        }
    }
}

void Leet::swapNodesInPairs(shared_ptr<LNode> &head) {
    shared_ptr<LNode> curr=head, prev=nullptr, prevprev=nullptr;
    while (curr && curr->next) {
        prev=curr;
        curr=curr->next;
        auto next=curr->next;

        curr->next=prev;
        prev->next=next;

        if (prevprev) {
            prevprev->next=curr;
        } else
            head=curr;
        prevprev=prev;

        curr=next;
    }
}

struct tupleHash {
    size_t operator()(const vector<int> &A) const {
        int x=0;
        for (auto &a : A)
            x ^= hash<int>()(a);
        return x;
    }
};

static bool wordSearch_helper(vector<vector<char> > &A, string &word, int i, int j, int k,
                unordered_set<vector<int>, tupleHash>& M, vector<vector<bool> > &visited) {
    if (i<0 || i>=A.size() || j<0 || j>=A[i].size()
            || A[i][j]!=word[k] || M.find({i, j, k}) != M.end() || visited[i][j])
        return false;
    vector<pair<int, int> > D={{0, 1}, {0,-1}, {1, 0}, {-1, 0}};
    visited[i][j]=true;
    for (auto &d : D){
        if (wordSearch_helper(A, word, i+d.first, j+d.second, k+1, M, visited))
            return true;
    }
    visited[i][j]=false;
    vector<int> key={i,j, k};
    M.emplace(key);
    return false;
}

bool Leet::wordSearch(vector<vector<char> > &A, string word) {
    unordered_set<vector<int>, tupleHash> M;
    vector<vector<bool> > visited(A.size(), vector<bool>(A.front().size(), false));

    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A[i].size(); j++) {
            if (wordSearch_helper(A, word, i, j, 0, M, visited))
                return true;
        }

    return false;
}

struct ListComp {
    bool operator()(const shared_ptr<Leet::LNode> &a, const shared_ptr<Leet::LNode> &b) const  {
        return a->data > b->data;
    }
};

shared_ptr<Leet::LNode> Leet::mergeKList(const vector<shared_ptr<LNode> > &A) {
    priority_queue<shared_ptr<LNode>, vector<shared_ptr<LNode> >, ListComp> Q;

    shared_ptr<LNode> head=nullptr, tail;
    for (auto &a : A)
        if (a)
            Q.push(a);

    while(!Q.empty()) {
        auto top = Q.top();
        Q.pop();
        if (head)
            tail->next=top;
        else
            head=top;
        tail=top;
        if (tail->next)
            Q.push(tail->next);
    }
    return head;

}

void generateParentheses_helper(string s, int left, int right, vector<string> &ret) {
    if (right==0) {
        ret.push_back(s);
        return;
    }
//    if (left<=0 )
//        if (right<=0) {
//            ret.push_back(s);
//        return;
//    }

    if (left>0) {
        s.push_back('(');
        generateParentheses_helper(s, left-1, right, ret);
        s.pop_back();
    }
    if (right>left) {
        s.push_back(')');
        generateParentheses_helper(s, left, right-1, ret);
        s.pop_back();
    }
}

vector<string> Leet::generateParentheses(int n) {
    vector<string> ret;
    generateParentheses_helper(string(), n, n, ret);
    copy(ret.begin(), ret.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    return ret;
}

int Leet::largestRectangleHistogram(const vector<int> &A) {
    if (A.empty())
        return 0;
    stack<int> s;
    int maxV=0;
    for (int i=0; i<A.size(); i++) {
        if (s.empty() || A[s.top()]<=A[i])
            s.push(i);
        else {
            int tmp = s.top();
            s.pop();
            maxV = max(maxV, A[tmp]*(s.empty() ? i : (i-s.top()-1)));
            i--;
        }
    }
    while (!s.empty()) {
        int tmp = s.top();
        s.pop();
        maxV = max(maxV, A[tmp]*(s.empty() ? (int) A.size() : int(A.size()-s.top()-1)));
    }
    return maxV;
}

int Leet::trapRainWater(const vector<int> &A) {
    if (A.size() < 3)
        return 0;

    stack<int> s;
    int sum=0;
    int level=0;
    for (int i=0; i<A.size(); i++) {
        if (s.empty() || A[i] < A[s.top()]) {
            level=A[i];
            s.push(i);
        }
        else {
            int tmp = s.top();
            s.pop();
//            if (i-tmp>1)
                sum += (A[tmp]-level) * (i-tmp-1);
            level = A[tmp];
            i--;
        }
    }
    return sum;
}

int Leet::trapRainWater2(const vector<int> &A) {
    stack<int> S;
    int water=0;
    for (int i=0; i<A.size(); i++) {
        while (!S.empty() && A[i]>A[S.top()]) {
//            cout << S.size() << " " << A[i] << endl;
            if (S.size()>=2) {
                int tmp=S.top();
                S.pop();
//                cout << A[S.top()] << " " << A[i] << " " << A[tmp] << " " << i << " " << S.top() << endl;
                water += (min(A[S.top()], A[i])-A[tmp])*(i-S.top()-1);
            }
            S.pop();
        }
        if (!S.empty() && A[i]==A[S.top()])
            continue;
        S.push(i);
    }
    return water;
}

int Leet::firstMissingPositive(vector<int> &A) {
    int n=A.size();
    for (int i=0; i<A.size(); i++) {
        while (A[i]>=1 && A[i]<=n && A[i]-1!=i) {
            swap(A[i], A[A[i]-1]);
        }
    }
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    for (int i=0; i<A.size(); i++)
        if (A[i]-1 != i)
            return i+1;
    return -1;
}

double Leet::powInt(double x, int n) {
    if (!n)
        return 1;
    if (n==1)
        return x;
    if (!x && n<0)
        throw invalid_argument("x=0 and n <0");
    if (n<0)
        return 1/powInt(x, -n);

    if (n&1)
        return x*powInt(x, n-1);
    else  {
        double y=powInt(x, n>>1);
        return y*y;
    }

}

static string callNumber_helper(string & prev) {
    string res;
    if (prev.empty())
        return res;

    char curr=prev[0];
    int count =1;
    for (int i=1; i<prev.size(); i++) {
        if (prev[i]==curr)
            count++;
        else {
            res.push_back(char('0'+count));
            res.push_back(curr);
            curr=prev[i];
            count =1;
        }
    }
    res.push_back('0'+count);
    res.push_back(curr);
    return res;
}

string Leet::callNumber(int n) {
    cout << __LINE__ << endl;
    if (n<1)
        return string();
    cout << __LINE__ << endl;

    string prev("1");
    for (int i=1; i<n; i++) {
        string curr=callNumber_helper(prev);
        prev=curr;
    }
    cout << __LINE__ << endl;
    return prev;
}

pair<int, int> Leet::searchSorted2D(const vector<vector<int> > &A, int k) {
    pair<int, int> res(-1, -1);
    if (A.empty() || A.front().empty())
        return res;

    int low=0, high=A.size()*A.front().size()-1;
    while (low<=high) {
        int mid = low+((high-low)>>1);

        int y = mid/A.front().size();
        int x = mid%A.front().size();
        if (A[y][x]==k) {
            res= pair<int, int>(y, x);
            break;
        } else if (A[y][x]<k)
            low=mid+1;
        else
            high=mid-1;
    }
    cout << res.first << "-" << res.second << endl;
    return res;
}

pair<int, int> Leet::searchSorted2D_2(const vector<vector<int> > &A, int k) {
    pair<int, int> res(-1, -1);
    if (A.empty() || A.front().empty())
        return res;

    int y=0, x=A.front().size()-1;
    while (y<A.size() && x >=0) {
        if (A[y][x]==k){
            res=pair<int, int>(y, x);
            break;
        } else if (A[y][x]<k) {
            y++;
        } else
            x--;
    }
    cout << res.first << "-" << res.second << endl;
    return res;

}

static string constructLine(vector<string> &A, int left, int right, bool isEnd, int k) {
    string res;
    if (isEnd || left==right) {
        res=A[left];
        for (int i=left+1; i<=right; i++)
            res += " "+A[i];
        return res;
    }
    int len=0;
    for (int i=left; i<=right; i++)
        len += A[i].size();
    int space = (k-len)/(right-left);
    int remain = (k-len)%(right-left);

    res += A[left] + string(remain, ' ');
    for (int i=left+1; i<=right; i++) {
        res += string(space, ' ') + A[i];
    }
    return res;
}

vector<string> Leet::textJustify(vector<string> &A, int k) {
    if (A.empty() || k<A[0].size())
        return vector<string>();
    if (A.size()==1)
        return A;

    vector<string> res;
    int left=0, right=0, len=A[0].size();
    for (int i=1; i<A.size(); i++) {
        if (A[i].size()>k)
            throw invalid_argument("word is too long");

        len += A[i].length()+1;
        if (len>k) {
            string str = constructLine(A, left, right, right==A.size()-1, k);
            res.push_back(str);
            left=i;
            len = A[i].length();
        }

        right=i;

        if (right==A.size()-1) {
            string str = constructLine(A, left, right, right==A.size()-1, k);
            res.push_back(str);

        }
    }
    return res;
}

int plusOne_helper(shared_ptr<Leet::LNode> &root) {
    if (!root)
        return 1;
    int ret = plusOne_helper(root->next);
    ret+= root->data;
    root->data = ret%10;
    return ret/10;
}

void Leet::plusOne(shared_ptr<LNode> &head) {
    int ret = plusOne_helper(head);
    if (ret) {
        shared_ptr<LNode> n(new LNode(ret));
        n->next=head;
        head=n;
    }
}

void combinations_helper(vector<int> &A, int idx, int k, vector<vector<int> > &ret, vector<int> &curr) {
    if (k==0) {
        ret.push_back(curr);
//        ret.push_back(vector<int>(A.begin(), A.begin()+k));
        return;
    }
    for (int i=idx; i<=A.size()-k; i++) {
        curr.push_back(A[i]);
        combinations_helper(A, i+1, k-1,ret, curr);
        curr.pop_back();
//        swap(A[idx], A[i]);
//        combinations_helper(A, idx+1, k, ret);
//        swap(A[idx], A[i]);
    }
}

void combinations_helper2(int s, int e, int k, vector<vector<int> > &ret, vector<int> &curr) {
    if (k==0) {
        ret.push_back(curr);
        return;
    }
    for (int i=s; i<=e; i++){
        curr.push_back(i);
        combinations_helper2(i+1, e, k-1, ret, curr);
        curr.pop_back();
    }
}


vector<vector<int> > Leet::combinations(int n, int k) {
    vector<vector<int> > ret;
    if (n<=0 || k<=0 || n<k)
        return ret;

    vector<int> A(n);
    iota(A.begin(), A.end(), 1);
    vector<int> curr;
    combinations_helper(A, 0, k, ret, curr);
    for (auto &x: ret) {
        copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    ret.clear();
    combinations_helper2(1, n, k, ret, curr);
    for (auto &x: ret) {
        copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    return ret;
}

static void combinationSum_helper(const vector<int> &A, int k, int idx,
                                  vector<int> curr, vector<vector<int> > &ret) {
    if (k==0) {
        ret.emplace_back(curr);
        return;
    }
    if (k<0 || idx>=A.size())
        return;

    while (idx && A[idx]==A[idx-1])
        idx++;

    auto tmp=curr;
    for (int i=0; i<=k/A[idx]; i++) {
        if (i) tmp.emplace_back(A[idx]);
        combinationSum_helper(A, k-i*A[idx], idx+1, tmp, ret);
    }


//    for (int i=idx; i<A.size(); i++) {
//        curr.emplace_back(A[i]);
//        combinationSum_helper(A, k-A[i], i+1, curr, ret);
//        curr.pop_back();
//    }
}

vector<vector<int> > Leet::combinationSum(vector<int> &A, int k) {
    vector<vector<int> > ret;
    if (A.empty()) return ret;
    vector<int> curr;
    sort(A.begin(), A.end());

    combinationSum_helper(A, k, 0, curr, ret);
    cout << "combinationSum:" << endl;
    for (auto &r : ret) {
        copy(r.begin(), r.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

static void combinationSum2_helper(const vector<int> &A, int k, int idx,
                                  vector<int> curr, vector<vector<int> > &ret) {
    if (k==0) {
        ret.emplace_back(curr);
        return;
    }
    if (k<0 || idx==A.size())
        return;

    for (int i=idx; i<A.size(); i++) {
        curr.emplace_back(A[i]);
        combinationSum2_helper(A, k-A[i],i+1, curr, ret);
        curr.pop_back();
        while (i<A.size()-1 && A[i]==A[i+1]) i++;
    }
}

vector<vector<int> > Leet::combinationSum2(vector<int> &A, int k) {
    vector<vector<int> > ret;
    if (A.empty()) return ret;
    vector<int> curr;
    sort(A.begin(), A.end());

    combinationSum2_helper(A, k, 0, curr, ret);
    cout << "combinationSum2:" << endl;
    for (auto &r : ret) {
        copy(r.begin(), r.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

void permutations_helper(vector<int> &A, int idx, vector<vector<int> > &ret) {
    if (idx==A.size())
        ret.push_back(A);

    for (int i=idx; i<A.size(); i++) {
        if (idx!=i && A[i-1]==A[i])
            continue;
        swap(A[idx], A[i]);
        permutations_helper(A, idx+1, ret);
        swap(A[idx], A[i]);
    }
//    if (e-s==1)
//        return vector<vector<int> >(1, vector<int>(1, A[s]));

//    vector<vector<int> > ret;
//    for (int i=s; i<e; i++) {

//        auto left = permutations_helper(A, s, i);
//        auto right = permutations_helper(A, i, e);
//        for (int m=0; m<left.size(); m++)
//            for (int n=0; n<right.size(); n++) {
//                auto tmp = left[m];
//                tmp.insert(tmp.end(), right[n].begin(), right[n].end());
//                ret.push_back(tmp);
//            }
//        for (int m=0; m<right.size(); m++)
//            for (int n=0; n<left.size(); n++) {
//                auto tmp = right[m];
//                tmp.insert(tmp.end(), left[n].begin(), left[n].end());
//                ret.push_back(tmp);
//            }

//    }
//    return ret;
}

vector<vector<int> > Leet::permutations(vector<int> &A) {
    vector<vector<int> > ret;
    if (A.empty())
        return ret;
    permutations_helper(A, 0, ret);
    for (auto &t : ret) {
        copy(t.begin(), t.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return ret;
}

static void permutation_k_helper(vector<int> &A, int idx, int k, vector<vector<int> > & ret) {
    if (k==0) {
        ret.emplace_back(A.begin(), A.begin()+idx);
        vector<int> tmp(A.begin(), A.begin()+idx);
        copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        return;
    }
    for (int i=idx; i<A.size(); i++) {
        swap(A[idx], A[i]);
        permutation_k_helper(A, idx+1, k-1, ret);
        swap(A[idx], A[i]);
    }
}

vector<vector<int> > Leet::permutations_k(vector<int> &A, int k) {
    vector<vector<int> > ret;
    if (A.empty() || k<=0 || k>A.size())
        return ret;
    permutation_k_helper(A, 0, k, ret);
    return ret;
}

/**
 * @brief Leet::textMessiness
 *M[i]=min(M[i-j]+1<<(k-sum(A[i]+1+A[i-1]+1+...))
 * @param A
 * @param k
 * @return
 */
int Leet::textMessiness(const vector<string> &A, int k) {
    vector<int> M(A.size(), INT_MAX);

    for (int i=0; i<A.size(); i++) {
        int len=k-A[i].size();
        M[i]=min(M[i], (i-1<0 ? 0: M[i-1])+(1<<len));
        for (int j=i-1; j>=0; j--) {
            len-=A[j].size()+1;
            if (len<0)
                break;
            M[i]=min((j-1<0?0:M[j])+(1<<len), M[i]);
        }
    }

    int minV=A.size()<2 ? 0: M[A.size()-2];
    int l=A.back().size();
    for (int i=A.size()-2; i>=0; i--) {
        l += A[i].size()+1;
        if (l>k) {
            break;
        }
        minV = min(minV,i-1<0?0: M[i-1]);
    }

    return minV;


}

string Leet::addBinaryStrings(string x, string y) {
    if (x.empty())
        return y;
    if (y.empty())
        return x;

    string res;
    int carry=0;
    for (int i=x.length()-1, j=y.size()-1; i>=0 || j>=0; i--, j--) {
        int t = int((i>=0?x[i]:'0')-'0')+ int((j>=0?y[j]:'0')-'0') +carry;
        carry = t/2;
        res = to_string(t%2)+res;
        cout << carry << " " << res << endl;
    }
    if (carry)
        res = to_string(carry)+res;

    return res;
}

static bool jumpGame_helper(const vector<int> &A, int index) {
//    cout << index << " " << A[index] << endl;
    if (index==A.size()-1)
        return true;
    if (!A[index])
        return false;
    for (int i=index+1; i<=index+A[index]; i++){
        if (jumpGame_helper(A, i))
            return true;
    }
    return false;
}

bool Leet::jumpGame(const vector<int> &A) {
    if (A.empty())
        return true;
    cout << jumpGame_helper(A, 0) << endl;

    // second method
    vector<bool> D(A.size(), false);
    D[0]=true;

    for (int i=0; i<A.size(); i++) {
        for (int j=1; j<=A[i]; j++) {
            if (i+j<A.size())
                D[i+j] = D[i] || D[i+j];
        }
    }
    cout << D.back() << endl;
    return D.back();

}

int Leet::jumpGame2(const vector<int> &A) {
    vector<int> D(A.size(), INT_MAX);
    D[0]=0;
    for (int i=0; i<A.size(); i++) {
        for (int j=1; j<=A[i]; j++) {
            if (i+j<A.size() && D[i+j]>D[i]+1) {
                D[i+j]=D[i]+1;
                copy(D.begin(), D.end(), ostream_iterator<int>(cout, " "));
                cout << endl;
            }
        }

    }
    return D.back();
}

static bool isSafe(vector<int> &A, int y, int x) {
    for (int i=0; i<y; i++){
        if (A[i]==x || A[i]-x==i-y || A[i]-x == y-i)
            return false;
    }
    return true;
}

static void NQueens_helper(vector<int> &A, int y, vector<vector<string> > &res) {
    if (y==A.size()) {
        vector<string> one;
        for (int i=0; i<A.size(); i++) {
            string str(A.size(), '.');
            str[A[i]]='Q';
            one.push_back(str);
        }
        res.push_back(one);

    }
    for (int i=0; i<A.size(); i++) {
        if (isSafe(A, y, i)) {
            A[y]=i;
            NQueens_helper(A, y+1, res);
            A[y]=0;
        }
    }

}

vector<vector<string> > Leet::NQueens(int n) {
    vector<vector<string> > res;
    vector<int> A(n, 0);
    NQueens_helper(A, 0, res);
    return res;
}

static string addStrings(string &x, string &y) {
    string res;
    int carry=0;
    for (int i=x.size()-1, j=y.size()-1; i>=0 || j>=0 || carry; i--, j--) {
        int tmp = int(i>=0?x[i]-'0':0) + int(j>=0?y[j]-'0' : 0) + carry;
        carry = tmp/10;
        res = string(1, tmp%10+'0') + res;
    }
    return res;
}

static void decreaseString(string &x) {
    if (x=="0")
        return;
    int carry=1;
    for (int i=x.size()-1; i>=0 && carry; i--) {
        if (x[i]>='1') {
            x[i] -= 1;
            carry =0;
        } else {
            x[i]='9';
            carry =1;
        }
    }
    while (!x.empty()) {
        if (x[0]!='0')
            break;
        x.erase(0,1);

    }
}

string Leet::multiplyStrings(string x, string y) {
    if (x.empty() || y.empty())
        throw invalid_argument("one of inputs is empty");
    if (y.size()>x.size())
        return multiplyStrings(y, x);
    if (y=="0" || x=="0")
        return string("0");

    string res(x);
    while (y.compare("1")) {
        res=addStrings(res, x);
        decreaseString(y);
    }
    return res;
}

static vector<int> multiplyVector_helper(vector<int> &x, int y) {
    vector<int> res;
    int carry=0;
    for (int j=0; j<x.size(); j++) {
        int tmp = y * x[j] + carry;
        res.push_back(tmp%10);
        carry = tmp/10;
//            cout << __LINE__ << " " << tmp << " " << carry << endl;
//            cin.get();
    }
    if (carry)
        res.push_back(carry);
    return res;
}

static vector<int> addVector(vector<int> &A, vector<int> &B) {
    int carry=0;
    vector<int> res;
    for (int i=0, j=0; i<A.size() || j<B.size() || carry; i++, j++) {
        int tmp = (i<A.size() ? A[i]:0) + (j<B.size()?B[j]:0) + carry;
        res.push_back(tmp%10);
        carry = tmp/10;
    }
    return res;
}

static vector<int> multiplyVector(vector<int> &x, vector<int> &y) {
//    copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
//    cout << "x" << endl;
//    copy(y.begin(), y.end(), ostream_iterator<int>(cout, " "));
//    cout << "y" << endl;
    vector<int> res;
    for (int i=0; i<y.size(); i++) {
        vector<int> part = multiplyVector_helper(x, y[i]);
        for (int j=0; j<i; j++)
            part.insert(part.begin(), 0);
        res = addVector(res, part);
    }
    return res;
}

string Leet::multiplyStrings_efficient(string x, string y) {
    if (x.empty() || y.empty())
        throw invalid_argument("one of inputs is empty");
    if (y=="0" || x=="0")
        return string("0");
    vector<int> xint, yint;
    for (int i=x.size()-1; i>=0; i--) {
        xint.push_back(int(x[i]-'0'));
    }
    for (int i=y.size()-1; i>=0; i--) {
        yint.push_back(int(y[i]-'0'));
    }
    vector<int> res = multiplyVector(xint, yint);
//    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
    string str;
    for (auto &x:res) {
        str = char(x+'0')+str;
    }
    return str;
}

static vector<int> multiplyVector_better(vector<int> &x, vector<int> &y){
    vector<int> z(x.size()+y.size(), 0);
    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++)
            z[i+j]+=x[i]*y[j];
    // transfer to 0-9
    int carry=0;
    for (int i=0; i<z.size(); i++){
        int tmp=z[i]+carry;
        carry=tmp/10;
        z[i]=tmp%10;
    }

    for (int i=z.size()-1; i>=0; i--){
        if (z[i])
            break;
        z.pop_back();
    }
    return z;
}

string Leet::multiplyStrings_moreefficient(string x, string y) {
    vector<int> xint, yint;
    for (int i=x.size()-1; i>=0; i--)
        xint.push_back(x[i]-'0');
    for (int i=y.size()-1; i>=0; i--)
        yint.push_back(y[i]-'0');

    vector<int> z = multiplyVector_better(xint, yint);

    string zstr;
    for (int i=z.size()-1; i>=0; i--)
        zstr.push_back((z[i]+'0'));
    return zstr;
}

bool Leet::regexMatch(string s, string p) {
//    cout << s << "->" << p << endl;
    if (s.empty())
        return p.empty() || p==".*";
    if (p.empty())
        return s.empty();

    if (p[0]=='*')
        throw invalid_argument("no preceding char before *");

    if (p==".*")
        return true;

    if (p[0]=='^') {
        if (p.size()<2)
            throw invalid_argument("there is no char after ^");
        else
            return s[0]==p[1] && regexMatch(s.substr(1), p.substr(2));
    }

    if (p[p.size()-1]=='$') {
        if (p.size()<2)
            throw invalid_argument("no char before $");
//        cout << s.substr(0, s.size()-1)<< "+" << p.substr(0, p.size()-2) << "-" << (s[s.size()-1]==p[s.size()-2]) << endl;
//        cout << s[s.size()-1] << "====" << p[p.size()-2] << endl;
        return (s[s.size()-1]==p[p.size()-2]) && regexMatch(s.substr(0, s.size()-1), p.substr(0, p.size()-2));
    }

    if (p.size()>=2 && p[1]=='*') {
//        if (p[0]=='*')
//            throw invalid_argument("input include **");
//        if (regexMatch(s, p.substr(2)))
//            return true;
        if ((s[0]==p[0] || p[0]=='.') && regexMatch(s.substr(1), p))
                return true;
        return regexMatch(s, p.substr(2));
//        return regexMatch(s.substr(1), p);
    }

    return (s[0]==p[0] || p[0]=='.') && regexMatch(s.substr(1), p.substr(1));

}

bool Leet::wildcardMatching(string x, string y) {
    if (x.empty()) {
        if (y.empty() || y=="*")
            return true;
        else
            return false;
    }

    cout << x << " " << y << " " << (y=="*") << endl;
    if (y=="*")
        return true;

    if (x[0]==y[0] || y[0]=='?' )
        return wildcardMatching(x.substr(1), y.substr(1));

    if (y[0]=='*') {
        if (y.size()>2) {
            if (x[0]==y[1]) {
                if (wildcardMatching(x.substr(1), y.substr(2)))
                    return true;
            }
            return wildcardMatching(x.substr(1), y);

        } else
            return true;

    }

    return false;
}

int Leet::divideInts(int x0, int y0) {
    if (y0==0)
        throw invalid_argument("divisor is zero");

    int x=abs(x0);
    int y=abs(y0);
    bool sign=true;
    if (x!=x0 ^ y!=y0)
        sign=false;

    if (x==0 || x<y)
        return 0;

    int res=0;
    if (y&1 ==0)
        res= divideInts(x>>1, y>>1);
    else
        res= 1+divideInts(x-y, y);

    return sign?res:-res;
}

vector<vector<int> > Leet::sum2(vector<int> &A, int k) {
    vector<vector<int> > res;
    if (A.size()<2)
        return res;
    sort(A.begin(), A.end());
//    unique(A.begin(), A.end());
    int left=0, right=A.size()-1;
    while (left<right) {
        int sum = A[left]+A[right];
        if (sum==k) {
            vector<int> part{A[left], A[right]};
            res.emplace_back(part);
            left++;
            right--;
        } else if (sum<k) {
            left++;
        }
        else {
            right--;
        }
        while(left-1>=0 && A[left]==A[left-1])
            left++;
        while (right+1<A.size() && A[right]==A[right+1])
            right--;
    }
    return res;
}

vector<vector<int> > Leet::sum3(vector<int> &A, int k) {
    vector<vector<int> >res;
    if (A.size()<3)
        res;
    sort(A.begin(), A.end());
//    unique(A.begin(), A.end());

    for (int i=A.size()-1; i>=2; i--) {
        if (i!=A.size()-1 && A[i]==A[i+1])
            continue;
        vector<int> part(A.begin(), A.begin()+i);
        vector<vector<int> > t = sum2(part, k-A[i]);
        if (!t.empty()) {
            for (auto &x : t) {
                x.push_back(A[i]);
                res.push_back(x);
            }
        }
    }
    return res;
}

vector<vector<int> > Leet::sum4(vector<int> &A, int k) {
    vector<vector<int> > res;
    if (A.size()<4)
        return res;

    sort(A.begin(), A.end());
//    unique(A.begin(), A.end());
    for (int i=A.size()-1; i>=2; i--) {
        if (i!=A.size()-1 && A[i]==A[i+1])
            continue;
        vector<int> part(A.begin(), A.begin()+i);
        vector<vector<int> > t = sum3(part, k-A[i]);
        if (!t.empty()) {
            for (auto &x : t) {
                x.push_back(A[i]);
                res.push_back(x);
            }
        }
    }
    return res;
}

static bool compareB(const pair<int, int> &x, const pair<int, int> &y) {
    return x.first+x.second < y.first +y.second;
}

struct HashCodeVector {
    size_t operator()(const vector<int> &A) const {
        size_t x=0;
        for (auto &a : A)
            x^=hash<int>()(a);
        return x;
    }
};

vector<vector<int> > Leet::sum4_efficient(vector<int> &A, int k) {
    vector<vector<int> > res;
    if (A.size()<4)
        return res;
    unordered_map<int, vector<vector<int> > > M;
    vector<int> B;

    for (int i=0; i<A.size()-1; i++)
        for (int j=i+1; j<A.size(); j++) {
            int x=A[i]+A[j];
            auto it = M.find(x);
            if (it == M.end()) {
                B.emplace_back(x);
            }
            vector<int> tmp={i, j};
            M[x].emplace_back(tmp);
        }

    auto y = sum2(B, k);
    if (y.empty())
        return res;

    unordered_set<vector<int>, HashCodeVector> ans;
    for (auto &t : y) {
        for (auto &i : M[t[0]])
            for (auto &j : M[t[1]]) {
                vector<int> tmp = i;
                tmp.insert(tmp.end(), j.begin(), j.end());
                sort(tmp.begin(), tmp.end());
                auto it=unique(tmp.begin(), tmp.end());
                tmp.resize(distance(tmp.begin(), it));
                if (tmp.size()==4)
                ans.emplace(tmp);
//                res.push_back(tmp);
            }
    }
    for (auto &tmp : ans) {
        copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        res.emplace_back(tmp);

    }
    return res;

}
//    sort(A.begin(), A.end());
////    unique(A.begin(), A.end());

//    vector<pair<int, int> > B;
//    for (int i=0; i<A.size()-1; i++)
//        for (int j=i+1; j<A.size(); j++) {
//            B.emplace_back(A[i], A[j]);
//        }

//    sort(B.begin(), B.end(), compareB);
//    vector<int> C;
//    for (auto &x : B)
//        C.push_back(x.first+x.second);
//    copy(C.begin(), C.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;

//    vector<vector<int> > one = sum2(C, k);
////    unordered_set<vector<int> > table;
//    if (!one.empty()) {
//        for (auto &x:one) {
//            copy(x.begin(), x.end(), ostream_iterator<int>(cout, " "));
//            cout << endl;
//            vector<int> z;

//            auto it = equal_range(C.begin(), C.end(), x[0]);
//            for (auto itx=it.first; itx<it.second; itx++) {
//                int dist = itx-C.begin();
//                cout << B[dist].first << "-" << B[dist].second << ":";
//            }
//            it = equal_range(C.begin(), C.end(), x[1]);
//            for (auto itx=it.first; itx<it.second; itx++) {
//                int dist = itx-C.begin();
//                cout << B[dist].first << "-" << B[dist].second << endl;
//            }
//            // there are many possible combination, must check whether there are 4 unique index
//            // So i stop here, assume that the interview will not go further.
//        }
//    }
//    return res;


int Leet::sum2_closest(vector<int> &A, int k) {
    int res=INT_MAX;
    if (A.size()<2)
        throw invalid_argument("A size is less than 2");

    sort(A.begin(), A.end());
    int left = 0, right = A.size()-1;
    while (left<right) {
        int sum = A[left]+A[right];
        if (sum==k)
            return 0;
        else if (sum<k) {
            left++;
        } else {
            right--;
        }
        res = min(res, abs(sum-k));

    }
    return res;
}

int Leet::sum3_closest(vector<int> &A, int k) {
    if (A.size()<3)
        throw invalid_argument("num of elements is less than 3");

    int res;
    bool first=true;
    sort(A.begin(), A.end());
    for (int i=0; i<=A.size()-3;i++) {
        for (int j=i+1; j<A.size(); j++) {
            vector<int> tmp(A.begin()+j, A.end());
            auto x = sum2_closest(tmp, k-A[i]);
            x += A[i];
        if (first) {
            first = false;
            res=x;
        } else
            res = abs(x-k)<abs(res-k) ? x : res;
        }
    }
    return res;
}

int Leet::reverseInt_noSpace(int x) {
    int res=0;
    bool isNegative=false;
    if (x<0) {
        isNegative = true;
        x = -x;
    }

    while (x) {
        int tmp = x%10;

        if ((INT_MAX-tmp)/10 <res)
            throw invalid_argument("overflow");

        res = res*10+tmp;
        x /=10;
    }
    return isNegative ? -res : res;
}

string Leet::convertIntToRoman(int x) {
    if (x<1 || x>3999)
        throw invalid_argument("input is not at the range");

//    vector<pair<int, string> > A={{1, "A"},{2, "B"},{3, "C"}};

    vector<pair<int, string> > D={{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
                                 {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"},
                                 {5, "V"}, {4, "IV"}, {1, "I"}};
    string ret;
    for (int i=0; i<D.size(); i++) {
        while (x>=D[i].first) {
            x -= D[i].first;
            ret += D[i].second;
        }
    }
    return ret;

//    vector<string> strtable{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V","IV", "I"};
//    vector<int> table{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

//    string str;
//    for (int i=0; i<table.size(); i++) {
//        while (x>=table[i]) {
//            x -= table[i];
//            str += strtable[i];
//        }
//    }
//    return str;
}

static int cti(char c) {
    switch (c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

int Leet::convertRomanToInt(string s) {
    if (s.empty())
        return 0;
    int ret=cti(s[0]);
    for (int i=1; i<s.size(); i++) {
        if (cti(s[i])>cti(s[i-1]))
            ret += cti(s[i])-2*cti(s[i-1]);
        else
            ret += cti(s[i]);
    }
    return ret;
//    map<char, int> table{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
//    int res=0;

//    for (int i=0; i<x.size(); i++) {
//        if (table.find(x[i])==table.end())
//            throw invalid_argument("invalid string input");

//        if (i>0 && table[x[i]]>table[x[i-1]])
//            res += table[x[i]]-2*table[x[i-1]];
//        else
//            res += table[x[i]];
//    }
//    return res;

}

shared_ptr<Leet::LNode> Leet::findBeginCyclicList(shared_ptr<LNode> &root) {
    if (!root)
        return nullptr;
    shared_ptr<LNode> slow=root, fast=root;
    while (fast || fast->next) {
        fast=fast->next->next;
        slow=slow->next;
        if (slow==fast) {
            slow=root;
            while (slow!=fast){
                slow=slow->next;
                fast=fast->next;
            }
            return slow;
        }
    }
    return nullptr;

}

int Leet::editDist(string x, string y) {
    vector<vector<int> > table(x.size()+1, vector<int>(y.size()+1, 0));
    for (int i=0; i<=x.size(); i++)
        table[i][0]=i;
    for (int i=0; i<=y.size(); i++)
        table[0][i]=i;

    for (int i=1; i<=x.size(); i++)
        for (int j=1; j<=y.size(); j++) {
            int minSide = min(table[i-1][j], table[i][j-1]);
            table[i][j]=x[i-1]==y[j-1] ? table[i-1][j-1]
                                       : min(table[i-1][j-1], minSide)+1;
        }
    return table.back().back();

}

int Leet::editDist_efficientSpace(string x, string y) {
    if (x.empty()) return y.size();
    if (y.empty()) return x.size();

    if (x.length()<y.length())
        swap(x, y);

    vector<vector<int> > table(2, vector<int>(y.size()+1, 0));
    for (int i=0; i<=y.size(); i++)
        table[0][i]=i;

    int flag=0;
    for (int i=1; i<=x.size(); i++) {
        vector<int> & prev=table[flag];
        vector<int> & curr = table[1-flag];
        curr[0]=i;
        for (int j=1; j<=y.size(); j++) {
            int minSide = min(prev[j], curr[j-1]);
            curr[j]=x[i-1]==y[j-1] ? prev[j-1]
                                       : min(prev[j-1], minSide)+1;
        }
        flag=1-flag;
    }
    return table[flag].back();

}


