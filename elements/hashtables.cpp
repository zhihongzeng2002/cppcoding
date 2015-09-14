#include "hashtables.h"
#include <algorithm>
#include <list>
#include <unordered_map>
#include <climits>

HashTables::HashTables()
{
}

vector<string> HashTables::kSuspiciousStrings(const vector<string> &S, int k) {
    unordered_map<string, vector<string> > table;
    for (auto &s : S) {
        for (int i=0; i<=s.size()-k; i++) {
            table[s.substr(0, k)].emplace_back(s);
        }
    }
    vector<string> ret;
    for (auto &t: table) {
        if (t.second.size()>=2)
            for (auto &x: t.second)
                ret.emplace_back(x);
    }
    return ret;
}

vector<string> HashTables::findMajorityWords_general(istringstream &sin, int k) {
    unordered_map<string, int> table;
    string s;
    int n=0;
    while (sin >> s) {
        table[s]++;
        n++;
        if (table.size()>=k+1) {
            for (auto it=table.begin(); it != table.end(); it++){
                if (--it->second==0) { // because it must be a item which is just added
                    table.erase(it++);
                }
            }
        }
    }

    for (auto &t:table)
        t.second=0;

    sin.clear();
    sin.seekg(0, ios::beg);
    while (sin>>s) {
        auto it = table.find(s);
        if (it != table.end())
            it->second++;
    }

    vector<string> ret;
    for (auto &t: table) {
        if (t.second>=static_cast<double>(n)/k)
            ret.emplace_back(t.first);
    }
    return ret;
}

shared_ptr<HashTables::BNode> HashTables::buildCannonicTree_helper(shared_ptr<BSTNode<int> > &n,
                             unordered_set<shared_ptr<BNode>, HashBNode, EqualBNode> &table) {
    if (!n) return nullptr;

    shared_ptr<BNode> left = buildCannonicTree_helper(n->left, table);
    shared_ptr<BNode> right = buildCannonicTree_helper(n->right, table);
    shared_ptr<BNode> newNode(new BNode(n->data, left, right));
    table.emplace(newNode);
    return newNode;
}

vector<shared_ptr<HashTables::BNode> > HashTables::buildCannonicTree(vector<shared_ptr<BSTNode<int> > > &nodes) {
    unordered_set<shared_ptr<BNode>, HashBNode, EqualBNode > table;
    vector<shared_ptr<BNode> > ret;
    for (auto &n : nodes) {
        buildCannonicTree_helper(n, table);
    }
    for (auto &x : table)
        ret.push_back(x);

    return ret;
}

int HashTables::chessHash(const vector<vector<int> > &B) {
    int h =0;
//    for (int i=0; i<B.size(); i++)
//        for (int j=0; j<B.front().size(); j++)
//            h=h*13+B[i][j];
    random_device rd;
    unordered_set<int> check; // prevent the repetition;
    vector<vector<int> > table(B.size(), vector<int>(B[0].size(), 0));
    for (int i=0; i<64; i++) {
        for (int j=0; j<13; j++) {
            int x=rd();
            while (check.find(x)!=check.end())
                x=rd();
            table[i][j]=x;  // or power(13,i)+j;
            check.emplace(x);
        }
    }

    for (int i=0; i<B.size(); i++)
        for (int j=0; j<B.front().size(); j++)
            h ^= table[i*8+j][B[i][j]];

    return h;
}

pair<int, int> HashTables::find_smallest_subarray_sequentially_covering_subset(stringstream &sin, const vector<string> &Q) {
    unordered_map<string, int> K;
    vector<int> L(Q.size(), -1), D(Q.size(), INT_MAX);

    for (int i=0;i<Q.size(); i++)
        K.emplace(Q[i], i);

    string x;
    pair<int, int> res(-1,-1);
    int i=0;
    while (sin>>x) {
        auto it = K.find(x);
        if (it != K.end()) {
            L[it->second]=i;
            if (it->second==0)
                D[it->second]=1;
            else if (D[it->second-1] != INT_MAX)
                D[it->second] = D[it->second-1] + i-L[it->second-1]+1;

            if (it->second==Q.size()-1 && D.back() < res.second-res.first+1)
                res=pair<int, int>(i-D.back()+1, i);
        }
        i++;
    }
    return res;

}

pair<int, int> HashTables::find_smallest_subarray_covering_subset(stringstream &sin, const vector<string> &Q)
{
    pair<int, int> res(-1,-1);
    list<int> loc;
    unordered_map<string, list<int>::iterator> table;
    for (auto w : Q)
        table.emplace(w, loc.end());

    int idx=0;
    string buff;
    while(sin>>buff)
    {
        auto it = table.find(buff);
        if (it != table.end())
        {
            if (it->second != loc.end())
            {
                loc.erase(it->second);
            }
            loc.push_back(idx);
            it->second = --loc.end();

        }

        if (table.size()==Q.size() && ((res.first==-1 && res.second ==-1)
                                       || idx-loc.front() < res.second-res.first))
        {
            res=pair<int, int>(loc.front(), idx);
        }

        idx++;
    }

    return res;
}

int HashTables::findIntAppearOnce(vector<int> &arr)
{
//    for x in lst:
//            twos |= ones & x
//            ones ^= x
//            not_threes = ~(ones & twos)
//            ones &= not_threes
//            twos &= not_threes
//        return ones
}

HashTables::Line::Line(PointA p0, PointA p1)
      : slope(p0.x!=p1.x ? get_canonical_fractional(p1.y-p0.y, p1.x-p0.x) : pair<int,int>(1, 0)),
      intercept(p0.x!=p1.x ? get_canonical_fractional(p1.x*p0.y-p0.x*p1.y, p1.x-p0.x) : pair<int,int>(p0.x, 1))
{}

HashTables::Line HashTables::find_line_with_most_points(const vector<PointA> & P)
{
    unordered_map<Line, unordered_set<PointA, hashPoint>, hashLine> table;
    for (int i=0; i<P.size(); i++)
    {
        for (int j=i+1; j<P.size(); j++)
        {
            Line line(P[i], P[j]);
            table[line].emplace(P[i]);
            table[line].emplace(P[j]);
        }
    }

    unordered_map<Line, unordered_set<PointA, hashPoint>, hashLine>::iterator result = max_element(table.begin(), table.end(), compobj);
    return result->first;
}

static void test()
{
    vector<int> arr;
    vector<int>::iterator x=max_element(arr.begin(), arr.end(), [](int i, int j){ return i<j;});
}


