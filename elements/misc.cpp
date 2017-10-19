#include "misc.h"
#include <stack>
#include "utilities.hpp"
#include <stdexcept>
#include <set>
#include <cstring>
#include <climits>
#include <list>
#include <numeric>

Misc::Misc()
{
}

bool Misc::checkPushPop(const vector<int> &pushV, const vector<int> &popV) {
    int pushCurr=0, popCurr=0;
    stack<int> buff;
    while (popCurr<popV.size()) {
        while ((buff.empty() || buff.top() != popV[popCurr]) && pushCurr<pushV.size()) {
            buff.push(pushV[pushCurr++]);
        }
        if (buff.top() == popV[popCurr]) {
            buff.pop();
            popCurr++;
            continue;
        }
        else
            return false;
    }
    return buff.empty();

}

void Misc::ArrayToOddEvenArray(vector<int> &A) {
    printVector<int>(A);
    int left=0, right=A.size()-1;

    while (left<right) {
        while (A[left] & 1)
            left++;
        while (A[right] & 1 == 0)
            right--;

//        cout << left << "," << right << endl;
        if (left<right) {
            swap(A[left], A[right]);
            left++;
            right--;
        }
    }
    printVector<int>(A);

}

void Misc::findContinuousSequence(const vector<int> &A, int k) {
    vector<int> psum;
    partial_sum(A.begin(), A.end(), back_inserter(psum));

    int left=0, right=1;
    while( right < A.size() && left <= right) {
        int sum=psum[right]-psum[left]+A[left];
        if (sum==k) {
            printVector(vector<int>(A.begin()+left, A.begin()+right+1));
            left++;
            right++;
        }
        else if (sum<k) {
            right++;
        } else
            left++;

    }
}

void Misc::findContinuousSequence2(int n, int k) {
    int left=1, right=2;
    while( right <=n && left <= right) {
        int sum=(right+left)*(right-left+1)/2;
        if (sum==k) {
            for (int i=left; i<=right; i++)
                cout << i << " ";
            cout << endl;
            left++;
            right++;
        }
        else if (sum<k) {
            right++;
        } else
            left++;

    }
}

void Misc::findContinuousSequence3(int n) {
    if (n<3)
        return;
    int left=1, right=2;
    int sum = left+right;
    int middle = (n+1) >>1;
    while( left <middle) {
        if (sum==n) {
            for (int i=left; i<=right; i++)
                cout << i << " ";
            cout << endl;
            sum -= left;
            left++;
        }
        else if (sum<n) {
            right++;
            sum += right;
        } else {
            sum -= left;
            left++;
        }

    }
}

struct CirNode {
    int val;
    shared_ptr<CirNode> next;
    CirNode(int v, shared_ptr<CirNode> ptr): val(v), next(ptr) {}
};

int Misc::findLastElmentInRemove(vector<int> &A, int k) {
    if (k<=0 || A.empty())
        throw invalid_argument("k is less than or equal 0 and/or array is empty");
    shared_ptr<CirNode> pre=nullptr, root=nullptr;
    for (int i=0; i<A.size(); i++) {
        if (i==0) {
            root = shared_ptr<CirNode>(new CirNode(A[0], nullptr));
            pre=root;
        } else {
            shared_ptr<CirNode> node(new CirNode(A[i], nullptr));
            pre->next=node;
            pre=node;
        }
    }
    pre->next = root;
    cout << root->val << "," << pre->val << endl;

    while (root->next != root) {
        pre=root;
        int n=0;
        while (root->next != root && n<k) {
            n++;
            pre=root;
            root=root->next;
        }
        root = root->next;
        cout << pre->val << "," << pre->next->val << "," << root->val << endl;
        cin.get();
        pre->next = root;
    }
    cout << root->val << endl;
}

int Misc::findLastElmentInRemove_efficient(vector<int> &A, int k) {
    if (k<0 || A.empty())
        throw invalid_argument("k is less than or equal 0 and/or array is empty");

    int start=0;

    while(A.size()>1) {
        cout << A[(start+k)%A.size()] << endl;
        A.erase(A.begin()+(start+k)%A.size());
        start += k;
    }
    return A[0];

}

static int findDigit_from1ToN_helper(int n, int i, int digit) {
    int power10=pow(10, i);
    int powerNext10=power10*10;
    int right = n%power10;

    int roundDown = n- n%powerNext10;
    int roundUp = roundDown + powerNext10;

    int num = n/power10 % 10;
    if (num<digit)
        return roundDown /10;
    else if (num==digit)
        return roundDown +right +1;
    else
        return roundUp / 10;

}

int Misc::findDigit_from1ToN(int n, int digit) {
    int m=0;

    for (int i=0; i<to_string(n).size(); i++)
        m += findDigit_from1ToN_helper(n, i, digit);

    return m;
}

int Misc::Fibonacci(int n) {
    if (n<0)
        throw invalid_argument("n<0");
    if (n==0 || n==1)
        return n;

    int x0=0, x1=1;
    int res;
    for (int i=2; i<=n; i++) {
        res=x0+x1;
        x0=x1;
        x1=res;
    }
    return res;
}

int Misc::StairJump(int n, const vector<int> &ways) {
    if (n<=0)
        throw invalid_argument("n<=0");

    vector<int> table(n+1, 0);
    table[0]=1;
    for (int i=1; i<=n; i++) {
        for (auto &x : ways) {
            table[i] += i<x ? 0 : table[i-x];
        }
    }
    return table.back();
}

bool isValidDigit(const char x) {
    return x>='0' && x<='9';
}

int Misc::StrToInt(const string str) {
    int num=0;
    bool neg=false;
    if (str[0]=='-') {
        neg=true;
    }

    for (int i=(neg?1:0); i<str.length(); i++) {
        char x = str[i];
        if (!isValidDigit(x))
            throw invalid_argument("input is not valid digit string");

        num = num * 10 + (x-'0');
    }

    return neg ? -num : num;
}

struct Node {
    int t;
    enum direction{
        init, left, top, lefttop
    } direct;
    Node() : t(0), direct(init) {}
};

void printTable(vector<vector<Node> > table) {
    for (int i=0; i<table.size(); i++)  {
        for (int j=0; j<table[i].size(); j++) {
            cout << table[i][j].t << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string Misc::findLongestCommonSubsequence(const string x, const string y) {
    vector<vector<Node> > table(x.size(), vector<Node>(y.size(), Node()));
//    printTable(table);

    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++) {
            if (x[i]==y[j]) {
                table[i][j].t = (i<1 || j<1 ? 1 : 1+table[i-1][j-1].t);
                table[i][j].direct = Node::lefttop;
            }
            else {
                if (i==0 && j==0) {
                    table[i][j].direct = Node::lefttop;
                } else if (i==0) {
                    table[i][j].t = table[i][j-1].t;
                    table[i][j].direct = Node::left;
                } else if (j==0) {
                    table[i][j].t = table[i-1][j].t;
                    table[i][j].direct = Node::top;
                } else {
                    if (table[i-1][j].t > table[i][j-1].t) {
                        table[i][j].t = table[i-1][j].t;
                        table[i][j].direct = Node::top;
                    } else {
                        table[i][j].t = table[i][j-1].t;
                        table[i][j].direct = Node::left;
                    }
                }
            }
        }
//    printTable(table);
//    cin.get();

    string str;
    int xi=x.size()-1, yi=y.size()-1;
    while (xi>=0 && yi>=0) {
        if (x[xi]==y[yi])
            str = x[xi]+str;

        if (table[xi][yi].direct==Node::left)
            xi--;
        else if (table[xi][yi].direct==Node::top)
            yi--;
        else {
            xi--;
            yi--;
        }
//        cout << xi << " " << yi << " " << str << endl;
//        cin.get();
    }

    return str;

}

string Misc::findLongestCommonSubarray(const string x, const string y) {
    vector<vector<Node> > table(x.size(), vector<Node>(y.size(), Node()));
//    printTable(table);

    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++) {
            if (x[i]==y[j]) {
                table[i][j].t = (i<1 || j<1 ? 1 : 1+table[i-1][j-1].t);
            }
        }
//    printTable(table);
//    cin.get();

    string str;
    int maxLen=0;

    for (int xi=x.size()-1; xi>=0; xi--) {
        for (int yi=y.size()-1; yi>=0; yi--) {
            if (maxLen<table[xi][yi].t) {
                maxLen=table[xi][yi].t;
                str = x.substr(xi-maxLen+1, maxLen);
//                cout << maxLen << " " <<  xi<< " " << yi << " " << str << endl;
            }
//            cout << maxLen << " " <<  xi<< " " << yi << " " << str << endl;
        }
    }

    return str;

}

void Misc::printUglyNum(int k) {
    if (k==0)
        return;
    int count = 0;
    set<int> table;
    table.insert(2);
    table.insert(3);
    table.insert(5);
    vector<int> factors{2,3,5};
    while (count<k) {
        auto it = table.begin();
        int x = *it;
        cout << count << " " << x << endl;
        for (auto & n : factors) {
            table.insert(x*n);
        }
        table.erase(it);
        count++;
    }
}

static void printnum(string & num) {
    cout << stoi(num) << endl;
}

static void printNDigits_helper(string & num, int index) {
    if (index==num.length()) {
        printnum(num);
        return;
    }
    for (int i=0; i<10; i++) {
        num[index] = i+'0';
        printNDigits_helper(num, index+1);
    }
}

void Misc::printNDigits(int n) {
    string num(n, '0');

    printNDigits_helper(num, 0);
}

void pushBottom(stack<int> &s, int x) {
    if (s.empty()) {
        s.push(x);
        return;
    }

    int top = s.top();
    s.pop();
    pushBottom(s, x);
    s.push(top);
}

void Misc::reverseStack(stack<int> &s) {
    if (s.size()<=1) return;
    int x = s.top();
    s.pop();
    reverseStack(s);
    pushBottom(s, x);
}

static bool CompFunc(int a, int b) {
    string as = to_string(a);
    string bs = to_string(b);
    return strcmp((as+bs).c_str(), (bs+as).c_str())<0;
}

void Misc::findMinIntCombination(vector<int> &a) {
    sort(a.begin(), a.end(), CompFunc);

    for (auto &x : a)
        cout << x;
    cout << endl;

}

int Misc::minRotateSortArray(const vector<int> &a) {
    int left=0, right=a.size()-1;

    while (right-left>1) {
        cout << left << " " << right << endl;
        int mid = left+((right-left) >>1);
        if (a[mid]>a[right])
            left=mid+1;
        else if (a[mid]<a[right])
            right=mid;
        else {
            if (a[left]<a[mid])
                right = mid;
            return a[mid];
        }
    }
    return a[left]<a[right]?a[left]:a[right];
}

int Misc::Temp::N=0;
int Misc::Temp::sum=0;

int Misc::addWithConstrains(int n) {
    Temp::reset();
    Temp * d = new Temp[n];
    delete [] d;
    return Temp::getSum();
}

void calcProbDices_helper(int nDice, int index, int sum, vector<int> & table) {
    if (index>=nDice) {
        table[sum-nDice]++;
        return;
    }

    for (int i=1; i<=6; i++)
        calcProbDices_helper(nDice, index+1, sum+i, table);
}

void Misc::calcProbDices(int nDice) {
    int total=pow(6, nDice);
    vector<int> table(6*nDice-1*nDice+1, 0);
    calcProbDices_helper(nDice, 0, 0, table);
    double p=0;
    for (int i=0; i<table.size(); i++) {
        p+=double(table[i])/total;
        cout << i+nDice << ": " << double(table[i])/total << endl;
    }
    cout << p << endl;
}

void Misc::calcProbDices_DP(int nDice) {
    vector<vector<int> > table(2, vector<int>(nDice*6+1, 0));
    table[0][0]=1;

    int m=1;
    for (int i=1; i<=nDice; i++) {
        for (int j=i*6; j>=i; j--) {
            table[m][j]=0;
            for (int k=1; k<=6; k++)
                table[m][j]=table[m][j]+(j-k<0 ? 0 : table[1-m][j-k] );
        }
        m=1-m;
//        copy(table.begin(), table.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
    }
    int total = pow(6, nDice);
//    copy(table.begin(), table.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;

    for (int i=nDice; i<=nDice*6; i++)
        cout << double(table[1-m][i])/total << endl;
    cout << endl;
}

double powDouble_positiveExp(double base, int exp) {
    if (exp==0)
        return 1.;
    else if (exp==1)
        return base;

    double y = powDouble_positiveExp(base, exp<<1);
    y *= y;
    if (exp &1)
        y *= base;

    return y*y;

}

double Misc::powDouble(double x, int exp) {
    if (exp<0) {
        if (x==0)
            throw invalid_argument("base=0, and exp<0");
        return 1/powDouble_positiveExp(x, -exp);
    } else
        return powDouble_positiveExp(x, exp);
}

shared_ptr<Misc::Singleton> Misc::Singleton::instance=nullptr;

void checkSymmetry(string & s, int left, int right, int &longestLen) {
    while (left>=0 && right < s.size()) {
        if (s[left]!=s[right])
            break;
        longestLen = max(longestLen, right-left+1);
        left--;
        right++;
    }
}

void getLongestSymmetrySubString_helper(string & s, int pos, int &longestLen) {
    int left=pos-1;
    int right=pos;
    // even len
    checkSymmetry(s, left, right, longestLen);
    left = pos-1;
    right = pos+1;
    checkSymmetry(s, left, right, longestLen);
}

int Misc::getLongestSymmetrySubString(string s) {
    if (s.size()<=1) return s.size();

    int longestLen=1;
    for (int i=1; i<s.size(); i++) {
        getLongestSymmetrySubString_helper(s, i, longestLen);
    }

    return longestLen;
}


int Misc::findMajorityNum(const vector<int> & A) {
    if (A.empty())
        throw invalid_argument("empty vector");

    int count = 1;
    int x = A[0];
    for (int i=1; i<A.size(); i++) {
        if (A[i]==x)
            count ++;
        else {
            count--;
            if (count==0) {
                count = 1;
                x= A[i];
            }
        }
    }
//    cout << count << " " << x << endl;

//    if (count<=A.size()/2)
//        throw invalid_argument("there is no majority number");

    return x;
}

shared_ptr<Misc::ComplexNode> Misc::copyComplexNode(shared_ptr<ComplexNode> &head) {
    if (!head || !head->next) return head;

    shared_ptr<ComplexNode> curr = head;
    while (curr) {
        shared_ptr<ComplexNode> next = curr->next;
        curr->next=shared_ptr<ComplexNode>(new ComplexNode(curr->value));
        curr = curr->next;
        curr->next=next;
        curr= curr->next;
    }

    curr= head;
    while (curr->next) {
        shared_ptr<ComplexNode> next = curr->next;
        next->sibling = curr->sibling->next;
        curr = next->next;
    }

    curr=head;
    shared_ptr<ComplexNode> copyhead = curr->next;
    while (curr->next) {
        shared_ptr<ComplexNode> next = curr->next;
        curr->next=next->next;
        if (curr->next)
            next->next = curr->next->next;
        curr=curr->next;
    }
    return copyhead;

}

bool treeMatch(shared_ptr<Misc::tNode> &big, shared_ptr<Misc::tNode> & small) {
    if (!small) return true;
    if (!big) return false;
    if (big->data != small->data)
        return false;
    return treeMatch(big->left, small->left) && treeMatch(big->right, small->right);
}

bool Misc::isSubTree(shared_ptr<tNode> &big, shared_ptr<tNode> &small) {
    if (!small) return true;
    if (!big) return false;
    bool result=false;
    if (small->data == big->data)
        result=treeMatch(big, small);
    if (!result && big->left)
        result = treeMatch(big->left, small);
    if (!result && big->right)
        result = treeMatch(big->right, small);
    return result;

}

bool isValid(int y, int x, vector<vector<bool> > &table) {
    return y>=0 && y<table.size() && x>=0 && x<table.front().size() && table[y][x];
}

void Misc::printMatrixClockwisely(const vector<vector<int> > &A) {
    if (A.empty()) return;

    vector<vector<bool> > table(A.size(), vector<bool>(A.front().size(), true));
    vector<pair<int, int> > direction{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int i=0;
    pair<int, int> d=direction[0];
    int x=0, y=0;
    while (table[y][x]) {
        cout << A[y][x] << " ";
        table[y][x]=false;
        if (!isValid(y+d.first, x+d.second, table))
            d=direction[(++i)%4];
        y=y+d.first;
        x=x+d.second;
    }
    cout << endl;
}

int Misc::maxDiff_DP(const vector<int> &A) {
    if (A.size()<2)
        throw invalid_argument("the vector size is less than 2");

    int maxV=A[0];
    int maxDif=INT_MIN;
    for (int i=1; i<A.size(); i++) {
        maxDif = max(maxDif, maxV-A[i]);
        maxV = max(maxV, A[i]);
//        cout << maxV << " " << maxDif << endl;
    }
    return maxDif;

}

void maxDiff_divide_helper(const vector<int> &A, int left, int right, int &maxV, int &minV, int &maxdiff) {
    if (left==right) {
        maxV=A[left];
        minV=A[left];
        maxdiff=INT_MIN;
        return;
    }
    int mid=left+((right-left)>>1);
    int minVL, maxVL, maxdiffL, maxVR, minVR, maxdiffR;
    maxDiff_divide_helper(A, left, mid, maxVL, minVL, maxdiffL);
    maxDiff_divide_helper(A, mid+1, right, maxVR, minVR, maxdiffR);

    maxV=max(maxVL, maxVR);
    minV=min(minVL, minVR);
    maxdiff = max( max(maxdiffL, maxdiffR), maxVL-minVR);

}

int Misc::maxDiff_divide(const vector<int> &A) {
    if (A.size()<2)
        throw invalid_argument("the vector size is less than 2");
    int maxV, minV, maxdiff;
    maxDiff_divide_helper(A, 0, A.size()-1, maxV, minV, maxdiff);
    return maxdiff;
}

int findMaxSubarr(const vector<int> &diff) {
    int sum=0, maxSum=INT_MIN;
    for (auto & x: diff) {
        sum += x;
        maxSum = max(maxSum, sum);
        sum = max(sum, 0);
    }
    return maxSum;
}

int Misc::maxDiff_subArray(const vector<int> &A) {
    if (A.size()<2)
        throw invalid_argument("the vector size is less than 2");

    vector<int> diff;
    for (int i=1; i<A.size(); i++) {
        diff.push_back(A[i-1]-A[i]);
    }

    return findMaxSubarr(diff);
}

void printTreePathSum_helper(shared_ptr<Misc::tNode> & root, list<int> & path, int k, int sum) {
    if (!root) {
        if (sum==k) {
            for (auto &x: path)
                cout << x << " ";
            cout << endl;
        }
        return;
    }
    path.push_back(root->data);
    printTreePathSum_helper(root->left, path, k, sum+root->data);
    printTreePathSum_helper(root->right, path, k, sum+root->data);

    path.pop_back();
}

void Misc::printTreePathSum(shared_ptr<tNode> &root, int k) {
    list<int> path;
    int sum=0;
    printTreePathSum_helper(root, path, k, sum);
}
