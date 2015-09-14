#include "meta.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <iterator>
#include <unordered_map>
#include <stdexcept>
#include <queue>
#include <set>
//#include <unordered_set>

atomic<int> Meta::Box::count(0);

Meta::Meta()
{
}

static bool isTutorAvailable(int r, list<Meta::Tutor> & tutors) {
    for (auto it=tutors.begin(); it != tutors.end(); it++) {
        if (r-it->start>120) {
            tutors.erase(it);
        } else if (r-it->startLesson>30) {
            it->startLesson = r;
//            tutors.erase(it);
//            tutors.emplace_back(Meta::Tutor(r,r));
            return true;
        }
    }
    return false;
}

static bool comp_sidx(const pair<int, int> &x, const pair<int, int> &y) {
    return x.second > y.second;
}

vector<vector<bool> > Meta::jobAssignment_clientsSevers(const vector<int> &T, const vector<int> &S) {
    int nTask = accumulate(T.begin(), T.end(), 0);
    int nS = accumulate(S.begin(), S.end(), 0,
                        [&T](const int &x, const int &y){return x+min(y, (int)T.size());});
    if (nS<nTask || *max_element(T.begin(), T.end()) > S.size())
        return vector<vector<bool> >();

    vector<pair<int, int> > s_idx, t_idx;
    for (int i=0; i<S.size(); i++)
        s_idx.emplace_back(i, S[i]);
    for (int i=0; i<T.size(); i++)
        t_idx.emplace_back(i, T[i]);
    vector<vector<bool> > X(T.size(), vector<bool>(S.size(), false));
    sort(s_idx.begin(), s_idx.end(), comp_sidx);
    for (int i=0; i<s_idx.size(); i++) {
        if (s_idx[i].second<T.size()) {
            nth_element(t_idx.begin(), t_idx.begin()+s_idx[i].second, t_idx.end(), comp_sidx);
        }
        int size = min(s_idx[i].second, (int)T.size());
        for (int j=0; j<size; j++) {
            if (t_idx[j].second) {
                X[t_idx[j].first][s_idx[i].first]=true;
                t_idx[j].second--;
                nTask--;
            }
        }
    }
    if (nTask)
        return vector<vector<bool> >();
    for (auto t: X) {
        copy(t.begin(), t.end(), ostream_iterator<bool>(cout, " "));
        cout << endl;
    }
    return X;

}

int Meta::min_tutor(vector<int> requests) {
    // here are not correct number;
    int daystart=9, dayend=5;
    sort(requests.begin(), requests.end());
    list<Tutor> tutors;
    int maxNum=0;
    for (auto &r : requests) {
        if (r <daystart || r>dayend)
            continue;
        if (!tutors.empty() && isTutorAvailable(r, tutors))
            continue;
        else {
            tutors.emplace_back(Tutor(r, r));
            maxNum = max(maxNum, (int)tutors.size());
        }
    }
    return maxNum;
}

static bool greedyAssign(const vector<int> &F, int nServer, int limit, vector<int> &A) {
    int n=-1;
    int sum=0;
    for (auto &f : F) {
        if (n==-1 || sum+f>limit){
            if (++n>=nServer)
                return false;
            sum=f;
        }
        else {
            sum+=f;
        }
        A[n] = sum;
    }
    return true;
}

vector<int> Meta::loadBalance(const vector<int> &F, int nServer) {
    int total = accumulate(F.cbegin(), F.cend(), 0);
    int s=0, e=total;
    vector<int> ret;
    while (s<=e) {
        int m=s+((e-s)>>1);
        vector<int> A(nServer, 0);
        bool isFeasible = greedyAssign(F, nServer, m, A);
        if (isFeasible){
            ret=A;
            e=m-1;
        } else
            s=m+1;
    }
    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return ret;
}

static bool stringConstruct_helper(string &s, const unordered_set<string> &D, vector<bool> &table, int len,
                                   vector<int> &L) {
    if (len==s.size())
        return true;
    if (len>s.size() || table[len]==false)
        return false;
    for (int i=1; i<=s.size()-len; i++){
        if (D.find(s.substr(len, i))!=D.end() && stringConstruct_helper(s, D, table, len+i, L)) {
            L[len]=i;
            return true;
        }
    }
    table[len]=false;
    return false;
}

bool Meta::stringConstruct(string s, const unordered_set<string> &D) {
    vector<bool> Q(s.size(), true);
    vector<int> L(s.size(), 0); // store the length of word
    if (stringConstruct_helper(s, D, Q, 0, L)) {
        int i=0;
        while (i<s.size()) {
            cout << s.substr(i, L[i]) << " ";
            i += L[i];
        }
        return true;
    }
    else return false;
}

int maxSubarrayInCyclicArray_helper(const vector<int> &D, const int& (*comp)(const int &, const int &), int init) {
    int till=0, overall=init;
    for (auto &d : D) {
        till = comp(d, d+till);
        overall = max(till, overall);
    }
    return overall;
}

int Meta::maxSubarrayInCyclicArray(const vector<int> &A) {
    return max(maxSubarrayInCyclicArray_helper(A, max, INT_MIN),
               accumulate(A.begin(), A.end(), 0)-maxSubarrayInCyclicArray_helper(A, min, INT_MAX));
}

//struct CompList {
//    bool operator()(const list<int> &a, const list<int> &b) const {
//        return a.size() < b.size();
//    }
//};

list<int> Meta::min_expression_seq(int n) {
    if (n<1)
        throw invalid_argument("input is less than 1");
    if (n==1)
        return list<int>({1});
    queue<list<int> > Q;
//    set<list<int>, CompList> Q;
    Q.push({1});

//    Q.push(list<int>({1}));

    while (!Q.empty()) {
        auto x = Q.front();
        Q.pop();
        for (auto &m : x) {
            int sum = m+x.back();
            list<int> newlist(x);
            newlist.push_back(sum);
            copy(newlist.begin(), newlist.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
            if (sum==n) {
                return newlist;
            }
            else if (sum>n) {
                break;
            }
            Q.push(newlist);
        }
    }
}

bool Meta::check_Collatz(int n) {
    if (n<=0) {
        throw std::invalid_argument("input is less than or equal 0");
    }
    if (n==1)
        return true;

    unordered_set<long long> table;
    for (long i=2; i<=n; i++) {
        long test_i=i;
        unordered_set<long long> seq;
        while(test_i>=i) {
            if (!seq.emplace(test_i).second)
                return false;
            if (!table.emplace(test_i).second)
                return true;
            if (test_i &1) {
                long long next = 3*test_i+1;
                if (next<test_i)
                    throw overflow_error("test process overflow");
                test_i = next;
            } else {
                test_i = test_i>>1;
            }
        }
        // that is for save space because i has been test and next one will bigger that this.
        table.erase(i);
    }
    return true;
}

bool check_Collatz_recursive_helper(int curr, int k, unordered_set<long long> &sequence,
                                    unordered_set<long long> &table) {
    if (curr<k || curr==1)
        return true;
    if (!sequence.emplace(curr).second)
        return false;
    if (!table.emplace(curr).second)
        return true;

    if (curr & 1) {
        long long next = curr*3 +1;
        if (next < curr)
            throw overflow_error("test process overflow");
        return check_Collatz_recursive_helper(next, k, sequence, table);
    } else {
        return check_Collatz_recursive_helper(curr>>1, k, sequence, table);
    }

}

bool Meta::check_Collatz_recursive(int n) {
    if (n<1)
        throw invalid_argument("input is less than 1");

    unordered_set<long long> table;
    for (int i=1; i<=n; i++) {
        try {
        unordered_set<long long> sequence;
        if (!check_Collatz_recursive_helper(i, i, sequence, table))
            return false;
        table.erase(i);
        } catch (exception &e) {
            throw e;
        }
    }
    return true;
}

static bool isValid_sudoku(vector<vector<int> > &G, int i, int j, int value) {
    //check row
    for (int k=0; k<G.size(); k++) {
        if (G[k][j] == value)
            return false;
    }
    for (int k=0; k<G.front().size(); k++) {
        if (G[i][k] == value)
            return false;
    }
    int region=sqrt(G.size());
    int I=i/region, J=i/region;
    for (int m=0; m<region; m++)
        for (int n=0; n<region; n++) {
            if (G[region*I+m][region*J+n]==value)
                return false;
        }
    return true;
}

static bool solve_Sudoku_helper(vector<vector<int> > &G, int i, int j) {
    if (i==G.size()) {
        i=0;
        if (++j==G[i].size())
            return true;
    }

    if (G[i][j]!=0) // no empty
        return solve_Sudoku_helper(G, i+1, j);

        for (int value=1; value<=G.size(); value++) {
            if (isValid_sudoku(G, i, j, value)) {
//                cout << i << "," << j << ":" << G[i][j] << "->" << value << endl;
                G[i][j]=value;
//                    for (int i=0; i<G.size(); i++){
//                        copy(G[i].begin(), G[i].end(), ostream_iterator<int>(cout, " "));
//                        cout << endl;
//                    }
//                cin.get();
                if (solve_Sudoku_helper(G, i+1, j))
                    return true;
                G[i][j]=0;
            }
        }
        return false;
}

bool Meta::solve_Sudoku(vector<vector<int> > &G) {
//    for (int i=0; i<G.size(); i++){
//        copy(G[i].begin(), G[i].end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//    }

    if (solve_Sudoku_helper(G, 0, 0)) {
        for (int i=0; i<G.size(); i++){
            copy(G[i].begin(), G[i].end(), ostream_iterator<int>(cout, " "));
            cout << endl;
        }
        return true;
    } else {
        cout << "No solution exists" << endl;
        return false;
    }

}

static bool fillMilk_helper(const vector<Meta::Jug> &J, int L, int H,
                            unordered_set<pair<int, int>, Meta::PairHash, Meta::PairEqual > &table,
                            vector<Meta::Jug> & path) {
    if (L>H || L<0 || H <0 || table.find(pair<int, int>(L, H)) != table.end())
        return false;
    for (auto &x : J) {
        path.push_back(x);
        if (x.low>=L && x.high<=H ) {
            for (auto &t: path)
                cout << t.low << "-" << t.high << endl;
            cout << endl;
            return true;
        }
        else if ( fillMilk_helper(J, L-x.low, H-x.high, table, path))
            return true;
        path.pop_back();
    }
    table.emplace(L, H);
    return false;
}

bool Meta::fillMilk(const vector<Jug> &J, int L, int H) {
    unordered_set<pair<int, int>, PairHash, PairEqual > table;
    vector<Jug> path;
    return fillMilk_helper(J, L, H, table, path);
}

int Meta::maxRodCutting(int len, vector<int> &table) {
    vector<int> res(len+1, 0);
    for (int i=1; i<=len; i++) {
        for (int j=1; j<table.size(); j++) {
            res[i] = max(res[i], (i-j< 0 ? 0: res[i-j]+table[j]));
            cout << i << "," << j << ":" ;
            for (auto &x: res)
                cout << x << ",";
            cout << endl;
        }
    }
    return res.back();
}

int Meta::coins_game(vector<int> &C, int a, int b, vector<vector<int> > &T) {
    if (a>b)
        return 0;
    if (T[a][b]==-1) {
        T[a][b]=max(C[a]+min(coins_game(C, a+1, b-1, T), coins_game(C, a+2, b, T)),
                    C[b]+min(coins_game(C, a+1, b-1, T), coins_game(C, a, b-2, T)));
    }
    return T[a][b];
}

int Meta::max_fish(vector<vector<int> > &A) {
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A[i].size(); j++)
            A[i][j] += max(i<1 ? 0 : A[i-1][j],  j<1 ? 0 : A[i][j-1]);
    return A.back().back();
}

int Meta::compute_binomial_coefficients(int n, int k) {
    vector<vector<int> > table(n+1, vector<int>(k+1, 0));
    for (int i=0; i<=k; i++) {
//        table[0][k]=1;
        table[i][i]=1;
    }
    for (int i=0; i<=n; i++)
        table[i][0]=1;

    for (int i=1; i<=n; i++)
        for (int j=1; j<i && j<=k; j++) {
            table[i][j]=table[i-1][j]+table[i-1][j-1];
        }
    return table[n][k];
}

int Meta::score_combination(int k, vector<int> &scores) {
    if (k==0) return 0;
    vector<int> table(k+1, 0);
    table[0]=1;
    for (auto & s: scores) {
        for (int i=1; i<=k; i++) {
            table[i] += i<s ? 0 : table[i-s];
        }
    }
    table.back();
}

int Meta::score_permutation(int k, vector<int> &scores) {
    if (k==0) return 0;
    vector<int> table(k+1, 0);
    table[0]=1;
    for (int i=1; i<=k; i++) {
        for (auto & s: scores) {
            table[i] += i<s?0:table[i-s];
        }
    }
    table.back();

}

int Meta::calc_ways_walk_in2darray_obstacle(const vector<vector<int> > &B){
    if (B.empty() || B[0][0]==1) return 0;

    vector<vector<int> > A(B.size(), vector<int>(B.front().size(), 0));
    A[0][0]=1;

    for (int i=0; i<B.size(); i++)
        for (int j=0; j<B.front().size(); j++) {
            if (B[i][j]==0)
                A[i][j]+=i<1?0:A[i-1][j]+j<1?0:A[i][j-1];
        }

    return A.back().back();

}

int Meta::calc_ways_walk_in2darray(int n, int m) {
    vector<int> A(m, 0);
    A[0]=1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
                A[j] += (j<1 ? 0:A[j-1]);
        }
        for (auto &x : A)
            cout << x << " ";
        cout << endl;
    }
    return A.back();

}

int Meta::find_pretty_print(const vector<string> &words, int L) {
    vector<int> M(words.size(), numeric_limits<int>::max());
    for (int i=0; i<words.size(); i++) {
        int ben=L-words[i].size();
        M[i]=min(i-1<0 ? 0 : M[i-1]+(1<<ben), M[i]);
        for (int j=i-1; j>=0; j--) {
            ben -= words[j].size()+1;
            if (ben<0)
                break;
            M[i]=min(j-1<0 ? 0 : M[j-1]+(1<<ben), M[i]);
        }
    }
    // consider the last line
   int  min_mess = words.size()>=2 ? M[words.size()-2] : 0;
    int ben=L-words.back().size();
    for (int j=words.size()-2; j>=0; j--) {
        ben -= words[j].size()+1;
        if (ben<0)
            return min_mess;
        min_mess=min(min_mess, j-1<0 ? 0 : M[j-1]);
    }
    return min_mess;
}

vector<string> Meta::word_breaking(string s, unordered_set<string> &dict) {
    vector<int> T(s.size(), 0);
    for (int i=0; i<s.size(); i++) {
        if (dict.find(s.substr(0, i+1)) != dict.end())
            T[i]=i+1;

        for (int j=0; j<i && T[i]==0; j++) {
            if (T[j] && dict.find(s.substr(j+1, i-j)) != dict.end())
                T[i]=i-j;
        }
    }
    vector<string> res;
    if (T.back()) {
        int idx=s.size()-1;
        while (idx>=0) {
            res.push_back(s.substr(idx-T[idx]+1, T[idx]));
            idx-=T[idx];
        }
        reverse(res.begin(), res.end());
    }
    return res;
}

vector<string> Meta::word_breaking_better(string s, unordered_set<string> &dict) {
    vector<int> M(s.size()+1, -1);
    M[0]=0;
    for (int i=1; i<=s.size(); i++)
        for (int j=0; j<i; j++) {
            if (M[j]!=-1 && dict.find(s.substr(j, i-j))!=dict.end()) {
                M[i]=i-j;
//                cout << i << " " << i-j << " " << M[i] << endl;
                break;
            }
        }
//    copy(M.begin(), M.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
    vector<string> ret;
    if (M.back()!=-1) {
        int k=s.size();
        while (k){
            ret.emplace_back(s.substr(k-M[k], M[k]));
            k-=M[k];
        }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int Meta::levenshtein_distance(string A, string B) {
    if (A.size()<B.size())
        swap(A, B);

    vector<int> D(B.size());
    iota(D.begin(), D.end(), 0);

    for (int i=1; i<=A.size(); i++) {
        int previ1j1=D[0];
        D[0]=i;
        for (int j=1; j<B.size(); j++) {
            int previ1j=D[j];
            D[j]= A[i-1]==B[j-1] ? previ1j1 : 1+min(min(D[j], D[j-1]), previ1j1);
            previ1j1=previ1j;
        }
    }
    return D.back();
}

struct TupleHash {
    int operator()(const tuple<int, int, int> & that) const {
        return hash<int>()(get<0>(that)) ^ hash<int>()(get<1>(that)) ^ hash<int>()(get<2>(that));
    }
};

static bool matchStringIn2DArray_helper(const vector<vector<int> > &A, const vector<int> &s,
                                 unordered_set<tuple<int, int, int>, TupleHash> &table, int i, int j, int len) {
    if (len=s.size())
        return true;
    if (i<0 || i>=A.size() || j<0 || j>=A[i].size() ||table.find(tuple<int, int, int>(i, j, len)) != table.end())
        return false;
    if (A[i][j]==s[len]
            && (matchStringIn2DArray_helper(A, s, table, i+1, j, len+1)
                || matchStringIn2DArray_helper(A, s, table, i, j+1, len+1)
                || matchStringIn2DArray_helper(A, s, table, i-1, j, len+1)
                || matchStringIn2DArray_helper(A, s, table, i, j-1, len+1)
            ))
        return true;
    table.insert(tuple<int, int, int>(i, j, len));
    return false;
}

bool Meta::matchStringIn2DArrary(const vector<vector<int> > &A, const vector<int> &s) {
    unordered_set<tuple<int, int, int>, TupleHash> table;
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A.front().size(); j++) {
            if (matchStringIn2DArray_helper(A, s, table, i, j, 0))
                return true;
        }
    return false;
}

template<typename T>
pair<double, double> calc_tree_diameter_helper(const unique_ptr<TreeNode<T> > &root) {
    double diameter=numeric_limits<double>::min();
    vector<double> height(2,0);// secondmax, max
    for (auto &e : root->edges) {
        auto bottom = calc_tree_diameter_helper(e.first);
        if (bottom.first+e.second>height[1]) {
            height[0]=height[1];
            height[1]=bottom.first+e.second;
        } else if (bottom.first + e.second > height[0])
            height[0]=bottom.first + e.second;
        diameter=max(diameter, bottom.second);
    }
    return pair<double, double>(height[1], max(diameter, height[1]+height[0]));
}

template<typename T>
double Meta::calc_tree_diameter(const unique_ptr<TreeNode<T> > &root) {
    return root ? calc_tree_diameter_helper(root) : 0.0;
}

static bool checkValidation(Meta::Box & b, vector<Meta::Box> & tower) {
    for (auto x: tower) {
        if (b.h<x.h || b.d<x.d)
            return false;
    }
    return true;
}

static int calcHeight(vector<Meta::Box> & b) {
    int height=0;
    for (auto x : b)
        height += x.h;
    return height;
}

static vector<Meta::Box> buildTallestTower_helper_table(vector<Meta::Box> &boxes, int index, unordered_map<int, vector<Meta::Box> > &table) {
    if (index>=boxes.size()) return vector<Meta::Box>();
    if (table.find(index) != table.end())
        return table[index];

    vector<Meta::Box> tallest;
    for (int i=index; i<boxes.size(); i++) {
        vector<Meta::Box> tower=buildTallestTower_helper_table(boxes, index+1, table);
        if (checkValidation(boxes[i], tower)) {
            tower.push_back(boxes[i]);
            if (calcHeight(tower)>calcHeight(tallest)) {
                tallest=tower;
            }
            tower.pop_back();
        }
    }
    table.emplace(index, tallest);
    return tallest;
}

static void buildTallestTower_helper(vector<Meta::Box> &boxes, vector<Meta::Box> &tower, vector<Meta::Box> &tallest, int index) {
    if (index>=boxes.size()) return;

    for (int i=index; i<boxes.size(); i++) {
        if (checkValidation(boxes[i], tower)) {
            tower.push_back(boxes[i]);
            if (calcHeight(tower)>calcHeight(tallest)) {
                tallest=tower;
            }
            buildTallestTower_helper(boxes, tower, tallest, index+1);
            tower.pop_back();
        }
    }
}

vector<Meta::Box> Meta::buildTallestTower(vector<Box> Boxes) {
    for (int i=0; i<Boxes.size(); i++) {
        Box x=Boxes[i];
        cout << x.id << " " << x.h << ", ";
    }
    cout << endl;

    sort(Boxes.begin(), Boxes.end());
    cout << "after sorting" << endl;
    for (auto x: Boxes) {
        cout << x.id << " " << x.h << ", ";
    }
    cout << endl;

    unordered_map<int, vector<Box> > table;
    vector<Box> tallest=buildTallestTower_helper_table(Boxes, 0, table);

    cout << "tallest tower" << endl;

    for (auto x: tallest) {
        cout << x.id << " " << x.h << ", ";
    }
    cout << endl;

    return tallest;
}

static int computeWaysParseExpression_helper(const string & exp, bool result, int s, int e, unordered_map<string, int> & table) {
    string key = to_string(result)+to_string(s)+to_string(e);
    if (table.find(key)!=table.end())
        return table[key];

    if (s==e) {
        if (exp[s]=='1' && result==true || exp[s]=='0' && result==false)
            return 1;
        return 0;
    }

    int c=0;
    if (result) {
        for (int i=s+1; i<=e; i+=2) {
            if (exp[i]=='&') {
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
            } else if (exp[i]=='|') {
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, false, i+1, e, table);
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
                c += computeWaysParseExpression_helper(exp, false, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
            } else if (exp[i]=='^') {
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, false, i+1, e, table);
                c += computeWaysParseExpression_helper(exp, false, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
            } else
                throw invalid_argument("invalid expression");
        }
    } else {
        for (int i=s+1; i<=e; i+=2) {
            if (exp[i]=='&') {
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, false, i+1, e, table);
                c += computeWaysParseExpression_helper(exp, false, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
            } else if (exp[i]=='|') {
                c += computeWaysParseExpression_helper(exp, false, s, i-1, table)*computeWaysParseExpression_helper(exp, false, i+1, e, table);
            } else if (exp[i]=='^') {
                c += computeWaysParseExpression_helper(exp, true, s, i-1, table)*computeWaysParseExpression_helper(exp, true, i+1, e, table);
                c += computeWaysParseExpression_helper(exp, false, s, i-1, table)*computeWaysParseExpression_helper(exp, false, i+1, e, table);
            } else
                throw invalid_argument("invalid expression");

        }
    }
    table.emplace(key, c);
        return c;

}

int Meta::computeWaysParseExpression(const string &exp, bool result) {
    unordered_map<string, int> table;
    return computeWaysParseExpression_helper(exp, result, 0, exp.size()-1, table);
}

static bool isPositionValid(int y, int x, vector<int> & positions) {
    for (int i=0; i<positions.size(); i++) {
//        printf("%d, %d, %d, %d\n", y, x, i, positions[i]);
        if (positions[i]==x || y-i==x-positions[i] || y-i==positions[i]-x)
            return false;
    }
    return true;
}

static void findQueensPositions_helper(int cSize, vector<vector<int> > & result, vector<int> & positions) {
    if (positions.size()==cSize) {
        result.push_back(positions);
        copy(positions.begin(), positions.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    int index=positions.size();
    for (int i=0; i<cSize; i++) {
        if (isPositionValid(index, i, positions)) {
//            cout << index << " " << i << endl;
           positions.push_back(i);
           findQueensPositions_helper(cSize, result, positions);
           positions.pop_back();
        }
    }
}

vector<vector<int> > Meta::findQueesPositions(int chessSize) {
    vector<vector<int> > res;
    vector<int> x; // one solution
    findQueensPositions_helper(chessSize, res, x);
    return res;
}

static int makeCoinSetNum_helper(int n, vector<int> coins, int index) {
    if (index==coins.size()) {
        if (n==0) return 1;
        return 0;
    }

    int ways=0;
    int coin=coins[index];
    for (int i=0; i<=n/coin; i++) {
        ways += makeCoinSetNum_helper(n-i*coin, coins, index+1);
    }
    return ways;
}

static void makeCoinSet_helper(int n, vector<vector<int> > & all, vector<int> & change, vector<int> coins, int index) {
    if (index==coins.size()) {
        if (n==0) {
            copy(change.begin(), change.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
            all.push_back(change);
        }
        return;
    }

    int coin=coins[index];
    for (int i=0; i<=n/coin; i++) {
        change.push_back(i);
        makeCoinSet_helper(n-i*coin, all, change, coins, index+1);
        change.pop_back();
    }

}

vector<vector<int> > Meta::makeCoinSet(int n) {
    vector<int> coins{25, 10, 5, 1};

    vector<vector<int> > all;
    vector<int> change;
    makeCoinSet_helper(n, all, change, coins, 0);
    cout << makeCoinSetNum_helper(n, coins, 0) << endl;
    return all;
}

static void generateParentheses_helper(vector<string> & all, int leftRem, int rightRem, string &str, int index) {
    if (leftRem==0 && rightRem==0) {
        all.push_back(str);
        return;
    }

    if (leftRem>0) {
        str[index]='(';
        generateParentheses_helper(all, leftRem-1, rightRem, str, index+1);
    }

    if (rightRem>leftRem) {
        str[index]=')';
        generateParentheses_helper(all, leftRem, rightRem-1, str, index+1);
    }
}

vector<string> Meta::generateParentheses(int count) {
    string str(count*2, '0');
    vector<string> all;
    generateParentheses_helper(all, count, count, str, 0);
    for (auto x: all)
        cout << x << endl;
    return all;
}

static int multiply_helper(int a, int b) {
    if (b==0) return 0;
    if (b==1)
        return a;
    if (!b & 1)
        return multiply_helper(a, b>>1) << 1;
    else
        return multiply_helper(a, b-1)+a;
}

int Meta::multiply(int a, int b) {
    if (!a || !b) return 0;
    bool neg=false;
    if (a>0 && b<0 || a<0 && b>0)
        neg=true;
    int x=abs(a), y=abs(b);
    int ret;
    if (x<y) ret = multiply_helper(y, x);
    else
        ret = multiply_helper(x, y);
    return neg ? -ret : ret;
}

bool Meta::checkPresidentEletionTie(vector<int> &votelist)
{
    int totalvotes = accumulate(votelist.begin(), votelist.end(), 0);

    if (totalvotes & 1)
        return false;

    vector<bool> table(totalvotes+1, false);
    table[0]=true;

    for (int i=0; i<votelist.size(); i++)
        for (int j=totalvotes; j>=votelist[i]; j++)
        {
            table[i] = table[i] ? table[i] : table[i-votelist[i]];
        }

    return table[totalvotes>>1];
}

/**
 * @brief Meta::knapsack
 * @param sweets vector of <weight, nutrition>
 * @param weightlimit
 */
void Meta::knapsack(vector<pair<int, int> > &sweets, int weightlimit)
{
    vector<int> nutrition(weightlimit+1, 0);
    vector<int> items(weightlimit+1, -1);

    //------ implementation for unlimited supplies, i.e., unlimited number of each items
//    for (int w=1; w<weightlimit+1; w++)
//        for (int i=0; i<sweets.size(); i++)
//        {
//            if (w>=sweets[i].first)
//            {
//                int x = nutrition[w-sweets[i].first] + sweets[i].second;
//                if (nutrition[w] < x)
//                {
//                    nutrition[w] = x;
//                    items[w] = i;
//                }
//            }
//        }
   //-------------another implementation for unique item, i.e., one of each item--------------------------------
    for (int i=0; i<sweets.size(); i++)
        for (int w=weightlimit; w>=sweets[i].first; w--)
        {
            nutrition[w] = max(nutrition[w], nutrition[w-sweets[i].first] + sweets[i].second);
        }


   //----------------------- the following should be wrong
    // print result
//    int k=weightlimit;
//    if (items[k]==-1)
//    {
//        cout << "basket is empty because of weight limit";
//        return;
//    }

//    while (k>0 && items[k] != -1)
//    {
//            cout << items[k] << " ";
//            k -= sweets[items[k]].first;
//    }
//    cout << endl;

}

int Meta::knapsack_clock(vector<Clock> &G, int capacity) {
    vector<int> w(capacity+1, 0);

    int maxV=0;
    for (auto & x: G) {
        for (int i=capacity; i>=x.weight; i--) {
            if ( w[i] < w[i-x.weight]+x.value) {
                w[i]=w[i-x.weight]+x.value;
                maxV=max(maxV, w[i]);
            }
        }
    }
    return maxV;
}

void Meta::knapsack_clock_2(vector<Clock> &G, int capacity) {
    vector<vector<pair<int, int> > >table(G.size(), vector<pair<int, int> >(capacity+1, pair<int, int>(0,0)));

    for (int i=0; i<G.size(); i++)
        for (int j=G[i].weight; j<=capacity; j++) {
            if (table[i][j].first< G[i].value + i<1 ? 0 : table[i-1][j-G[i].weight].first) {
                table[i][j].first= G[i].value + i<1 ? 0 : table[i-1][j-G[i].weight].first;
                table[i][j].second=i;
            } else
                table[i][j]=i<1? table[i][j]: table[i-1][j];
        }
    int maxV=0, index=-1;
    for (int j=1; j<=capacity; j++) {
        if (maxV< table[G.size()-1][j].first) {
            maxV=table[G.size()-1][j].first;
            index=j;
        }
    }
    if (maxV=0) {
        cout << "cannot hold any item due to small capacity" ;
        return;
    }
    int curr=table[G.size()-1][index].second, prev=-1;
    while (curr>=0) {
        if (curr!=prev) {
            cout << curr << endl;
            maxV=maxV-G[curr].weight;
        }
        prev=curr;
        curr=table[curr-1][maxV].second;
    }
}

struct MaxHW
{
    int h, w;
    MaxHW(int _h, int _w): h(_h), w(_w){}
    MaxHW(){}
};

// time O(mn), space O(mn)
int Meta::computeMaxRectangleMatrix_mn(vector<vector<bool> > &arr)
{
    vector<vector<int> > table(arr.size(), vector<int>(arr.front().size(), 0));

    for (int i=0; i<arr.size(); i++)
        for (int j=0; j<arr.front().size(); j++)
        {
            table[i][j] = arr[i][j] ? i+1<arr.size() ? table[i+1][j]+1: 1 : 0;
        }

    int maxRect=0;
    for (int i=0; i<arr.size(); i++)
        maxRect = max(maxRect, findLargestRectangleforArray(table[i]));

    return maxRect;
}

/// time O(mn^2) space O(mn)
vector<vector<MaxHW> > compute2DTable(vector<vector<bool> > &arr)
{
    vector<vector<MaxHW> > table(arr.size(), vector<MaxHW>(arr[0].size()));
    for (int i=arr.size()-1; i>=0; i--)
        for (int j=arr.front().size()-1; j>=0; j--)
        {
            table[i][j]=arr[i][j] ?
                        MaxHW(i+1<arr.size() ? table[i+1][j].h+1 : 1, j+1<arr.front().size() ? table[i][j+1].w+1 : 1) :
                        MaxHW(0,0);
        }
    return table;
}

// time O(mn), Space O(mn)
int Meta::computeMaxSquareMatrix(vector<vector<bool> > &arr)
{
    vector<vector<MaxHW> > table = compute2DTable(arr);
    vector<vector<int> > s(arr.size(), vector<int>(arr.front().size(), 0));

    int maxSquare=0;
    for (int i=arr.size()-1; i>=0; i--)
        for (int j=arr.front().size()-1; j>=0; j--)
        {
            int t = min(table[i][j].h, table[i][j].w);
            if (arr[i][j])
            {
                if (i+1< arr.size() && j<arr.front().size())
                    t = min(t, s[i+1][j+1]+1);
                s[i][j]=t;
                maxSquare = max(maxSquare, t*t);
            }
        }
    return maxSquare;
}

int Meta::computeMaxRectangleMatrix(vector<vector<bool> > &arr)
{
    vector<vector<MaxHW> > table = compute2DTable(arr);

    int maxRect=0;
    for (int i=0; i<arr.size(); i++)
        for (int j=0; j< arr.front().size(); j++)
        {
            if (arr[i][j] && table[i][j].h*table[i][j].w > maxRect)
            {
                int minW = numeric_limits<int>::max();
                for (int x=0; x<table[i][j].h; x++)
                {
                    minW = min(minW, table[i+x][j].w);
                    maxRect = max(maxRect, minW*(x+1));
                }
            }

        }
    return maxRect;
}

int Meta::findLargestRectangleforArray_linearTime(vector<int> &arr) {
    stack<int> s;
    vector<int> L;
    for (int i=0; i<arr.size(); i++)
    {
        if (!s.empty() && arr[s.top()]>=arr[i])
            s.pop();
        L.push_back(s.empty()?-1:s.top());
        s.push(i);
    }
    while (!s.empty())
        s.pop();
    vector<int> R(arr.size());
    for (int i=arr.size()-1; i>=0; i--) {
        while (!s.empty() && arr[s.top()]>=arr[i])
            s.pop();
        R[i]=!s.empty() ? arr.size() : s.top();
        s.push(i);
    }
    int maxArea=0;
    for (int i=0; i<arr.size(); i++) {
        maxArea=max(maxArea, arr[i]*(R[i]-L[i]-1));
    }
    return maxArea;
}

//http://www.youtube.com/watch?v=E5C5W6waHlo
int Meta::findLargestRectangleforArray(vector<int> &arr)
{
    stack<int> indexes;
    stack<int> heights;
    int maxArea =0;
    int startIndex =0;

    for (int i=0; i<arr.size(); i++)
    {
        if (indexes.empty() || heights.top() > arr[i])
        {
            // case 1: push the start candidate
            indexes.push(i);
            heights.push(arr[i]);
        }
        else if (heights.top() < arr[i])
        {
            // case 2: pop the start index, compute the area and update maxArea;

            while( !indexes.empty() && heights.top() < arr[i])
            {
                startIndex=indexes.top();
                int area = heights.top() * (i-indexes.top());
                maxArea = max(area, maxArea);
                heights.pop();
                indexes.pop();
            }

            indexes.push(startIndex);
            heights.push(arr[i]);
        }
    }
    while( !indexes.empty())
    {
        int area = heights.top() * (arr.size()-indexes.top());
        maxArea = max(area, maxArea);
        heights.pop();
        indexes.pop();
    }

    return maxArea;
}

void Meta::findLongestSubArraySumLessThanK_general(vector<int> &arr, int k)
{
    vector<int> Cursum;
    partial_sum(arr.begin(), arr.end(), back_inserter(Cursum));

    vector<int> psum;
    psum.push_back(Cursum[0]);
    for (int i=1; i<Cursum.size(); i++)
        psum.push_back(max(psum[i-1], Cursum[i]));

    pair<int, int> result(0,0);
    int left=0,right=0;
    for (int right=0; right<psum.size(); right++)
    {
        if (psum[right]- psum[left]>k)          // change here for greater, equal of sum or average sum
        {
            if (result.second-result.first < right-1-left)
            {
                result = make_pair(left, right-1);
            }
            while (psum[right]-psum[left]>=k) // change here for greater, equal of sum or average sum
            {
                left += 1;
            }

            // if include equal, should check it here
        }
    }
    if (result.second-result.first<right-1-left)
        result = make_pair(left, right-1);
    cout << result.first << " " << result.second << endl;
}

pair<int, int> Meta::findLongestSubarrySumLessEqualK(vector<int> & arr, int k)
{
    vector<int> Cursum;
    partial_sum(arr.begin(), arr.end(), back_inserter(Cursum));

    vector<int> psum(Cursum);
    for (int i=psum.size()-2; i>=0; i--)
        psum[i]=min(psum[i], psum[i+1]);

    pair<int, int> result(0, distance(psum.begin(), upper_bound(psum.begin(), psum.end(), k))-1);
    for (int i=0; i<psum.size(); i++)
    {
        int idx = distance(psum.begin(), upper_bound(psum.begin(), psum.end(), Cursum[i]+k))-1;
        if (idx-i-1>result.second-result.first) {
            result = make_pair(i+1, idx);
        }
    }

    return result;

}

pair<int, int> Meta::findLongestSubarrySumLessEqualK_queue(const vector<int> &A, int k){
    int sum=0;
    queue<int> Q, ret;
    for (int i=0; i<A.size(); i++) {
        sum += A[i];
        Q.push(i);
        if (sum<=k) {
            if (Q.size()>ret.size())
                ret=Q;
        } else {
            while (!Q.empty() && sum>k) {
                sum-=A[Q.front()];
                Q.pop();
            }
        }
//        if (sum+A[i]<=k){
//            sum += A[i];
//            Q.push(i);
//            if (Q.size()>ret.size()) {
//                ret=Q;
//            }
//        } else {
//            while (!Q.empty() && sum+A[i] > k) {
//                sum -= A[Q.front()];
//                Q.pop();
//            }
//            if (sum+A[i]<=k) {
//                sum += A[i];
//                Q.push(i);
//            }
//        }
    }
    pair<int, int> ans(-1, -1);
    while (!ret.empty()) {
        if (ans.first==-1)
            ans.first=ret.front();
        ans.second = ret.front();
        ret.pop();
    }
    return ans;

}

pair<int, int> Meta::findLongestSubarrySumLessEqualK_withoutqueue(const vector<int> &A, int k){
    pair<int, int> ret={-1, -1};
    if (A.empty()) return ret;
    int sum=0, start=0;
    for (int i=0; i<A.size(); i++) {
        sum+=A[i];
        if (sum<=k) {
            if (ret.first==-1 || i-start> ret.second-ret.first)
                ret={start, i};
        } else {
            while (sum>k && start<=i) {
                sum-=A[start++];
            }
        }
    }
    return ret;
}

void Meta::findNonNegativeSubArraySumToK(vector<int> &arr, int k)
{
    if (arr.empty()) return;
    if (arr.size()==1)
    {
        if (arr[0]==k) cout << 0 << " " << 0 << endl;
        return;
    }

    int sumTill = 0;
    int start=0;
    for (int i=0; i<arr.size(); i++)
    {
        sumTill += arr[i];
        if (sumTill == k)
        {
            cout << start << " " << i << endl;
            return ;
        }
        else if (sumTill > k)
        {
            while (sumTill > k && start <= i)
            {
                sumTill -= arr[start];
                start++;
            }

            if (sumTill == k)
            {
                cout << start << " " << i << endl;
                return;
            }
        }

    }


}

vector<int> findLongestIncreaseSubSequence(vector<int> &arr)
{
    vector<int> buff;
    vector<int> inc(arr.size(), 1);
    buff.push_back(arr[0]);
    for (int i=1; i<arr.size(); i++)
    {
        auto itr = upper_bound(buff.begin(), buff.end(), arr[i]);
        if (itr==buff.end())
        {
            buff.push_back(arr[i]);
            inc[i]=inc[i-1]+1;
        }
        else
            *itr = arr[i];
    }
    return inc;
}

int Meta::findLongestBitonicSubSequence(vector<int> &arr)
{
    if (arr.empty()) return 0;
    if (arr.size()==1) return 1;

    vector<int> inc = findLongestIncreaseSubSequence(arr);
    reverse(arr.begin(), arr.end());
    vector<int> dec = findLongestIncreaseSubSequence(arr);

    int maxV=0;
    for (int i=0; i<arr.size(); i++)
        maxV = max(maxV, inc[i]+dec[arr.size()-i-1]-1);

    return maxV;
}

int Meta::findLongestAlternatingSubSequence(vector<int> &arr)
{
    vector<int> inc(arr.size(), 1);
    vector<int> dec(arr.size(), 1);

    for (int i=1; i<arr.size(); i++)
        for (int j=0; j<i; j++)
        {
            if (arr[j]<arr[i])
            {
                inc[i] = max(inc[i], dec[j]+1);
            }
            else
            {
                dec[i] = max(dec[i], inc[j]+1);
            }
        }
    int maxInc = *(max_element(inc.begin(), inc.end()));
    int maxDec = *(max_element(dec.begin(), dec.end()));
    return maxInc > maxDec ? maxInc: maxDec;
}

int Meta::findLongestNonDescreaseSubSequence(vector<int> &arr)
{
    vector<int> subsequence;
    for (auto &x : arr)
    {
        auto itr = upper_bound(subsequence.begin(), subsequence.end(), x);
        if (itr==subsequence.end())
            subsequence.push_back(x);
        else
            *itr=x;
    }
    return subsequence.size();
}

vector<int> Meta::findLongestNonDescreaseSubSequence_vect(vector<int> &A) {
    if (A.empty())
        return A;
    vector<pair<int, int> > M(A.size(), pair<int, int>(1, -1));
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<i; j++) {
            if (A[i]>=A[j] && M[i].first<M[j].first +1)
                M[i] = {M[j].first+1, j};
        }
    int maxlen=0, k=0;
    for (int i=0; i<A.size(); i++) {
        if (maxlen<M[i].first) {
            maxlen=M[i].first;
            k=i;
        }
    }
    vector<int> ret;
    while (k!=-1) {
        ret.push_back(A[k]);
        k=M[k].second;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int findMaxSumSubArray(const vector<int> &arr)
{
    int maxSum=numeric_limits<int>::min();
    int maxSumTill=0;
    for (auto x : arr)
    {
        maxSumTill = max(maxSumTill+x, x);
        maxSum = max(maxSum, maxSumTill);
    }
    return maxSum;
}

int findMaxSumSubCircularArray_helper(const vector<int> & arr)
{
    vector<int> maxSumBegin;
    int sumTill = arr[0];
    maxSumBegin.push_back(arr[0]);
    for (int i=1; i<arr.size(); i++)
    {
        sumTill += arr[i];
        maxSumBegin.push_back(max(maxSumBegin.back(), sumTill));
    }
    vector<int> maxSumEnd(arr.size(), 0);
    sumTill=0;
    for (int i=arr.size()-2; i>=0; i--)
    {
        sumTill += arr[i+1];
        maxSumEnd.push_back(max(maxSumEnd[i+1], sumTill));
    }
    int maxSum=numeric_limits<int>::min();
    for (int i=0; i<arr.size(); i++)
    {
        maxSum = max(maxSum, maxSumBegin[i]+maxSumEnd[i]);
    }
    return maxSum;

}

int Meta::findMaxSumSubCircularArray(const vector<int> &arr)
{
    return max(findMaxSumSubArray(arr), findMaxSumSubCircularArray_helper(arr));
}

static void MaxMarginCoinGame_sub(stack<int> & coins, vector<int> & seq, int &maxMargin)
{
    if (coins.size()==1)
    {
        seq.push_back(coins.top());
        int player0=0, player1=0;
        for (int i=0; i<seq.size(); i+=2)
        {
            cout << seq[i] << " " << seq[i+1] << " ";
            player0 += seq[i];
            player1 += seq[i+1];
        }
        seq.pop_back();

        int margin=abs(player0-player1);
        if (maxMargin<margin)
            maxMargin=margin;

        cout << maxMargin  << endl;

        return;
    }

    int top=coins.top();
    seq.push_back(top);
    coins.pop();
    MaxMarginCoinGame_sub(coins, seq, maxMargin);
//    cout << "maxMargin=" << maxMargin << endl;
//    cin.get();

    int top1=coins.top();
    coins.pop();
    coins.push(top);
    seq.pop_back();
    seq.push_back(top1);
    MaxMarginCoinGame_sub(coins, seq, maxMargin);

//    cout << "maxMargin=" << maxMargin << endl;
//    cin.get();

    seq.pop_back();
    coins.pop();
    coins.push(top1);
    coins.push(top);

}

int Meta::MaxMarginCoinGame(vector<int> &arr)
{
    if (arr.empty() || ((arr.size()&1)==1)) return 0;

    stack<int> coins;
    for (int i=0; i<arr.size(); i++)
        coins.push(arr[i]);

    vector<int> seq;
    int maxMargin=0;
    MaxMarginCoinGame_sub(coins, seq, maxMargin);

    return maxMargin;

}

int Meta::compute_combination_without_overflow(int n, int k)
{
    if (n<=0 || k<=0 || n<k) return 0;

    vector<vector<int> > table(n+1, vector<int>(k+1, 1));

    for (int i=0; i<=k; i++)
        table[i][i]=1;

    for (int i=2; i<=n; i++)
        for (int j=1; j<i && j<=k; j++)
        {
            table[i][j]=table[i-1][j-1]+table[i-1][j];
        }

    return table[n][k];
}

int Meta::count_score_combination(int k, const vector<int> &score_ways)
{
    if (k<=0) return 0;

    vector<int> combination(k+1, 0);
    combination[0]=1;

    for (auto score : score_ways)
        for (int i=score; i<=k; i++)
            combination[i] += combination[i-score];

    return combination[k];

}

int Meta::count_score_permutation(int k, const vector<int> &score_ways)
{
    if (k==0) return 0;

    vector<int> permutation(k+1, 0);
    permutation[0]=1;

    for (int i=1; i<=k; i++)
        for (auto score : score_ways)
        {
            if (i>=score)
            permutation[i]+=permutation[i-score];
        }
    return permutation[k];
}

//int Meta::count_score_permutation_const_space(int k, const vector<int> &score_ways)
//{
//    if (k==0) return 0;

//    int maxScore = *(std::max_element(score_ways.begin(), score_ways.end()));
//    vector<int> permutation(maxScore+1, 0);
//    permutation[0]=1;

//    for (int i=1; i<=k; i++)
//        for (auto score : score_ways)
//        {
//            if (i>=score)
//            permutation[i%(maxScore+1)]+=permutation[(i-score)%(maxScore+1)];
//        }
//    return permutation[maxScore];
//}

static int maxMargin_pick_up_coins_help(const vector<int> & coins, int a, int b, vector<vector<int> > &table)
{
    if (a>b) return 0;

    if (table[a][b] == -1)
    {
        table[a][b]= std::max(coins[a]+std::min(maxMargin_pick_up_coins_help(coins, a+1, b-1, table),
                                                maxMargin_pick_up_coins_help(coins, a+2, b, table)),
                              coins[b]+std::min(maxMargin_pick_up_coins_help(coins, a, b-2, table),
                                                maxMargin_pick_up_coins_help(coins, a+1, b-1, table)));
    }

    return table[a][b];
}

int Meta::maxMargin_pick_up_coins(const vector<int> &coins)
{
    vector<vector<int> > table(coins.size(), vector<int>(coins.size(), -1));

    return maxMargin_pick_up_coins_help(coins, 0, coins.size()-1, table);
}

double distance(PointA &a, PointA &b)
{
    return sqrt((a.x-b.x)^2 + (a.y-b.y)^2);
}

tuple<PointA, PointA, double> bruteForceSearch(vector<PointA> &arr, int s, int e)
{
    double minDist = numeric_limits<double>::max();
    tuple<PointA, PointA, double> ret;
    for (int i=s; i<=e; i++)
        for (int j=i+1; j<=e; j++)
        {
            double x = distance(arr[i], arr[j]);
            if (minDist>x)
            {
                minDist = x;
                ret=make_tuple(arr[i], arr[j], x);
            }
        }
    return ret;
}

tuple<PointA, PointA, double> findClosestPoints_crossPartition(vector<PointA> & arr, int s, int m, int e, double d)
{
    vector<PointA> remainLeft;
    vector<PointA> remainRight;
    for (int i=s; i<m; i++)
    {
        if (fabs(arr[i].x - arr[m].x)<d)
        {
            remainLeft.push_back(arr[i]);
        }
    }
    for (int i=m; i<e; i++)
    {
        if (fabs(arr[i].x - arr[m].x)<d)
        {
            remainRight.push_back(arr[i]);
        }
    }
    sort(remainLeft.begin(), remainLeft.end(), [](const PointA &a, const PointA &b){ return a.y<b.y;});
    sort(remainRight.begin(), remainRight.end(),[](const PointA &a, const PointA &b){ return a.y<b.y;});
    tuple<PointA, PointA, double> ret;
    get<2>(ret) = numeric_limits<double>::max();
    for (int i=0; i<remainLeft.size(); i++)
        for (int j=0; j<remainRight.size() && (remainRight[j].y-remainLeft[i].y)<d; j++)
        {
            double t = distance(remainLeft[i], remainRight[j]);
            if (t < get<2>(ret))
            {
                ret = make_tuple(remainLeft[i], remainRight[j], t);
            }
        }
    return ret;
}

tuple<PointA, PointA, double> findClosestPoints_helper(vector<PointA> &arr, int s, int e)
{
    if (e-s<=2)
        return bruteForceSearch(arr, s, e);

    int m = s + ((e-s)>>1);
    auto left = findClosestPoints_helper(arr, s, m-1);
    auto right = findClosestPoints_helper(arr, m, e);
    tuple<PointA, PointA, double> ret = get<2>(left) < get<2>(right) ? left : right;

    auto ret2 = findClosestPoints_crossPartition(arr,s, m, e, get<2>(ret));

    return get<2>(ret) < get<2>(ret2) ? ret : ret2;

}

pair<PointA, PointA> Meta::findClosestPoints(vector<PointA> &arr)
{
    sort(arr.begin(), arr.end(), [](const PointA &a, const PointA &b){ return a.x < b.x; });

    auto ret = findClosestPoints_helper(arr, 0, arr.size()-1);

    return make_pair(get<0>(ret), get<1>(ret));

}

//************************



