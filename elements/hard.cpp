#include "hard.h"
#include <random>
#include <iostream>
#include <iterator>
#include <math.h>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <climits>

Hard::Hard()
{
}

int Hard::addTwoInts(int a, int b) {
    if (!b)
        return a;
    if (!a)
        return b;
    int x = a^b;
    int carry = a & b;
    return addTwoInts(x, carry<<1);
}

void Hard::shuffleCards(vector<int> & cards, int k) {
    random_device dev;
    default_random_engine eng(dev());

    for (int i=0; i<k; i++) {
        uniform_int_distribution<int> num(i, cards.size()-1);
        int x = num(eng);
        swap(cards[i], cards[x]);
    }
    cards.resize(k);

    copy(cards.begin(), cards.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

static int countIndividual(int i, int digit) {
    int count=0;
    string istr=to_string(i);
    string dstr=to_string(digit);
    char t = dstr[0];
    for (int i=0; i<istr.length(); i++) {
        char c=istr[i];
        if (c==t)
            count++;
    }
//    while (i) {
//        if (i%10==digit)
//            count++;
//        i /= 10;
//    }
    return count;
}

int Hard::countDigit_bruteforce(int n, int digit) {
    int count=0;
    for (int i=digit; i<=n; i++)
        count += countIndividual(i, digit);
    return count;
}

int countDigit_efficient_helper(int n, int d, int digit) {
    int power10 = pow(10, d);
    int powernext10 = power10*10;
    int right = n%power10;

    int roundDown = n - n%powernext10;
    int roundUp = roundDown + powernext10;

    int num = (n/power10) % 10;
    cout << "d=" << d << " right=" << right << " roundDown=" << roundDown << " num=" << num << endl;
    if (num<digit)
        return roundDown/10;
    else if (num==digit) {
        int x=(roundDown/10) + right +1;
        return x;
    }
    else
        return roundUp / 10;

}

int Hard::countDigit_efficient(int n, int digit) {
    int count=0;
    int len = to_string(n).length();
    for (int i=0; i<len; i++) {
        int x =countDigit_efficient_helper(n, i, digit) ;
        cout << x << endl;
        count += x;
    }
    return count;
}

bool compfunc(const string &x, const string & y) {
    return x.length()>y.length();
}

static bool canBuilt(string & x, bool isOriginal, unordered_map<string, bool> & table) {
    if (!isOriginal && table.find(x)!= table.end())
        return table.find(x)->second;

    for (int i=1; i<x.length(); i++) {
        string left = x.substr(0, i);
        string right = x.substr(i);
        if (table.find(left)!= table.end() && table[left] && canBuilt(right, false, table))
            return true;
    }
    table.emplace(x, false);
    return false;
}

string Hard::findLongestWordBuiltInDict(vector<string> &dict) {
    sort(dict.begin(), dict.end(), compfunc);

    unordered_map<string, bool> table;
    for (auto &x : dict) {
        table.emplace(x, true);
    }

    for (auto &x : dict) {
        if (canBuilt(x, true, table))
            return x;
    }
    return string();

}

struct TrieNode {
    unordered_map<char, shared_ptr<TrieNode> > children;

    TrieNode() {
    }

    void insert(shared_ptr<TrieNode> & node, string str) {
        if (str.empty()) return;

        auto it = node->children.find(str[0]);
        if (it == node->children.end()) {
            node->children.emplace(str[0], shared_ptr<TrieNode>(new TrieNode));
            it = node->children.find(str[0]);
        }
        insert(it->second, str.substr(1));
        insert(node, str.substr(1));
    }

    bool search(shared_ptr<TrieNode> & node, string str) {
        if (str.empty()) return true;

        auto it = node->children.find(str[0]);
        if ( it != node->children.end())
            return search(it->second, str.substr(1));
        else
            return false;
    }

};

void Hard::searchString_trie(const string str, const vector<string> &A) {
    // build trie
    shared_ptr<TrieNode> tree(new TrieNode);
    tree->insert(tree, str);

    // search
    for (auto & x : A) {
        if (tree->search(tree, x)) {
            cout << x << " is found" << endl;
        } else {
            cout << x << " not found" << endl;
        }
    }
}

static bool stringComp(const string &x, const string &y){
    return x.length()<y.length();
}

static bool rectValid(vector<string> & curr, shared_ptr<TrieNode> & trie) {
    string x;
    for (auto &t : curr)
        x.append(t, 0, 1);
    return trie->search(trie, x);
}

static void buildRect_helper(vector<string> &curr, vector<string> &result, int h, vector<string> & group, unordered_map<int, shared_ptr<TrieNode> > & table) {
    int len=curr.size();
    if (len==h) {
        result = curr;
        return;
    }

    for (int i=len; i<group.size(); i++) {
        swap(group[len], group[i]);
        curr.push_back(group[len]);
        if (rectValid(curr, table[h])) {
            buildRect_helper(curr, result, h, group, table);
            if (!result.empty())
                return;
        }
        curr.pop_back();
        swap(group[len], group[i]);
    }
}

static vector<string> buildRect(int w, int h, vector<vector<string> > & group, unordered_map<int, shared_ptr<TrieNode> > & table) {
    if (table.find(h) == table.end()) {
        shared_ptr<TrieNode> trie;
        for (int i=0; i<group[h-1].size(); i++)
            trie->insert(trie, group[h-1][i]);
        table.emplace(h, trie);
    }

    // permutation from group[w-1]
    vector<string> result, curr;
    buildRect_helper(curr, result, h, group[w-1], table);
    return result;
}

vector<string> Hard::buildLargestWordRectangle(vector<string> & dict) {
    // sort dict
    sort(dict.begin(), dict.end(), stringComp);

    vector<vector<string> > group;
    vector<string> curr;
    for (int i=0; i<dict.size(); i++) {
        if (!curr.empty()) {
            if (curr.back().size()==dict[i].size())
                curr.push_back(dict[i]);
            else {
                group.push_back(curr);
                curr.clear();
            }
        } else
            curr.push_back(dict[i]);
    }
    if (!curr.empty())
        group.push_back(curr);

    int area=dict.back().size() * dict.back().size();
    unordered_map<int, shared_ptr<TrieNode> > table;
    for (int x=area; x>=1; x--) {
        for (int w=1; w<sqrt(x); w++) {
            if (float(x)/w != x/w)
                continue;
            int h = x/w;
            vector<string> rect = buildRect(w, h, group, table);
            if (!rect.empty())
                return rect;
        }

    }
    return vector<string>();
}

void printMatrix(const vector<vector<int> > &A) {
    for (int i=0; i<A.size(); i++) {
        for (int j=0; j<A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int Hard::findMaxSub2DArray(vector<vector<int> > &A) {
    printMatrix(A);
    cout << endl;

    vector<vector<int> > B(A.size(), vector<int>(A.front().size(), 0));

    int t=0;
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A[i].size(); j++) {
            B[i][j]= (i<1 ? 0: B[i-1][j])
                           + (j<1 ? 0: B[i][j-1])
                                   - (i<1 || j<1 ? 0 : B[i-1][j-1])
                                                  +A[i][j];
            t+=A[i][j];
//            cout << i<< "," << j << "=" << A[i][j] << " " << B[i][j] << endl;
        }
    cout << t << endl;
    printMatrix(B);

    int maxV=INT_MIN;
    for (int x0=0; x0<B.size(); x0++)
        for (int x1=x0+1; x1<B.size(); x1++)
            for (int y0=0; y0<B.front().size(); y0++)
                for (int y1=y0+1; y1<B.front().size(); y1++) {
                    int sum=B[x1][y1]
                            -(y0<0 ? 0: B[x1][y0])
                            -(x0<0 ? 0: B[x0][y1])
                            +(x0<0 || y0<0 ? 0: B[x0][y0]);
                    if (maxV<sum)
                        maxV=sum;
//                    cout << x0<< "," << x1 << " " << y0 << " " << y1 << "=" << sum << " " << maxV << endl;
                }

    return maxV;
}

static vector<vector<int> > preprocess_column(vector<vector<int> > &A) {
    vector<vector<int> > B(A.size(), vector<int>(A.front().size(), 0));
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A[i].size(); j++) {
            B[i][j]=A[i][j]
                    + (i<1 ? 0 : B[i-1][j]);
        }
    return B;
}

static int findMaxColumn(int y0, int y1, vector<vector<int> > &B) {
    vector<int> v;
    for (int i=0; i<B.front().size(); i++) {
        v.push_back(B[y1][i]-B[y0][i]);
    }
//    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
    int maxV=INT_MIN;
    int sum=0;
    for (int i=0; i<v.size(); i++) {
        sum += v[i];
        if (maxV<sum) {
            maxV=sum;
        }
        if (sum<0)
            sum=0;
    }
    return maxV;

}

int Hard::findMaxSub2DArray_efficient(vector<vector<int> > &A) {
    printMatrix(A);
    vector<vector<int> > B = preprocess_column(A);
    cout << endl;
    printMatrix(B);
    cout << endl;

    int maxV=INT_MIN;
    for (int y0 = 0; y0<A.size(); y0++)
        for (int y1=y0+1; y1<A.size(); y1++) {
            maxV=max(maxV, findMaxColumn(y0, y1, B));
        }
    return maxV;
}

tuple<int, int, int> Hard::findMaxBlackBorderSquare(const vector<vector<int> > &A) {
    printMatrix(A);
    tuple<int, int, int> res;
    vector<vector<pair<int,int> > > B(A.size(), vector<pair<int, int> >(A.front().size()));

    for (int i=A.size()-1; i>=0;  i--)
        for (int j=A.front().size()-1; j>=0; j--) {
            if (A[i][j]==1) {
                B[i][j]=pair<int, int>(0, 0);
                continue;
            }

            int rowValue = 1 + (i==A.size()-1 ? 0 : B[i+1][j].first);
            int colValue = 1 + (j==A.front().size()-1 ? 0 : B[i][j+1].second);
            B[i][j]=pair<int, int>(rowValue, colValue);
        }

//    cout << endl;
//    for (int i=A.size()-1; i>=0;  i--)
//        for (int j=A.front().size()-1; j>=0; j--) {
//            cout << B[i][j].first << "," << B[i][j].second << endl;
//        }
    cout << endl;

    for (int size=A.size(); size>=1; size--)
        for (int i=0; i<A.size()-size;  i++)
            for (int j=0; j<A.front().size()-size; j++) {
//                cout << i << "," << j << ":" << B[i][j].first << ":" << B[i][j].second << endl;

                if (B[i][j].first<size || B[i][j].second<size)
                    continue;
                if (B[i+size-1][j].second<size)
                    continue;
                if (B[i][j+size-1].first<size)
                    continue;
                return tuple<int, int, int>(i, j, size);
            }

    return res;
}
