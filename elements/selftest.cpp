#include "selftest.h"
#include "iostream"
#include "iterator"
#include <queue>
#include <stack>
#include <utility>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <fstream>
#include <climits>
#include <set>
#include <cassert>

static void merge(vector<int> &A, int s, int m, int e) {
//    cout << "merge" << endl;
//    cout << s << " " << m << " " << e << endl;
    int lnl = m - s +1;
    int lnr = e-m ;
    vector<int> B(m-s+1);
    vector<int> C(e-m);
    copy(A.begin()+s, A.begin()+m+1, B.begin());
    copy(A.begin()+m+1, A.begin()+e+1, C.begin());

    int i=0, j=0 , k=s;
    while (i<lnl && j<lnr) {
        A[k++] = B[i] < C[j] ? B[i++]: C[j++];
    }
    if (i<lnl)
        copy(B.begin()+i, B.end(), A.begin()+k);
    else if (j<lnr)
        copy(C.begin()+j, C.end(), A.begin()+k);
}

void Selftest::mergeSort(vector<int> &A, int s, int e) {
    if (s>=e) return;
    int m = s + ((e-s)>>1);
    mergeSort(A, s, m);
    mergeSort(A, m+1, e);

    merge(A, s, m, e);
}

static int quickSort_helper3(int *A, int s, int e) {
    int m = s + ((e-s)>>1);
    int pivot = A[m];
    int i=s, j=e;
    while (i<=j) {
        while (A[i] < pivot )
            i++;
        while (A[j] > pivot )
            j--;
        if (i<=j) {
            swap(A[i++], A[j--]);
        }
    }
    return i;
}

/**
 * @brief Selftest::quickSort
 * @param A
 * @param s
 * @param e
 */
void Selftest::quickSort(int *A, int s, int e){
    if (s>=e)return;
    int sep = quickSort_helper3(A, s, e);
    quickSort(A, s, sep-1);
    quickSort(A, sep, e);
}

//although the final results in sort, this part result is not right
static int quickSort_helper(vector<int> &A, int s, int e) {
//    if (s>=e) return s;
    int m = s + ((e-s)>>1);
    int pivot = A[m];
    int i=s, j=e;
    while (i<=j) {
        while (A[i] < pivot )
            i++;
        while (A[j] > pivot )
            j--;
        if (i<=j) {
            swap(A[i++], A[j--]);
        }
    }
    cout << pivot << " " << i << endl;
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cin.get();
    return i;
}

static int quickSort_helper2(vector<int> &A, int s, int e) {
    int pivot = A[e];
    int small=s;
    for (int i=s; i<=e-1; i++) {
        if (A[i]<pivot)
            swap(A[i], A[small++]);
    }
    swap(A[e], A[small]);
    return small;
}

void Selftest::quickSort(vector<int> &A, int s, int e) {
    if (s>=e) return;
    int sep = quickSort_helper(A, s, e);
    quickSort(A, s, sep-1);
    quickSort(A, sep, e);
}

void Selftest::quickSort2(vector<int> &A, int s, int e) {
    if (s>=e) return;
    int sep = quickSort_helper2(A, s, e);
    quickSort(A, s, sep-1);
    quickSort(A, sep+1, e);
}

void Selftest::SortSmallEqualLarge(vector<int> &A, int k) {
//    quickSort_helper(A, 0, A.size()-1);
    int s=0, e=0, l=A.size()-1;
    while (e<=l) {
        if (A[e]<k)
            swap(A[e++], A[s++]);
        else if (A[e]==k)
            e++;
        else
            swap(A[e], A[l--]);
    }
}

bool Selftest::TicTocGame::move(int player, int y, int x) {
    if (x<0 || y<0 || x>=B.size() || y >= B.size() || player !=1 && player != 2 || B[y][x] != 0)
        return false;
    B[y][x] = player;
    return true;
}

int Selftest::TicTocGame::check() {
    int size = B.size();
    for (int i=0; i<size; i++) {
        if (B[i][0]==0) break;
        for (int j=1; j<size; j++) {
            if (B[i][j] != B[i][j-1])
                break;
        }
        return B[i][0];
    }
    for (int i=0; i<size; i++) {
        if (B[0][i]==0) break;
        for (int j=1; j<size; j++) {
            if (B[j][i] != B[j-1][i])
                break;
        }
        return B[0][i];
    }
    if (B[0][0] != 0) {
        for (int i=1; i<size; i++) {
            if (B[i][i]!=B[i-1][i-1]) break;
        }
        return B[0][0];
    }
    if (B[0][size-1] != 0) {
        for (int i=1; i<size; i++) {
            if (B[i][size-1-i]!=B[i-1][size-i]) break;
        }
        return B[0][size-1];
    }
    return 0;

}

bool static isValid(Selftest::Coor & p, vector<vector<bool> > &B) {
    return p.x>=0 && p.y>=0 && p.y<B.size() && p.x<B.front().size() && B[p.y][p.x]==false;
}

void static printPath(vector<vector<Selftest::Coor> > &table, Selftest::Coor &start, Selftest::Coor &exit) {
    stack<Selftest::Coor> path;
    path.emplace(exit);
    Selftest::Coor next;
    do {
        next = exit - table[exit.y][exit.x];
        path.emplace(next);
    } while (next != start);
    while (!path.empty()) {
        auto next = path.top();
        path.pop();
        cout << next.y << "," << next.x << "->";
    }
    cout << endl;
}

void Selftest::robotMoveAtoB(vector<vector<bool> > B, Coor start, Coor exit) {
    queue<Coor> Q;
    B[start.y][start.x] = true;
    Q.emplace(start);
    vector<Coor> move({{1, 0}, {-1, 0}, {0, 1}, {0,-1}});
    vector<vector<Coor> > table(vector<vector<Coor> >(B.size(), vector<Coor>(B.front().size(), Coor({0, 0}))) );

    while (!Q.empty()) {
        auto curr = Q.front();
        Q.pop();
        if (curr == exit) {
            printPath(table, start, exit);
        }
        for (auto m: move) {
            auto next = curr + m;
            if (isValid(next, B)){
                B[next.y][next.x] = true;
                table[next.y][next.x] = m;
                Q.emplace(next);
            }
        }

    }

}

void Selftest::LRU::insert(int x, int price) {
    auto it = T.find(x);
    if (it != T.end()) {
        A.erase(it->second);
    }
    A.emplace_front(x, price);
    T[x] = A.begin();

    if (A.size()>=maxsize) {
        T.erase(A.back().first);
        A.pop_back();
    }
}

bool Selftest::LRU::check(int x, int &price) {
    auto it = T.find(x);
    if (it == T.end())
        return false;

    price = it->second->second;
    A.erase(it->second);
    A.emplace_front(x, price);
    T[x] = A.begin();
    return true;
}

void Selftest::LRU::remove(int x) {
    auto it = T.find(x);
    if (it != T.end()) {
        A.erase(it->second);
        T.erase(it);
    }
}

static int findnthelement_helper(vector<int> &A, int s, int e) {
    int pivot = A[e];
    int l=s;
    for (int i=s; i<e; i++) {
        if (A[i] < pivot)
            swap(A[i], A[l++]);
    }
    swap(A[e], A[l]);
    return l;
}

static int findnthelement(vector<int> &A, int k) {
    if (A.empty() || k<0 || k>=A.size())
        throw invalid_argument("input error");
    int s = 0, e = A.size()-1;
    while (s<=e) {
        int p = findnthelement_helper(A, s, e);
        cout << k << " " << p << endl;
        if (p==k) return A[k];
        else if (p < k)
            s = p+1;
        else
            e = p-1;
    }
    return -1;

}

double Selftest::getMedian(vector<int> &A) {
    int n = A.size()>>1;
    int x = findnthelement(A, n);
//    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
//    cin.get();
    if (A.size() & 1)
        return x;
    else {
//        cout << n << " " << x << " " << findnthelement(A, n-1) << endl;
        return 0.5 * (x + findnthelement(A, n-1));
    }
}

struct compTuple {
    bool operator() (const tuple<int, int, int> &a, const tuple<int, int, int> &b) const {
        return get<0>(a) < get<0>(b);
    }
};

struct Compare {
    bool operator() (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.first > b.first;
    }
};

vector<int> Selftest::merge_arr(const vector<vector<int> > &A) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, compTuple > T;
    for(int i=0; i<A.size(); i++) {
        T.emplace(A[i][0], i, 0);
    }
    vector<int> ans;

    while (!T.empty()) {
        auto x = T.top();
        T.pop();
        ans.push_back(get<0>(x));
        int y = get<1>(x);
        int i = ++get<2>(x);
        if (i < A[y].size())
            T.emplace(A[y][i], y, i);
    }
    return ans;
}

vector<vector<int> > Selftest::sort_k_increase_descrease_arr(const vector<int> &A) {
    vector<vector<int> > S;
    if (A.size()<=1) return S;
    int start = 0;
    bool isIncrease= true;

    for(int i=1; i<A.size(); i++) {
        if (isIncrease && A[i-1]> A[i] || !isIncrease && A[i-1]<A[i]) {
            if (isIncrease)
                S.emplace_back(A.cbegin()+start, A.cbegin()+i);
            else {
                vector<int> B(A.cbegin()+start, A.cbegin()+i);
                reverse(B.begin(), B.end());
                S.emplace_back(B.begin(), B.end());
            }
            start=i;
            isIncrease = !isIncrease;
        }
    }
    if (start<A.size()) {
        if (isIncrease)
            S.emplace_back(A.cbegin()+start, A.cend());
        else {
            vector<int> B(A.cbegin()+start, A.cend());
            reverse(B.begin(), B.end());
            S.emplace_back(B.begin(), B.end());
        }
    }
    return S;
}

void Selftest::online_median(istringstream &sin) {
    int buff;
    priority_queue<int, vector<int>, greater<int> > minheap;
    priority_queue<int> maxheap;

    while (sin>> buff) {
        if (maxheap.empty() || buff <maxheap.top())
            maxheap.push(buff);
        else
            minheap.push(buff);

        if (maxheap.size()+1>minheap.size()) {
            minheap.push(maxheap.top());
            maxheap.pop();
        } else if (minheap.size()+1 > maxheap.size()) {
            maxheap.push(minheap.top());
            minheap.pop();
        }

        if (maxheap.size()==minheap.size())
            cout << 0.5 * (maxheap.top() + minheap.top());
        else {
            double ans = maxheap.size()>minheap.size() ? maxheap.top() : minheap.top();
            cout << ans << endl;
        }

    }

}

static void advance_append(shared_ptr<Selftest::Node> &head, shared_ptr<Selftest::Node> &tail, shared_ptr<Selftest::Node> &curr) {
    head?tail->next = curr : head = curr;
    tail = curr;
    curr = curr->next;
}

shared_ptr<Selftest::Node> Selftest::buildOddEvenList_again(shared_ptr<Node> &head) {
//    if (!head || !head->next)
//        return nullptr;
    shared_ptr<Node> eHead=nullptr, eTail=nullptr, oHead=nullptr, oTail=nullptr;
    while (head) {
        advance_append(eHead, eTail, head);
        if (head)
            advance_append(oHead, oTail, head);
    }
    if (eTail)
        eTail->next = oHead;
    if (oTail)
        oTail->next = nullptr;

    return eHead;

}

string Selftest::findMajorityWord(istringstream &sin) {
    string s;
    int count = 0;
    string candidate;
    while (getline(sin, s)) {
        if (count==0) {
            candidate = s;
            count = 1;
        } else if (s==candidate) {
            count++;
        } else
            count--;
    }
    return candidate;


}

int Selftest::findNearestRepetition(const vector<int> &A) {
    int minD = A.size();
    unordered_map<int, int> T;
    for (int i=0; i<A.size(); i++) {
        auto it = T.find(A[i]);
        if (it == T.end()) {
            T[A[i]] = i;
        } else {
            int d = i-it->second;
            if (minD > d)
                minD = d;
            T[A[i]] = i;
        }
    }
    return minD;

}

shared_ptr<Selftest::Node> Selftest::copyComplexList(shared_ptr<Node> &H) {
    if (!H) return nullptr;
    unordered_map<shared_ptr<Node>, shared_ptr<Node> > T;
    queue<shared_ptr<Node> > Q;
    Q.push(H);
    shared_ptr<Node> n(new Node(H->data));
    T[H] = n;
    while (!Q.empty()) {
        auto node = Q.front();
        Q.pop();
        if (node->next) {
            auto x= node->next;
            auto it = T.find(x);
            if (it == T.end()) {
                shared_ptr<Node> next(new Node(x->data));
                T[x] = next;
            }
            T[node]->next = T[x];
            Q.push(x);
        }
        if (node->jump) {
            auto x= node->jump;
            auto it = T.find(x);
            if (it == T.end()) {
                shared_ptr<Node> next(new Node(x->data));
                T[x] = next;
            }
            T[node]->next = T[x];
            Q.push(x);

        }
    }
    return n;
}

shared_ptr<Selftest::TNode> Selftest::copyTree(const shared_ptr<TNode> &root) {
    if (!root) return nullptr;
    shared_ptr<TNode> copyNode(new TNode(root->data));
    copyNode->left = copyTree(root->left);
    copyNode->right = copyTree(root->right);
    return copyNode;
}

void static DFS(shared_ptr<Selftest::Vertex> &x, int time, vector<shared_ptr<Selftest::Vertex> > &extends) {
    for (auto &e: x->contacts) {
        if (e->visit != time) {
            e->visit = time;
            extends.emplace_back(e);
            DFS(e, time, extends);
        }
    }

}

void Selftest::build_extended_contacts(vector<shared_ptr<Vertex> > &G) {
    for (int i=0; i<G.size(); i++) {
        auto &x = G[i];
        x->visit = i;
        DFS(x, i, x->extend_contacts);
    }

}

bool Selftest::shortestTransform(string &s, string &e, unordered_set<string> &D) {
    if (s.size()!= e.size()) return false;
    queue<string> Q;
    Q.push(s);
    D.erase(s);

    while(!Q.empty()) {
        auto x = Q.front();
        Q.pop();
        if (x==s)
            return true;
        for (int i=0; i<s.size(); i++) {
            char tmp = x[i];
            for (int j=0; j<26; j++) {
                char y = j+'a';
                x[i] = y;
                if (D.find(x) != D.end()) {
                    Q.push(x);
                    D.erase(x);
                }
            }
            x[i] = tmp;
        }

    }
    return false;
}

bool static shortestTransform_DFS_helper(string s, string e, int k, unordered_set<string> &D, vector<string> &path) {
    if (s==e)
        return true;
    for (int i=0; i<26; i++) {
        s[k] = i+'a';
        if (D.find(s)!=D.end())
            D.erase(s);
            path.push_back(s);
            if (shortestTransform_DFS_helper(s, e, k+1, D, path))
                return true;
            path.pop_back();
    }
    return false;

}

bool Selftest::shortestTransform_DFS(string &s, string &e, unordered_set<string> &D) {
    if (e.size() != e.size()) return false;
    vector<string> path;
    if (shortestTransform_DFS_helper(s, e, 0, D, path)) {
        for (auto &x: path){
            cout << x << " ";
        }
        cout << endl;
        return true;
    }
    return false;
}

pair<int,int> Selftest::findPairInSortedArr(vector<int> &A, int k) {
    int s=0, e=A.size();
    while (s<e) {
        int sum = A[s]+A[e];
        if (sum==k)
            return {s, e};
        else if (sum<k)
            s++;
        else
            e--;

    }
    return {-1, -1};
}


int Selftest::binary_search_unknown_len(vector<int> &A, int k) {
    int p=0;
    while (true) {
        try {
            int x = A[(1<<p)-1];
            if (x==k)
                return (1<<p)-1;
            else if (x<k)
                p++;
            else
                break;
        }catch (exception &er) {
                break;
        }
    }
    int s = 1<<(p-1), e = (1<<p)-2;
    while (s<=e) {
        int m = s + ((e-s)>>1);
        try {
            int x = A[m];
            if (x==k)
                return m;
            else if (x<k)
                s=m+1;
            else
                e = m-1;

        } catch (exception &er) {
            e = m-1;
        }
    }
    return -1;
}

//assume numbers are distint
int Selftest::findStartCircularSortedArr(const vector<int> &A){
    int s=0, e=A.size();
    while (s<=e) {
        int m = s+((e-s)>>1);
        int x = A[m];
        if (x<A[e])
            e = m;
        else
            s=m+1;
    }
    return s;
}

static int findStartCircularSorted_RepeatedArr_helper(const vector<int> &A, int s, int e) {
    if (s==e) return s;
    int m = s + ((e-s)>>1);
    int x = A[m];
    if (x<A[e])
        return findStartCircularSorted_RepeatedArr_helper(A, s, m);
    else if (x>A[e])
        return findStartCircularSorted_RepeatedArr_helper(A, m+1, e);
    else {
        int l = findStartCircularSorted_RepeatedArr_helper(A, s, m);
        int r = findStartCircularSorted_RepeatedArr_helper(A, m+1, e);
        return A[l] < A[r] ? l : r;

    }
}

int Selftest::findStartCircularSorted_RepeatedArr(const vector<int> &A) {
    return findStartCircularSorted_RepeatedArr_helper(A, 0, A.size()-1);
}

int Selftest::find_missing_element(ifstream &ifs) {
    vector<int> A(1<<16, 0);
    int x;
    while (ifs >> x) {
        A[x>>16]++;
    }

    bitset<(1<<16)> B;
    for (int i=0; i<A.size(); i++) {
        if (A[i]!=(1<<16)) {
            ifs.clear();
            ifs.seekg(0, ios::beg);
            while (ifs>>x) {
                B.set(((1<<16)-1)&x );
            }
            ifs.close();

            for (int j=0; j<(1<<16); j++) {
                if (B.test(j)==0)
                    return (i<<16) | j;
            }

        }
    }
}

int Selftest::combinationCoins(int x, vector<int> &coins){
    vector<int> path(x+1, 0);
    path[0]=1;
    for (auto &c: coins) {
        for (int i=c; i<=x; i+=c) {
            path[i] += path[i-c];
        }
    }
    return path[x];
}

int Selftest::numberOfPath(int x, vector<int> &steps) {
    if (!x) return 0;
    vector<int> P(x+1, 0);
    for (int i=0; i<=x; i++) {
        for (auto &c: steps)
            P[i] += i<=c ? 1: P[i-c];
    }
    return P[x];
}

int Selftest::numberOfPath2D(vector<vector<int> > &A) {
    for (int i=0; i<A.size(); i++) {
        for (int j=0; j<A.front().size(); j++) {
            if (!i && !j) A[i][j]=0;
            else if (i==0)
                A[i][j] += A[i-1][j];
            else if (j==0)
                A[i][j] += A[i][j-1];
            else
                A[i][j] += A[i-1][j] + A[i][j-1];

        }
    }
    return A.back().back();
}

void Selftest::indirect_sortfile(const string &srcfile, const string &desfile){
    vector<string> arr;
    string s;
    ifstream ifs(srcfile.c_str());
    while (ifs >> s)
        arr.emplace_back(s);

    vector<string *>P;
    for (auto &c: arr)
        P.emplace_back(&c);

    sort(P.begin(), P.end(), [](const string *a, const string *b)->bool{return a->size() < b->size();});

    ofstream out(desfile.c_str());
    for (int i=0; i<P.size(); i++)
        out << *P[i];
}

bool isvalidMove(int y, int x, vector<vector<int> > &A) {
    return y>0 && y<A.size() && x>0 && x<A.front().size() && A[y][x]!= -1;
}

void Selftest::printMatrixSpiralOrder(vector<vector<int> > &A){
    vector<pair<int, int> > D({{0, 1},{1, 0}, {0, -1}, {-1, 0}});
    int y=0, x=0, d=0;
    for (int i=0; i<A.size()*A.front().size(); i++) {
        cout << A[y][x];
        A[y][x] = -1;
        int nexty, nextx;
        while (true) {
            int nexty = y+D[d].first;
            int nextx = x+D[d].second;
            if (isvalidMove(nexty, nextx, A))
                break;
            d = (d+1) % 4;

        }
        y=nexty;
        x=nextx;
    }
}

pair<int, int> Selftest::longestIncreaseSubArr(const vector<int> &A){
    pair<int, int> ans({0, 0});
    if (A.size()==1) return ans;
    int count=1, maxlen=1;
    for (int i=1; i<A.size(); i++) {
        if (A[i-1]<A[i])
            count++;
        else {
            if (maxlen < count){
                maxlen = count;
                ans = make_pair(i-count, i-1);
            }
            count=1;
        }

    }
    return ans;

}

int Selftest::maxProfit2BuySell(const vector<int> &A) {
    if (A.size()<=1) return -1;
    vector<int> forward(A.size(), 0);
    vector<int> backward(A.size(), 0);
    int lowest = A[0];
    for (int i=1; i<A.size(); i++){
        forward[i] = max(forward[i-1], A[i]-lowest);
        lowest = min(lowest, A[i]);
    }
    lowest = A.back();
    for (int i=A.size()-2; i>=0; i++ ) {
        backward[i] = max(backward[i+1], A[i]-lowest);
        lowest = min(lowest, A[i]);
    }
    int maxV=0;
    for (int i=1; i<A.size()-1; i++) {
        maxV = max(maxV, forward[i]+backward[i+1]);
    }
    return maxV;
}

bool static isvalid(pair<int, int> &p, vector<vector<bool> > &A) {
    return p.first>0 && p.first<A.size() && p.second>0 && p.second<A.front().size() && A[p.first][p.second]==false;
}

bool static sequenceIn2DArr_helper(const vector<vector<int> > &A, const vector<int> &s, int k,
                                   pair<int, int> position, vector<pair<int, int> > &ans, vector<vector<bool> > &T) {
    if (k==s.size()) return true;
    if (A[position.first][position.second] != s[k]) return false;
    ans.push_back(position);
    T[position.first][position.second] = true;
    vector<pair<int, int> > D({{1,0}, {-1,0}, {0, 1}, {0, -1}});
    for (auto &d: D) {
        pair<int, int> next({position.first+d.first, position.second+d.second});
        if (isvalid(position, T)) {
            if (sequenceIn2DArr_helper(A, s, k+1, next, ans, T))
                break;
        }
    }
    ans.pop_back();
    T[position.first][position.second] = false;
    return false;

}

vector<pair<int, int> > Selftest::sequenceIn2DArr(const vector<vector<int> > &A, vector<int> &s) {
    for (int i=0; i<A.size(); i++) {
        for (int j=0; j<A.front().size(); j++) {
            vector<pair<int, int> > ans;
            pair<int, int> position({i, j});
            vector<vector<bool> > T(A.size(), vector<bool>(A.front().size(), false));
            if (sequenceIn2DArr_helper(A, s, 0, position, ans, T))
                return ans;
        }
    }
    return vector<pair<int, int> >();
}

void Selftest::bst_inorder_iterative(const shared_ptr<TNode> &root) {
    shared_ptr<TNode> curr;
    stack<shared_ptr<TNode> > S;
    while (curr || !S.empty()) {
        if (curr) {
            S.push(curr);
            curr = curr->left;
        } else {
            cout << S.top() << " ";
            S.pop();
            curr = curr->right;
        }

    }

}

void Selftest::bst_preorder_iterative(const shared_ptr<TNode> &root) {
    stack<shared_ptr<TNode> >S;
    if (root)
        S.emplace(root);
    while (!S.empty()) {
        auto curr = S.top();
        S.pop();
        cout << curr->data << " ";
        if (curr->right)
            S.emplace(curr->right);
        if (curr->left)
            S.push(curr->left);

    }

}

void Selftest::bst_postorder_iterative(const shared_ptr<TNode> &root) {
    stack<shared_ptr<TNode> > S;
    if (root)
        S.push(root);
    shared_ptr<TNode> prev;
    while (!S.empty()) {
        auto top = S.top();
        if (!top->left && !top->right || top->left==prev || top->right==prev) {
            cout << top->data << " ";
            S.pop();
        } else {
            if (top->right)
                S.push(top->right);
            if (top->left)
                S.push(top->left);
        }
        prev = top;

    }

}

void Selftest::bst_inorder_iterative_with_parentnode(const shared_ptr<TNode> &root){
    shared_ptr<TNode> prev=nullptr, next, curr=root;
    while (curr) {
        if (!prev || prev->left == curr || prev->right == curr) {
            if (curr->left)
                next = curr->left;
            else {
                cout << curr->data <<  " ";
                next = curr->right ? curr->right: curr->parent;
            }
        } else if (curr->left == prev) {
            cout << curr->data << " ";
            next = curr->right ? curr->right: curr->parent;
        } else {
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }

}

static bool isBST_helper(const shared_ptr<Selftest::TNode> &node, int minv, int maxv) {
    if (!node) return true;
    if (node->data < minv  || node->data >maxv)
        return false;
    return isBST_helper(node->left, minv, node->data) && isBST_helper(node->right, node->data, maxv);
}

bool Selftest::isBST(const shared_ptr<TNode> &root) {
    return isBST_helper(root, INT_MIN, INT_MAX);
}

bool Selftest::isBST_iterative(const shared_ptr<TNode> &root){
    stack<shared_ptr<TNode> > S;
    shared_ptr<TNode> curr=root;
    int prev = INT_MIN;

    while (curr || !S.empty()) {
        if (curr) {
            S.push(curr);
            curr = curr->left;
        } else {
            auto x = S.top();
            S.pop();
            if (x->data<prev)
                return false;
            prev = x->data;
            curr = curr->right;

        }
    }
    return true;
}

shared_ptr<Selftest::TNode> Selftest::fistAppearNode(const shared_ptr<TNode> & root, int k) {
    shared_ptr<TNode> curr = root, last=nullptr;
    while (curr) {
        int v = curr->data;
        if (v == k) {
            last = curr;
            curr = curr->left;
        } else if (v>k) {
            curr = curr->left;
        } else
            curr = curr->right;

    }
    return last;
}

bool Selftest::minBSTfind(const shared_ptr<TNode> &root, int k) {
    if (!root || root->data < k)
        return false;
    shared_ptr<TNode> curr = root;
    while (curr) {
        if (curr->data == k)
            return true;
        else if (k < curr->data )
            return false;
        else if (curr->right && k>=curr->right->data) {
            curr = curr->right;
        } else
            curr->left;
    }
    return false;
}

static shared_ptr<Selftest::TNode> bstTolist_helper(shared_ptr<Selftest::TNode> curr, bool right) {
    if (curr) return nullptr;
    auto leftnode = bstTolist_helper(curr->left, false);
    auto rightnode = bstTolist_helper(curr->right, true);

    if (leftnode) {
        leftnode->right = curr;
        curr->left = leftnode;
    }
    if (rightnode) {
        rightnode->left = curr;
        curr->right = rightnode;
    }
    if (right) {
        while (curr->left)
            curr = curr->left;
    } else {
        while (curr->right)
            curr = curr->right;
    }
    return curr;
}

shared_ptr<Selftest::TNode> Selftest::bstTolist(shared_ptr<TNode> &root) {
    return bstTolist_helper(root, true);
}

static void bstTolist_ncomplexity_helper(shared_ptr<Selftest::TNode> curr, shared_ptr<Selftest::TNode> prev, shared_ptr<Selftest::TNode> head) {
    if (curr) return;
    bstTolist_ncomplexity_helper(curr->left, prev, head);
    if (prev) {
        prev->right = curr;
        curr->left = prev;
    } else
        head = curr;
    prev = curr;
    bstTolist_ncomplexity_helper(curr->right, prev, head);
}

//complexity O(n) with call stack. Space O(h)
shared_ptr<Selftest::TNode> Selftest::bstTolist_ncomplexity(shared_ptr<TNode> &root) {
    shared_ptr<TNode> prevNode=nullptr, head=nullptr;
    bstTolist_ncomplexity_helper(root, prevNode, head);
    return head;
}

static shared_ptr<Selftest::TNode> listTobst_helper(shared_ptr<Selftest::TNode> &L, int s, int e) {
    shared_ptr<Selftest::TNode> curr = nullptr;
    if (s<e) {
        int m = s+((e-s)>>1);
        auto leftnode = listTobst_helper(L, s, m) ;
        curr = L;
        L = L->left;
        curr->right = leftnode;
        curr->left = listTobst_helper(L, m+1, e);
    }
    return curr;
}

shared_ptr<Selftest::TNode> Selftest::listTobst(shared_ptr<TNode> &head){
    int n=0;
    auto curr=head;
    while (curr) {
        n++;
        curr=curr->left;
    }
    return listTobst_helper(head, 0, n);
}

static void advance_app(shared_ptr<Selftest::TNode> &head, shared_ptr<Selftest::TNode> &tail, shared_ptr<Selftest::TNode> &node) {
    if (head)
    {   tail->right = node;
        node->left=tail;
    } else
        head = node;
    tail = node;
}

static void advance_app_ad(shared_ptr<Selftest::TNode> &head, shared_ptr<Selftest::TNode> &tail, shared_ptr<Selftest::TNode> &node) {
    advance_app(head, tail, node);
    node = node->right;
}

shared_ptr<Selftest::TNode> Selftest::merge2doubleList(shared_ptr<TNode> &A, shared_ptr<TNode> &B) {
    shared_ptr<TNode> head=nullptr, tail=nullptr;
    while (A && B) {
        advance_app_ad(head, tail, A->data < B->data ? A : B);
    }
    if (A) {
        advance_app(head, tail, A);
    } else if (B) {
        advance_app(head, tail, B);
    }
    return head;
}

static void bst_findKLargest_helper(shared_ptr<Selftest::TNode> &curr, vector<int> ans, int k) {
    if (!curr) return;
    bst_findKLargest_helper(curr->right, ans, k);
    ans.push_back(curr->data);
    if (ans.size()==k) return;
    bst_findKLargest_helper(curr->left, ans, k);
}

vector<int> Selftest::bst_findKLargest(shared_ptr<TNode> root, int k) {
    vector<int> ans;
    bst_findKLargest_helper(root, ans, k);
    return ans;
}

shared_ptr<Selftest::TNode> Selftest::LCA_iterative(const shared_ptr<TNode> &root, const shared_ptr<TNode> &a, const shared_ptr<TNode> &b) {
    pair<int, int> v = minmax(a->data, b->data);
    int s = v.first, e = v.second;
    shared_ptr<TNode> curr = root;
    while (curr->data < s)
        curr=curr->right;
    while (curr->data > e)
        curr= curr->left;
    return curr;

}

shared_ptr<Selftest::TNode> Selftest::build_bst_from_markedsequence_preorder(const vector<int> &A) {
    stack<shared_ptr<TNode> > S;
    for (auto it = A.rbegin(); it != A.rend(); it++) {
        int a = *it;
        if (!a) {
            S.push(nullptr);
        } else {
            auto right = S.top();
            S.pop();
            auto left = S.top();
            S.pop();
            shared_ptr<TNode> n(new TNode(a, left, right));
            S.push(n);
        }
    }
    return S.top();
}

shared_ptr<Selftest::TNode> Selftest::build_bst_from_markedsequence_postorder(const vector<int> &A) {
    stack<shared_ptr<TNode> > S;
    for (auto it = A.begin(); it != A.end(); it++) {
        int a = *it;
        if (!a) {
            S.push(nullptr);
        } else {
            auto right = S.top();
            S.pop();
            auto left = S.top();
            S.pop();
            shared_ptr<TNode> n(new TNode(a, left, right));
            S.push(n);
        }
    }
    return S.top();
}

static void print_middle(shared_ptr<Selftest::TNode> &root) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->data << endl;
    } else {
        print_middle(root->left);
        print_middle(root->right);
    }
}

static void print_left_middle(shared_ptr<Selftest::TNode> &curr) {
    if (!curr) return;
    cout << curr->data << " ";
    print_left_middle(curr->left);
    print_middle(curr->right);
}

static void print_middle_right(shared_ptr<Selftest::TNode> &curr) {
    if (!curr) return;
    print_middle(curr->left);
    print_middle_right(curr->right);
    cout << curr->data << " ";
}

void Selftest::print_envolope_bst(shared_ptr<TNode> &root){
    if (!root) return;
    cout << root->data << " ";
    print_left_middle(root->left);
    print_middle_right(root->right);
}

int Selftest::longestContinousSubArray(const vector<int> &A){
    unordered_set<int> S;
    for (auto &a: A)
        S.emplace(a);
    int maxL = 0;
    for (auto &s: S) {
        int i=1;
        while (S.find(s+i) != S.end()) {
            i++;
        }
        maxL = max(maxL, i);
    }
    return maxL;
}

int Selftest::maxSubArrSum(const vector<int> &A){
    int maxSum = 0, x=0;
    bool isNegative = true;
    for (auto &a: A) {
        if (a>=0) isNegative=false;
        x += a;
        maxSum = max(maxSum, x);
        x = max(0, x);
    }
    if (isNegative)
        maxSum = *(max_element(A.begin(), A.end()));
    return maxSum;
}

pair<int, int> Selftest::maxSubArray(const vector<int> &A) {
    pair<int, int> ans;
    if (A.empty()) return ans;
    if (A.size()==1) return {0, 0};
    int currMax=A[0], finalMax=INT_MIN;
    for (int i=1; i<A.size(); i++) {
        int curr = currMax + A[i];
        if (curr>currMax)
            currMax = curr;
        else {
            currMax = A[i];
            ans.first = i;
        }
        if (currMax>finalMax) {
            finalMax = currMax;
            ans.second = i;
        }
    }
    return ans;
}

pair<int, int> Selftest::longestSubArrLessK(const vector<int> &A, int k) {
    pair<int, int> ans(-1, -1), final(-1, -1);
    int curr=0;
    for (int i=0; i<A.size(); i++) {
        curr += A[i];
        if (curr<=k) {
            ans.second=i;
            if (ans.first==-1)
                ans.first=i;
        } else {
            if (final.first==-1 || ans.second-ans.first > final.second-final.first) {
                final = ans;
            }
            while (ans.first!=-1 && ans.first<=i && curr>k) {
                curr-=A[ans.first++];
            }
            if (ans.first==-1)
                curr=0;
        }
    }
    if (ans.second-ans.first > final.second-final.first)
        final = ans;
    return final;
}

// nonnegative integer seq
void Selftest::subArrayGivenSum(const vector<int> &A, int k){
    int sum=A[0], left=0, right=0;
    while (left<=right && right<A.size()) {
        if (sum==k) {
            cout << left << " " << right << endl;
            return;
        }
        else if (sum<k) {
            right++;
            sum += A[right];
        } else {
            sum -= A[left];
            left++;
        }
    }
    cout << "no found" << endl;
}

void Selftest::longestCommonSubstring(const string &x, const string &y) {
    vector<vector<int> > T(x.size(), vector<int>(y.size(), 0));
    for (int i=0; i<x.size(); i++) {
        for (int j=0; j<y.size(); j++) {
            if (x[i]==y[j]) {
                T[i][j] = (!i || !j) ? 1: T[i-1][j-1]+1;
            }
        }
    }
    int maxL =0;
    string str;
    for (int i=0; i<x.size(); i++) {
        for (int j=0; j<y.size(); j++) {
            if (maxL < T[i][j]) {
                maxL = T[i][j];
                str = x.substr(i-maxL+1, maxL);
            }
        }
    }
    cout << str << endl;

}

void Selftest::printUglyNumber(int k){
    set<int> T({1});
    vector<int> A({3,5,7});
    int i=0;
    while (i<k) {
        int x = *T.begin();
        cout << "Ugly: " << ++i << " " << x << endl;
        for (auto &a: A) {
            T.insert(x*a);
//            cout << x << " " << a << endl;
        }
        T.erase(x);

    }
}

bool static isValidmove(vector<vector<Selftest::Color> > &A, pair<int, int> &position, Selftest::Color &c) {
    int y = position.first, x=position.second;
    return y>0 && y<A.size() && x>0 && x<A.front().size() && A[y][x]!=c;
}

void Selftest::flip_color(vector<vector<Color> > &A, pair<int, int> &position, Color &c){
    if (A.empty()) return;
    vector<pair<int, int> > D({{1,0}, {-1, 0}, {0, 1}, {0, -1}});
    queue<pair<int, int> > Q;
    if (isValidmove(A, position, c))
        Q.push(position);
    while (!Q.empty()) {
        auto p = Q.front();
        Q.pop();
        A[p.first][p.second] = c;
        for (auto &d : D) {
            pair<int, int> next({p.first+d.first, p.second+d.second});
            if (isValidmove(A, next, c)) {
                Q.push(next);
            }
        }

    }
}

bool wordBreaking_helper(const string &s, int k, const unordered_set<string> &D, vector<string> &ans) {
    if (k==s.size())
        return true;
    for (int i=k+1; i<=s.size(); i++) {
        string sub = s.substr(k, i-k);
        if (D.find(sub) != D.end())  {
            ans.push_back(sub);
            if (wordBreaking_helper(s, i, D, ans))
                return true;
            ans.pop_back();
        }
    }
    return false;
}

vector<string> Selftest::wordBreaking(const string &s, unordered_set<string> &D) {
    vector<string> ans;
    wordBreaking_helper(s, 0, D, ans);
    return ans;
}

vector<string> Selftest::wordBreaking_iterative(const string &s, unordered_set<string> &D) {
    vector<string> ans;
    vector<int> T(s.size()+1, -1);
    T[0]=0;
    for (int i=1; i<=s.size(); i++) {
        for (int j=0; j<i; j++) {
            string sub = s.substr(j, i-j);
            if (T[j]!=-1 && D.find(sub)!=D.end() ){
                T[i] = i-j;
            }
        }
    }
    if (T.back()!=-1) {
        int t = s.size();
        int e = T.back();
        while (e>0) {
            ans.push_back(s.substr(t-e, e));
            t=t-e;
            e = T[t];
        }
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

void gene_helper(int n, int left, int right, vector<char> &ans) {
    if (right==n) {
        for (auto &c: ans)
            cout << c << " ";
        cout << endl;
    }
    if (left<n) {
        ans.push_back('(');
        gene_helper(n, left+1, right, ans);
        ans.pop_back();
    }
    if (right<left) {
        ans.push_back(')');
        gene_helper(n, left, right+1, ans);
        ans.pop_back();
    }
}
void Selftest::generateParentheses(int n) {
    vector<char> ans;
    int left=0, right=0;
    gene_helper(n, left, right, ans);
}

int Selftest::fibonacci(int n) {
    if (n<0) return -1;
    if (n<=1) return n;
    int x=0, y=1;

    int sum =0;
    for (int i=2; i<=n; i++) {
        sum = x+y;
        x=y;
        y=sum;
    }
    return sum;
}

void Selftest::unittest() {
    assert(fibonacci(-3)==-1);
    assert(fibonacci(0)==0);
    assert(fibonacci(1)==1);
    assert(fibonacci(10)==55);
    assert(fibonacci(10.5)==55);

    cout << "test is OK" << endl;
}

pair<int,int> Selftest::masterMind(string s, string d) {
    pair<int, int> ans;
    if (s.size()!=d.size()) return ans;
    unordered_map<char, int> T, D;
    int hit=0, pseudo_hit=0;
    for (int i=0; i<s.size(); i++) {
        char x=s[i];
        char y=d[i];
        if (x==y)
            hit++;
        else {
            if (T.find(x)==T.end())
                T[x]=1;
            else
                T[x]++;
            if (D.find(y)==D.end())
                D[y]=1;
            else
                D[y]++;
        }

    }
    for (auto itx=T.begin(); itx!=T.end(); itx++) {
        auto key = itx->first;
        if (D.find(key)!=D.end())
            pseudo_hit += min(itx->second, D[key]);

    }
    return {hit, pseudo_hit};
}

void Selftest::sortPartialSortedArr(vector<int> &A) {
    if (A.size()<=1) return;
    int l, r;
    int i;
    for (i=1; i<A.size(); i++) {
        if (A[i] < A[i-1]) {
            l=i;
            break;
        }
    }
    if (i==A.size()) return;
    for (i = A.size()-2; i>=0; i--) {
        if (A[i]>A[i+1]) {
            r = i;
            break;
        }
    }
    int left=min(l,r);
    int right=max(l, r);
//    cout << "left, right:" << left << " " << right << endl;
    int maxv=numeric_limits<int>::min(), minv=numeric_limits<int>::max();
    for (i=left; i<=right; i++) {
        maxv = max(maxv, A[i]);
        minv = min(minv, A[i]);
    }
    pair<int, int> ans{-1, -1};
    for (i =0; i<left; i++) {
        if (A[i]>minv)
            break;
    }
    ans.first = i;
    for (i=A.size()-1; i> right; i--) {
        if (A[i]<maxv)
            break;
    }
    ans.second = i;
    cout << ans.first << " " << ans.second << endl;

}

void optimalParse_helper(const string s, unordered_set<string> &D, int k, int illegal, int minV, vector<string> &currpath, vector<string> &best) {
    if (k==s.size()) {
        if (illegal<minV) {
            minV=illegal;
            best = currpath;
        }
        return;
    }
    if (illegal>minV) return;
    for (int i=k+1; i<=s.size(); i++) {
        string next = s.substr(k, i-k);
        int n=0;
        if (D.find(next) == D.end())
            n=1;
        currpath.push_back(next);
        optimalParse_helper(s, D, i, illegal+n, minV, currpath, best);
        currpath.pop_back();
    }

}

void Selftest::optimalParse(const string s, unordered_set<string> &D) {
    vector<string> path;
    vector<string> best;
    optimalParse_helper(s, D, 0, 0, INT_MAX, path, best);

}

int Selftest::add_noplus(int x, int y){
    if (!y) return x;
    int sum = x^y;
    int carry = (x&y)<<1;
    return add_noplus(sum, carry);
}

static int zero_one_generator() {
    return 1;
}

int Selftest::generateRandom_a_b(int a, int b){
    int res=0, len=b-a+1;
    do {
        res=0;
        for (int i=0; (1<<i)<len; i++) {
            res = res<<1 | zero_one_generator();
        }
    } while (res>=len);
    return a+res;
}

double Selftest::generateRandFromProb(const vector<double> &A, const vector<double> &prob){
    vector<double> psum;
//    partial_sum(prob.begin(), prob.end(), psum, [](const double &x, const double &y){return x+y;});
    partial_sum(prob.begin(), prob.end(), back_inserter(psum));
    auto it = upper_bound(psum.begin(), psum.end(), zero_one_generator());
    int i = distance(psum.begin(), it);
    return A[i-1];

}

static void add_move(shared_ptr<Selftest::Node> &head, shared_ptr<Selftest::Node>&tail, shared_ptr<Selftest::Node>&node) {
    head ? tail->next = node : head = node;
    tail=node;
}

shared_ptr<Selftest::Node> Selftest::addition_signficantLast(const shared_ptr<Node> &a, const shared_ptr<Node> &b){
    shared_ptr<Node> head=nullptr, tail=nullptr, curr_a=a, curr_b=b;
    int carry=0;
    while (curr_a || curr_b || carry) {
        int sum = carry;
        if (curr_a) {
            sum += curr_a->data;
            curr_a = curr_a->next;
        }
        if (curr_b) {
            sum +=curr_b->data;
            curr_b = curr_b->next;
        }
        carry = sum>10 ? 1: 0;
        sum %= 10;
        shared_ptr<Node> node(new Node(sum));
        add_move(head, tail, node);
    }
    return head;
}

static void addition_signficantFirst_helper(shared_ptr<Selftest::Node> &head, shared_ptr<Selftest::Node> &tail, shared_ptr<Selftest::Node> &curr_a, shared_ptr<Selftest::Node> &curr_b, int carry){
    if (!curr_a && !curr_b &&!carry) return;
    int sum = carry;
    if (curr_a) {
        sum += curr_a->data;
        curr_a = curr_a->next;
    }
    if (curr_b) {
        sum +=curr_b->data;
        curr_b = curr_b->next;
    }
    carry = sum>10 ? 1: 0;
    sum %=10;
    shared_ptr<Selftest::Node> node(new Selftest::Node(sum));
    add_move(head, tail, node);
    addition_signficantFirst_helper(head, tail, curr_a, curr_b, carry);
}

static int computeLen(const shared_ptr<Selftest::Node> &a) {
    shared_ptr<Selftest::Node> curr = a;
    int len=0;
    while(curr) {
        len++;
        curr=curr->next;
    }
    return len;
}

static shared_ptr<Selftest::Node> add_front_node(const shared_ptr<Selftest::Node> &a, int diff) {
    shared_ptr<Selftest::Node> curr= a;
    for (int i=0;i<diff; i++) {
        shared_ptr<Selftest::Node> n(new Selftest::Node(0));
        n->next = curr;
        curr = n;
    }
    return a;
}

shared_ptr<Selftest::Node> Selftest::addition_signficantFirst(const shared_ptr<Node> &a, const shared_ptr<Node> &b){
    shared_ptr<Selftest::Node> curr_a=a, curr_b=b, head=nullptr, tail=nullptr;
    int len_a = computeLen(a);
    int len_b = computeLen(b);
    int diff = abs(len_a-len_b);
    if (diff) {
        if (len_a>len_b)
            curr_b = add_front_node(b, diff);
        else
            curr_a = add_front_node(a, diff);
    }
    int carry=0;
    addition_signficantFirst_helper(head, tail, curr_a, curr_b, carry);
}

shared_ptr<Selftest::Node> Selftest::find_start_cyclic_list(const shared_ptr<Node> &a) {
    shared_ptr<Node> slow = a, fast = a;
    while(fast) {
        fast = fast->next;
        if (slow==fast)break;
        if (fast) {
            slow=slow->next;
            fast = fast->next;
        }
    }
    if (!fast) return nullptr;
    slow = a;
    while (slow!=fast) {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}

// 2 solution: 1. compare the reversed list, 2. use stack
bool Selftest::isPalindrome(const shared_ptr<Node> &a){
    stack<int> S;
    shared_ptr<Node> slow=a, fast=a;
    while(fast && fast->next) {
        S.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast)
        slow = slow->next;
    while (slow) {
        if (slow->data != S.top())
            return false;
        S.pop();
        slow = slow->next;
    }
    return true;

}

shared_ptr<Selftest::Node> Selftest::reverseList(shared_ptr<Node> &n){
    shared_ptr<Node> head=nullptr, curr=n;
    while (curr) {
        auto next = curr->next;
        curr->next = head;
        head=curr;
        curr=next;
    }
    return head;
}

static void print_list(const shared_ptr<Selftest::Node> &head) {
    shared_ptr<Selftest::Node> curr = head;
    while(curr){
        cout << curr->data << " ";
        curr=curr->next;
    }
    cout << endl;
}

void Selftest::test_reverseList(vector<int> &A){
    shared_ptr<Node> head=nullptr, tail=nullptr;
    for (auto &a: A) {
        shared_ptr<Node> node(new Node(a));
        if (head) {
            tail->next=node;
        } else
            head = node;
        tail = node;
    }
    print_list(head);
    auto n = reverseList(head);
    print_list(n);

}

static void moveTo(stack<int> &S, int x) {
    if (S.empty()) {
        S.push(x);
    } else {
        int top = S.top();
        if (x>top){
            S.push(x);
        } else {
            int y = top;
            S.pop();
            moveTo(S, x);
            S.push(y);
        }
    }
}

void Selftest::sortStack(stack<int> &S){
    if (S.empty()) return;
    int top = S.top();
    S.pop();
    sortStack(S);
    moveTo(S, top);
//    if (!S.empty()) {
//        if (top>S.top())
//            S.push(top);
//        else {
//            int x = S.top();
//            S.pop();
//            moveTo(S, top);
//            S.push(x);
//        }
//    } else
//        S.push(top);
}

void Selftest::test_sortStack(vector<int> &A) {
    stack<int> S;
    for (auto &a: A)
        S.push(a);
    sortStack_additionStack_iterative(S);
    while(!S.empty()) {
        cout << S.top() << endl;
        S.pop();
    }

}

void Selftest::sortStack_additionStack_iterative(stack<int> &S){
    stack<int> T;
    while (!S.empty()) {
        int x = S.top();
        S.pop();
        while(!T.empty() && x < T.top()) {
            S.push(T.top());
            T.pop();
        }
        T.push(x);
    }
    S=T;
}

shared_ptr<Selftest::TNode> createTreeFromArray_helper(vector<int> &A, int s, int e) {
    if (s>=e)return nullptr;
    int m = s + ((e-s)>>1);
    auto left = createTreeFromArray_helper(A, s, m);
    shared_ptr<Selftest::TNode> node(new Selftest::TNode(A[m]));
    node->left = left;
    node->right = createTreeFromArray_helper(A, m+1, e);
    return node;

}

shared_ptr<Selftest::TNode> Selftest::createTreeFromArray(vector<int> &A){
    return createTreeFromArray_helper(A, 0, A.size());
}

shared_ptr<Selftest::TNode> Selftest::nextNode(shared_ptr<TNode> &n){
    if (!n) return nullptr;
    if (!n->parent || n->right) {
        n=n->right;
        if (!n) return nullptr;
        while (n->left)
            n = n->left;
        return n;
    } else {
        while (n && n->parent && n->parent->right == n ) {
            n = n->parent;
        }
        return n;
    }

}

shared_ptr<Selftest::TNode> Selftest::LCA_again(shared_ptr<TNode> &root, shared_ptr<TNode> &a, shared_ptr<TNode> &b) {
    if (!root) return nullptr;
    if (root==a || root==b)
        return root;
    auto left = LCA_again(root->left, a, b);
    auto right = LCA_again(root->right, a, b);
    if (left && right)
        return root;
    if (left)
        return left;
    else
        return right;
}

void findSumPath_helper(shared_ptr<Selftest::TNode> &curr, int k, vector<int> &path, int sum) {
    if (sum==k) {
        copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        return;
    }
    if (!curr) return;
    path.push_back(curr->data);
    sum += curr->data;
    findSumPath_helper(curr->left, k, path, sum);
    findSumPath_helper(curr->right, k, path, sum);
    vector<int> another;
    findSumPath_helper(curr->left, k, another, 0);
    findSumPath_helper(curr->right, k, another, 0);
}

void Selftest::findSumPath(shared_ptr<TNode> &root, int k){
    vector<int> path;
    findSumPath_helper(root, k, path, 0);

}

int getDepth(shared_ptr<Selftest::TNode> &curr) {
    int len_left, len_right;
    len_left = getDepth(curr->left);
    len_right = getDepth(curr->right);
    return max(len_left, len_right)+1;
}

void findSumPath_arr_helper(shared_ptr<Selftest::TNode> &curr, int k, vector<int> &path, int level){
    if(!curr) return;
    path[level] = curr->data;
    int sum = 0;
    for (int i=level; i>=0; i--) {
        sum += path[i];
        if (sum==k){
            copy(path.begin()+i, path.begin()+level+1, ostream_iterator<int>(cout, " "));
            cout << endl;
        }
    }
    findSumPath_arr_helper(curr->left, k, path, level+1);
    findSumPath_arr_helper(curr->right, k, path, level+1);
}

void Selftest::findSumPath_arr(shared_ptr<TNode> &root, int k){
    int len = getDepth(root);
    vector<int> path(len, 0);
    findSumPath_arr_helper(root, k, path, 0);
}

int Selftest::insertBit(int n, int m, int i, int j) {
    cout << bitset<32>(n) << " " << bitset<32>(m) << endl;
    int mask = ((1<<(j+1))-1)^ ((1<<i)-1);
    mask = ~mask;
    cout << bitset<32>(mask) << endl;
    n &= mask;
    m = m<<i;
    cout<< bitset<32>(m) << endl;
    cout << bitset<32>(n|m) << endl;
    return n|m;
}

string processInt(int x) {
    if (x==0) return "0";
    stringstream y;
    while (x) {
        y<<(x&1);
        x = x>>1;
    }
    string ans = y.str();
    reverse(ans.begin(), ans.end());
    return ans;
}

string Selftest::printBinary(double x){
    stringstream ans;
    bool negative=false;
    if (x<0) {
        negative=true;
        x=-x;
    }
    string integ = processInt(int(x));
    x -=int(x);
    while (x) {
        x*=2;
        if (x>=1) {
            ans<<1;
            x-=1;
        }
        else
            ans<<0;
        if (ans.str().size()>=32)
            break;
        cout << x << endl;
    }
    string result = integ + "." +ans.str();
    return negative? "-" + result :  result;
}

void traverseC(shared_ptr<Selftest::TNode> &root)
{
  if (!root->left && !root->right) //bottom reached
    cout << root->data << " ";
  else
  {
    if (root->left ) traverseC(root->left );
    if (root->right) traverseC(root->right);
  }
}

void traverseL(shared_ptr<Selftest::TNode> &root)
{
  cout << root->data << " ";
  if (root->left ) traverseL(root->left ); //still in outer left
  if (root->right) traverseC(root->right);
}

void traverseR(shared_ptr<Selftest::TNode> &root)
{
  if (root->left ) traverseC(root->left );
  if (root->right) traverseR(root->right); //still in outer right
  cout << root->data << " ";
}

void traverse(shared_ptr<Selftest::TNode> &root)
{
  if (!root) return;
  cout << root->data << " ";
  if (root->left ) traverseL(root->left ); //special function for outer left
  if (root->right) traverseR(root->right); //special function for outer right
}

int Selftest::largestSubSquare(const vector<vector<int> > &A){
    vector<vector<int> > T(A.size(), vector<int>(A.front().size(), 0));
    for (int y=0; y<A.size(); y++) {
        for (int x=0; x<A.front().size(); x++) {
                T[y][x] = y>0 ? T[y-1][x]:0 + x>0 ? T[y][x-1] : 0 + A[y][x]- y>0&&x>0 ? T[y-1][x-1]:0;
        }
    }
    int maxArea=INT_MIN;
    for (int y=-1; y<A.size()-1; y++) {
        for (int x = -1; x<A.front().size()-1; x++) {
            for (int y2 = y+1; y2<A.size(); y2++) {
                for (int x2=x+1; x2<A.front().size(); x2++) {
                    int area = T[y2][x2] - x>-1 ? T[y2][x]:0 - y>-1? T[y][x2]:0 + x>-1&&y>-1?T[y][x]:0;
                    maxArea = max(area, maxArea);
                }
            }
        }
    }
    return maxArea;
}


int Selftest::largestSubSquare_n3(const vector<vector<int> > &A){
    vector<vector<int> > T(A.size(), vector<int>(A.front().size(), 0));
    for (int y=0; y<A.size(); y++) {
        for (int x=0; x<A.front().size(); x++) {
                T[y][x] = y>0 ? T[y-1][x]:0 + A[y][x];
        }
    }
    int maxArea=INT_MIN;
    for (int y=-1; y<A.size()-1; y++) {
            for (int y2 = y+1; y2<A.size(); y2++) {
                vector<int> B(A.front().size(), 0);
                for (int x=0; x<A.front().size(); x++) {
                    B[x] = T[y2][x] - y>0 ? T[y][x]:0;
                }
                int curr = maxSubArrSum(B);
                maxArea = max(maxArea, curr);
            }
    }
    return maxArea;
}

bool Selftest::abs_sorted_sum3(const vector<int> &A, int k){
    if (A.empty()) return false;
    int s=0, e=A.size()-1;
    // for positive
    while(s<e) {
        while (A[s]<0)
            s++;
        while (A[e]<0)
            e--;
        if (s<e) {
            int v = A[s]+A[e];
            if (v==k)
                return true;
            else if (v>k)
                e--;
            else
                s++;
        }
    }
    s=0;
    e=A.size()-1;
    while(s<e) {
        while (A[s]>0)
            s++;
        while (A[e]>0)
            e--;
        if (s<e) {
            int v = A[s]+A[e];
            if (v==k)
                return true;
            else if (v<k)
                e--;
            else
                s++;
        }
    }
    s=A.size()-1;
    e=A.size()-1;
    while(s>=0 && e>=0) {
        while (A[s]<0)
            s--;
        while (A[e]>0)
            e--;
        if (s>0 && e>=0) {
            int v = A[s]+A[e];
            if (v==k)
                return true;
            else if (v<k)
                e--;
            else
                s--;
        }
    }
    return false;

}

int Selftest::largest_rect_arr(const vector<int> &A) {
    stack<int> S;
    vector<int> L;
    for (int i=0; i<A.size(); i++) {
        while (!S.empty() && A[S.top()]>=A[i])
            S.pop();
        L.emplace_back(S.empty() ? -1: S.top());
        S.push(i);
    }
    S=stack<int>();
    vector<int> R(A.size(), 0);
    for (int i=A.size()-1; i>=0; i--) {
        while(!S.empty() && A[S.top()]>=A[i])
            S.pop();
        R[i] = S.empty()? A.size(): S.top();
        S.push(i);
    }
    int maxRect=0;
    for (int i=0; i<A.size(); i++) {
        maxRect = max(maxRect, A[i]*(R[i]-L[i]-1));
//        int minV = min(A[i], (R[i]-L[i]-1)); // this code is for max square;
//        maxRect = max(maxRect, minV*minV);
    }
    return maxRect;
}

int Selftest::largest_rect_2Dmatrix(const vector<vector<int> > &A){
    vector<vector<int> > B(A.size(), vector<int>(A.front().size()));
    for (int i=0; i< A.size(); i++) {
        for (int j=0; j<A.front().size(); j++) {
            B[i][j]=A[i][j]? i>=1? B[i-1][j]+1:1: 0;
        }
    }
    int maxRect=0;
    for (int i=0; i<A.size(); i++) {
        maxRect = max(maxRect, largest_rect_arr(B[i]));
    }
    return maxRect;
}

int Selftest::compute_binomial_coefficients(int n, int k){
    if (n<k) return -1;
    vector<vector<int> > B(n+1, vector<int>(k+1, 0));
    for (int i=0; i<=n; i++) {
        B[i][0]=1;
        if (i<=k)
            B[i][i]=1;
    }
    for (int i=2; i<=n; i++ ) {
        for (int j=1; j<i && j<=k; j++) {
            B[i][j] = B[i-1][j] + B[i-1][j-1];
        }
    }
    return B[n][k];
}

bool Selftest::findPairWithSum_unsorted(const vector<int> &A, int sum) {
    unordered_set<int> T;
    for (auto &a: A) {
        if (T.find(sum-a) != T.end())
            return true;
        T.insert(a);
        
    }
    return false;

}

bool comp_string_helper(const string &a, const string &b, int i) {
    if (i==a.size()) return false;
    return a[i] == b[i] ? comp_string_helper(a, b, i+1) : a[i]<b[i];
}

bool comp_string(const string &a, const string &b) {
    return a.size()==b.size() ? comp_string_helper(a, b, 0): a.size()<b.size();
}

void Selftest::bigNumberSort(vector<string> &A){
    sort(A.begin(), A.end(), comp_string);
    copy(A.begin(), A.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

void Selftest::stableSort(vector<pair<int, string> > &A) {
    vector<pair<int, int> > B;
    for(int i=0; i<A.size(); i++) {
        B.emplace_back(i, A[i].first);
    }
    sort(B.begin(), B.end(), [](const pair<int, int> &a, const pair<int, int> &b) { return a.second==b.second ? a.first<b.first : a.second < b.second;});
    vector<pair<int, string> > C;
    for (int i=0; i<A.size(); i++) {
        C.emplace_back(B[i].second, A[B[i].first].second);
    }
}
