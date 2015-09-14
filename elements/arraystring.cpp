#include "arraystring.h"
#include <iostream>
#include <climits>
#include <map>
#include <numeric>
#include <algorithm>
#include <stdexcept>

ArrayString::ArrayString()
{
}

void ArrayString::dutch_flag_partition(vector<int> &A, int i)
{
    int s=0, e=0, l=A.size()-1;
    int pivot=A[i];
    while (e<=l) {
        if (A[e]<pivot) {
            swap(A[e++], A[s++]);
        } else if (A[e]==pivot)
            e++;
        else
            swap(A[e], A[l--]);

    }
}

static int countOne_backward(const vector<char> &A, int idx) {
    if (idx<0 || ((A[idx]>>7)&1==0))
        return 0;
    return 1+countOne_backward(A, idx-1);
}

/**
 * @brief ArrayString::isChineseSequence, from the last word, Chinese letter has two byte which the first bit of 1,
 *and Englishe has one byte where the first bit is 0
 *
 * @param A byte array
 * @return true if chinese, and otherwise false;
 */
bool ArrayString::isChineseSequence(const vector<char> &A) {
    if (A.empty())
        throw invalid_argument("invalid input");
    char x=A.back();
    if ((x>>7)&1)
        return true;
    else {
        int n = countOne_backward(A, A.size()-2);
        if (n&1)
            return true;
        else
            return false;
    }


}

void ArrayString::replace_remove(string &s) {
    int count=0;
    int len = s.size();
    for (auto &c : s) {
        if (c=='a')
            count+=2;
        else if (c!='b')
            count++;
    }
    s.resize(count);
    for (int i=count-1, j=len-1; j>=0; j--) {
        if (s[j]=='a') {
            s[i--]='d';
            s[i--]='d';
        } else if (s[j] != 'b')
            s[i--]=s[j];
    }
}

static void copy_patch(vector<vector<int> > &A, int Ays, int Aye, int Axs, int Axe, vector<vector<int> > &D, int Dys, int Dxs) {
    int len=Axe-Axs;// ymid=Ays+half, xmid=Axs+half;
    for (int i=0; i<Aye-Ays; i++) {
        copy(A[Ays+i].begin()+Axs, A[Ays+i].begin()+Axs+len, D[Dys+i].begin()+Dxs);
    }

}

static void rotate2DArray_helper(vector<vector<int> > &A, int ys, int ye, int xs, int xe) {
    if (ye>ys+1) {
        int half=(ye-ys)>>1;
        int midy=ys+half, midx=xs+half;
        vector<vector<int> > temp(half, vector<int>(half)); // the lefttop patch;
        copy_patch(A, ys, midy, xs, midx, temp, 0, 0);
        copy_patch(A, midy, ye, xs, midx, A, ys, xs);
        copy_patch(A, midy, ye, midx, xe, A, midy, xs);
        copy_patch(A, ys, midy, midx, xe, A, midy, midx);
        copy_patch(temp, 0, half, 0, half, A, ys, midx);

        rotate2DArray_helper(A, ys, ys+half, xs, xs+half);
        rotate2DArray_helper(A, midy, ye, xs, xs+half);
        rotate2DArray_helper(A, midy, ye, midx, xe);
        rotate2DArray_helper(A, ys, ys+half, midx, xe);
    }
}

void ArrayString::rotate2DArray_recursive(vector<vector<int> > &A)
{
    rotate2DArray_helper(A, 0, A.size(), 0, A.size());
}

void ArrayString::rotate2DArray(vector<vector<int> > &A) {
    if (A.size()!=A.front().size()) throw string("invalid input");
    int size=A.size();
    for (int y=0; y<(A.size()>>1); y++)
        for (int x=y; x<A.size()-1-y; x++) {
            int temp=A[y][x];
            A[y][x]=A[size-1-x][y];
            A[size-1-x][y]=A[size-1-y][size-1-x];
            A[size-1-y][size-1-x]=A[x][size-1-y];
            A[x][size-1-y]=temp;
        }
}

void ArrayString::printMatrixInSpiralOrder(vector<vector<int> > &arr)
{
    vector<pair<int, int> > shift;
    shift.push_back(pair<int,int>(0, 1));
    shift.push_back(pair<int,int>(1, 0));
    shift.push_back(pair<int,int>(0, -1));
    shift.push_back(pair<int,int>(-1, 0));

    int x=0, y=0, dir=0;
    for (int i=0; i<arr.size()*arr[0].size(); i++)
    {
        cout << arr[y][x] << " ";
        arr[y][x]=-1;
        int ny=y+shift[dir].first;
        int nx=x+shift[dir].second;
        if (ny<0 || ny>=arr.size() || nx<0 || nx>=arr[0].size() || arr[ny][nx]==-1)
        {
            dir = (dir+1)%4;
            ny=y+shift[dir].first;
            nx=x+shift[dir].second;
        }
//        cout << ny << " " << nx << endl;
//        cin.get();
        y=ny;
        x=nx;
    }
}

int ArrayString::subStringSearch_Rabin_Karp(string &t, string &s)
{
    if (t.size()<s.size()) return -1;

    int kMod=977;
    int base=26;

    int t_hash=0, s_hash=0, powerS=1;
    for (int i=0; i<s.size(); i++)
    {
        powerS = i ? powerS*base % kMod : 1;
        t_hash=(t_hash*base + t[i]) % kMod;
        s_hash=(s_hash*base + s[i]) % kMod;
    }

    for (int i=0; i<t.size()-s.size(); i++)
    {
        if (t_hash==s_hash && !t.compare(i-s.size(), s.size(), s))
            return i-s.size();

        t_hash -= t[i-s.size()]*powerS % kMod;
        if (t_hash<0)
            t_hash += kMod;

        t_hash = (t_hash*base+t[i]) % kMod;

    }

    if (t_hash==s_hash && t.compare(t.size()-s.size(), s.size(), s)==0)
        return t.size()-s.size();

    return -1;
}

static bool match2D(vector<vector<int> > &s, vector<vector<int> > &t, int y, int x) {
    int h=s.size();
    int w=s.front().size();
    for (int i=0; i<h; i++)
        for (int j=0; j<w; j++) {
            if (s[i][j]!=t[y+i][x+j])
                return false;
        }
    return true;

}

pair<int, int> ArrayString::sub2DSquareSearch_Rabin_Karp(vector<vector<int> > &t, vector<vector<int> > &s) {
    if (s.empty())
        return pair<int, int>(0,0);
    if (s.size()>t.size() || s.front().size() > t.front().size())
        return pair<int, int>(-1,-1);
    int base=26, mod=997;
    int scode=0;
    int hpow=1;
    int size = s.size();
    for (int i=0; i<s.size(); i++)
        for (int j=0; j<s.front().size(); j++) {
            hpow = !i && !j ? 1 : (hpow*base) % mod;
            scode = (scode *base + s[i][j]) % mod;
        }

    int tcode=0;
    for (int i=s.size(); i<t.size(); i++) {
        // tcode
        tcode=0;
        for (int y=0; y<s.size(); y++)
            for (int x=0; x<s.front().size(); x++) {
                tcode = (tcode*base + t[i-size+y][x]) % mod;
            }

        for (int j=s.front().size(); j<t.front().size(); j++) {
            if (tcode == scode && match2D(s, t, i-s.size(), j-s.front().size()))
                return pair<int, int>(i-s.size(),j-s.front().size());
            for (int k=i-size; k<i; k++)
                tcode -= t[k][j-size]*hpow % mod;
            for (int k=i-size; k<i; k++)
                tcode = (tcode & base + t[k][j]) % mod;
        }
    }

    if (tcode==scode && match2D(s, t, t.size()-s.size(), t.front().size()-s.front().size()))
        return pair<int, int>(t.size()-s.size(), t.front().size()-s.front().size());

    return {-1, -1};

}

string ArrayString::deleteBreplaceA(string s)
{
    int index=0, a_count=0;
    for (auto c : s)
    {
        if (c != 'b')
            s[index++]=c;
        if (c == 'a')
            a_count++;
    }

    int len=index+a_count;
    s.resize(len);
    int curIndex = index-1;
    int writeIndex=s.size()-1;
    while (curIndex>=0)
    {
        if (s[curIndex]=='a')
        {
            s[writeIndex--]='d';
            s[writeIndex--]='d';
        }
        else
            s[writeIndex--]=s[curIndex];

        curIndex--;
    }

    return s;
}

void ArrayString::convertPhoneNumberToString(string &num, string &s, vector<string> & result)
{
    if (s.size()==num.size())
    {
        result.push_back(s);
        return;
    }
    vector<string> phonePad;
    phonePad.push_back("ABC");
    phonePad.push_back("DEF");
    phonePad.push_back("GHI");
    phonePad.push_back("IJL");
    phonePad.push_back("MNO");
    phonePad.push_back("PQRS");
    phonePad.push_back("TUV");
    phonePad.push_back("WXYZ");

    char c=num[s.size()];
    int index=c-'0';
    for (auto t : phonePad[index])
    {
        s.push_back(t);
        convertPhoneNumberToString(num, s, result);
    }

}

static bool isMatch(string r, string s)
{
//    cout << r << "-" << s << endl;
    if (r.empty()) return s.empty();  // note the difference between next line: this line is exact match
//    if (r.empty()) return true;

    if (r[0]=='$')
        return s.empty();

    if(r.size()>=2 && r[1]=='*')
    {
        for (int i=0; i<s.size() && (r[0]=='.' || r[0]==s[i]); i++)
        {
            cout << r[0] << "+" << s[0] << endl;
            if( isMatch(r.substr(2), s.substr(i+1)))  // note the difference between line 273: Line 273 is better implem to me
                return true;
        }
        return isMatch(r.substr(2), s);
    }

    if(r.size()>=2 && r[1]=='+')
    {
//        return !s.empty() && (r[0]=='.' || r[0]==s[0]) && isMatch(r, substr(1))
        for (int i=0; i<s.size() && (r[0]=='.' || r[0]==s[i]); i++)
        {
//            cout << r[0] << "+" << s[0] << endl;
            if( isMatch(r.substr(2), s.substr(i+1)))
                return true;
        }
        return false;
    }

    return !s.empty() && (r[0]=='.' || r[0]==s[0]) && isMatch(r.substr(1), s.substr(1));
}

bool ArrayString::regexMatch(string &r, string &s)
{
    cout << r << "-" << s << endl;
    return isMatch(r, s);

//    if (r.empty()) return true;
//    if (s.empty()) return false;

    if (r[0] == '^')
        return isMatch(r.substr(1), s);

    for (int i=0; i<s.size(); i++)
    {
        if (isMatch(r, s.substr(i))) return true;
    }

    return false;
}

int ArrayString::maxProfitKBuySell(const vector<int> &price, int k)
{
    vector<int> k_sum(k<<1, INT_MIN);
    for (int i=0; i<price.size(); i++)
    {
        vector<int> pre_k_sum(k_sum);
        for (int j=0, sign=-1; j<k_sum.size() && j<i; j++, sign *=-1) {
            int diff = sign*price[j] + j==0 ? 0 : pre_k_sum[j-1];
            k_sum[j] = max(diff, pre_k_sum[j]);
        }
    }
    return k_sum.back();
}

int ArrayString::maxProfit2BuySell(const vector<int> & price) {
    vector<int> forward_max(price.size(), INT_MIN);
    int minPrice=INT_MAX, maxProfit=INT_MIN;
    for (int i=0; i<price.size(); i++) {
        forward_max[i]= max(i==0? 0: price[i]-minPrice, maxProfit);
        minPrice = min(price[i], minPrice);
    }
    vector<int> backward_max(price.size(), INT_MIN);
    int maxPrice=INT_MIN;
    maxProfit=INT_MIN;
    for (int i=price.size()-1; i>=0; i--) {
        backward_max[i]= max(i==price.size()-1? 0: maxPrice-price[i], maxProfit);
        maxPrice = max(price[i], maxPrice);
    }
    maxProfit=INT_MIN;
    for (int i=1; i<price.size()-2; i++) {
        int profit=forward_max[i]+backward_max[i+1];
        maxProfit = max(profit, maxPrice);
    }
    return maxProfit;
}

int ArrayString::maxProfitUnlimitBuySell(const vector<int> &price)
{
    if (price.size()<2) return 0;

    int profit=0, buy=price.front();
    for (int i=1; i<price.size()-1; i++)
    {
        if (price[i]>price[i-1] && price[i]>price[i+1]) {
            profit += price[i]-buy;
            buy=price[i+1];
        }  else if (price[i]<price[i-1] && price[i]<price[i+1])
            buy=price[i];
    }

    if (price.back()>buy)
        profit += price.back()-buy;

    return profit;
}

vector<int> ArrayString::find_0_mod_sum_subset(const vector<int> &A)
{
    vector<int> prefix_sum;
    partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));
//    for_each(prefix_sum.begin(), prefix_sum.end(), [](int x){return x%A.size();});
    for (int i=0; i<A.size(); i++) {
        prefix_sum[i] %= A.size();
    }

    map<int, int> table;
    for (int i=0; i<A.size(); i++) {
        if (prefix_sum[i]=0)
        {
            vector<int> ans(i+1);
            iota(ans.begin(), ans.end(), 0);
            return ans;
        } else if (table.find(prefix_sum[i]) != table.end()) {
            vector<int> ans(i-table[prefix_sum[i]]);
            iota(ans.begin(), ans.end(), table[prefix_sum[i]]+1);
            return ans;
        }
        table[prefix_sum[i]]=i;
    }
    return vector<int>();
}

pair<int, int> ArrayString::find_longest_increase_subarray(const vector<int> &A) {
    if (A.empty()) throw string("invalid input");
    pair<int,int> longest(pair<int, int>(0,0)), curr(longest);
    if (A.size()==1) return longest;
    int maxLen=1, i=1;
    while (i<A.size()) {
        if (A[i]<A[i-1]) {
            curr.first=i;
        }
        curr.second=i;

        if (longest.second-longest.first<curr.second-curr.first)
            longest=curr;

        i++;
    }
    return longest;
}

pair<int, int> ArrayString::find_longest_increase_subarray_efficient(const vector<int> &A) {
    if (A.empty()) throw string("invalid input");
    pair<int,int> ans(pair<int, int>(0,0));
    if (A.size()==1) return ans;
    int maxLen=1, i=0;
    while (i<A.size()) {
        bool isSkipable=false;
        // check backward
        for (int j=i+maxLen-1; j>=i; j--) {
            if (j+1>A.size() || A[j]>A[j+1]) {
                i=j+1;
                isSkipable=true;
                break;
            }
        }

        // check forward
        if (!isSkipable) {
            i=i+maxLen-1;
            while (i+1<A.size() && A[i]<A[i+1]) {
                i++;
                maxLen++;
            }
            ans=pair<int, int>(i-maxLen+1, i);
        }

    }
    return ans;
}

static int backtrace(vector<int> &F, int idx) {
    while (F[idx] != idx)
        idx=F[idx];
    return idx;
}

vector<int> ArrayString::compute_equivalence_classes(int n, const vector<int> &A, const vector<int> &B)
{
    vector<int> F(n);
    iota(F.begin(), F.end(), 0);

    for (int i=0; i<A.size(); i++) {
        int a = backtrace(F, A[i]);
        int b = backtrace(F, B[i]);
        if (a<b) {
            F[b]=a;
        } else
            F[a]=b;
    }

    for (int i=0; i<F.size(); i++) {
        if (F[i] != i)
            F[i] = backtrace(F, i);
    }
    return F;
}

void ArrayString::apply_permutation( vector<int> &A, vector<int> &perm) {
    for ( int i=0; i<A.size(); i++) {
        if (perm[i]>=0) {
            int a = i;
            int temp = A[i];

            do {
                int next_a = perm[a];
                int next_temp = A[next_a];
                A[next_a] = temp;
                perm[a] -= perm.size();
                a = next_a;
                temp = next_temp;

            } while (a != i);

        }
    }
    int s = perm.size();
    for_each(perm.begin(), perm.end(), [s](int &x){ x+=s;});
}
