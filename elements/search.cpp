#include <string>
#include <math.h>
#include <iostream>
#include "search.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <climits>
#include <sstream>
#include <bitset>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <random>

Search::Search()
{
}

pair<int, int> Search::findSubtractionPairInSortedArray(const vector<int> &A, int k)
{
    int s = 0, e =0;
    while (s<A.size() & e <A.size()) {
        int x = A[s]-A[e];
        if (x==k)
            return pair<int, int>(s, e);
        else if (x>k)
            e++;
        else
            s++;
    }
    return pair<int, int>(-1, -1);
}

void Search::drawLine(vector<char> & screen, int width, int y, int x1, int x2) {
//    int byteStart=(width*y+x1)/8 + (x1%8) ==0 ? 0: 1;
    int byteStart=min((width*y+x1)/8+1, (int)screen.size());
    int byteEnd=max((width*y+x2)/8-1, 0);

    for (int i=byteStart; i<=byteEnd; i++)
        screen[i]=char(0xFF);

    byteStart--;
    byteEnd++;
    int mask = 0xFF>>(x1%8);
    int mask2 = ~(0xFF>>(x2%8+1));
    if (byteStart==byteEnd) {
        screen[byteStart] |= mask & mask2 ;
    }
    else {
        screen[byteStart] |= mask;
        screen[byteEnd] |= mask2;
    }
}

static int find_missing_num_bits_helper(const vector<int> &A, int bitNum, int currBit) {
    if (currBit>=bitNum) return 0;

    vector<int> zeroBits, oneBits;
    for (auto x : A) {
        if (x & (1<<currBit)) {
            oneBits.push_back(x);
        } else
            zeroBits.push_back(x);
    }

    if (A[0] & 1 == 0) {
        if (zeroBits.size()<=oneBits.size())
            return find_missing_num_bits_helper(zeroBits, bitNum, currBit+1)<<1 | 0;
        else
            return find_missing_num_bits_helper(oneBits, bitNum, currBit+1)<<1 | 1;
    } else {
        if (zeroBits.size()>=oneBits.size())
            return find_missing_num_bits_helper(oneBits, bitNum, currBit+1)<<1 | 1;
        else
            return find_missing_num_bits_helper(zeroBits, bitNum, currBit+1)<<1 | 0;

    }
}

int Search::find_missing_num_bits(vector<int> &A, int bitNum) {
    return find_missing_num_bits_helper(A, bitNum, 0);
}

float Search::sqrt_bySearch(float x)
{
    if (x==0 || x==1) return x;
    if (x<0) throw string("Error: invalid input");

    float small=0, large=x;
    float middle=x/2;
    float error = x-middle*middle;

    float epi=1e-5;
    int itrNum=0;
    while (fabs(error)>epi && itrNum <10)
    {
        cout << small << " " << middle << " " << large << " " << error << endl;
        if (error>0)
            small = middle;
        else if (error<0)
            large = middle;
        else
            break;
        middle = (large+small)/2;
        error = x-middle*middle;

        itrNum++;
    }

    return middle;
}

double Search::computeUpperBoundForBurget(vector<double> &salaries, double burget)
{
    vector<double> accSum;
    sort(salaries.begin(), salaries.end(), less<double>());
    copy(salaries.begin(), salaries.end(), ostream_iterator<double>(cout, " "));
    cout << endl;
    partial_sum(salaries.begin(), salaries.end(), back_inserter(accSum));
    copy(accSum.begin(), accSum.end(), ostream_iterator<double>(cout, " "));
    cout << endl;



    return 0;
}

static pair<int, int> find_pos_neg_pair(const vector<int> &A, int k) {
    pair<int, int> ret(A.size()-1, A.size()-1);
    while (ret.first>=0 && A[ret.first]<0)
        ret.first--;
    while (ret.second>=0 && A[ret.second]>=0)
        ret.second--;

    while (ret.first>=0 && ret.second >=0) {
        int sum = A[ret.first]+A[ret.second];
        if ( sum == k)
            return ret;
        else if (sum < k) {
            do {
                ret.second--;
            } while (ret.second>=0 && A[ret.second]>=0);
        } else {
            do {
                ret.first--;
            } while (ret.first>=0 && A[ret.first] <0);
        }

    }

    return pair<int, int>(-1, -1);
}

template<typename Comp>
static pair<int, int> find_pair(const vector<int> &A, int k, Comp comp) {
    pair<int, int> ret(0, A.size()-1);
    while (ret.first<ret.second && comp(A[ret.first], 0))
        ret.first++;
    while (ret.first<ret.second && comp(A[ret.second], 0)) {
        ret.second--;
    }

    while (ret.first<ret.second) {
        int sum=A[ret.first]+A[ret.second];
        if (sum==k)
            return ret;
        else if (comp(sum, k)) {
            do {
                ret.first++;
            } while (ret.first<ret.second && comp(A[ret.first], 0));
        } else {
            do {
                ret.second--;
            } while (ret.first<ret.second && comp(A[ret.second], 0));
        }
    }
    return pair<int, int>(-1, -1);
}

pair<int, int> Search::find_pair_positivenegativeArray(const vector<int> &A, int k) {
    pair<int, int> ret = find_pos_neg_pair(A, k);
    if (ret.first == -1 && ret.second == -1)
        return k>=0 ? find_pair(A, k, less<int>()) : find_pair(A, k, greater_equal<int>());
}

int Search::find_start_circular_sorted_array(const vector<int> &A) {
    if (A.empty()) return -1;

    int s=0, e=A.size()-1;
    while (s<e) {
        int mid=s+((e-s)>>1);
        if (A[mid] < A[e])
            e=mid;
        else if (A[mid] > A[e])
            s=mid+1;
        else {
            // it is questionable see page 276
            if (A[s] < A[mid])
                e=mid-1;
            else
                return mid;
        }

    }
    return s;
}

//int Search::find_start_circular_sorted_array_duplicates(const vector<int> &A, int s, int e) {
//    if (A.empty()) return -1;
//    if (s==e) return s;

//    int m=s+((e-s)>>1);
//    if (A[m] > A[e])
//        return find_start_circular_sorted_array_duplicates(A, m+1, r);
//    else if (A[m] < A[e])
//        return find_start_circular_sorted_array_duplicates(A, s, m);
//    else {
//        int left = find_start_circular_sorted_array_duplicates(A, a, m);
//        int right = find_start_circular_sorted_array_duplicates(A, m+1, e);
//        return A[left]<A[right] ? left : right;

//    }


//}

int Search::binary_search_unknown_len(const vector<int> &A, int k) {
    int p=0;
    while (true) {
        int val = A[(1<<p)-1];
        try {
            if (val==k)
                return (1<<p)-1;
            if (val>k)
                break;
        } catch (exception & e) {
            break;
        }
        p++;
    }

    int s=1<<(p-1), e=(1<<p)-2;
    while (s<=e) {
        int m = s + ((e-s)>>1);
        try {
            if (A[m]<k)
                s=m+1;
            else if (A[m]>k)
                e=m-1;
            else
                return m;
        } catch (exception & ex) {
            e=m-1;
        }
    }
    return -1;
}

double Search::plan_for_budget(vector<double> &A, double budget) {
    sort(A.begin(), A.end());
    vector<double> partialSum;
    partial_sum(A.begin(), A.end(), back_inserter(partialSum));

    vector<double> plan;
    for (int i=0; i<partialSum.size(); i++)
        plan.push_back(partialSum[i]+A[i]*(partialSum.size()-i-1));

    auto idx=lower_bound(plan.begin(), plan.end(), budget);

    if (idx==plan.begin())
        return budget/A.size();
    else if (idx==plan.end())
        return -1;
    else {
        int t=distance(plan.begin(), idx);
        return A[t-1]+(budget-plan[t-1])/(A.size()-t);
    }
}

int Search::find_kth_two_sorted_arrays(const vector<int> &A, const vector<int> &B, int k) {
    int s = max(0, int(k-B.size()));
    int e = min(k, int(A.size()));

    while (s<e) {
        int x = s+((e-s)>>1);
        int A_x_1 = x>=0 ? A[x-1] : INT_MIN;
        int A_x = x<A.size() ? A[x] : INT_MAX;
        int B_k_x_1 = (k-x-1)>0 ? B[k-x-1]: INT_MIN;
        int B_k_x = (k-x) < B.size() ? B[k-x] : INT_MAX;

        if (A_x < B_k_x_1)
            s=x+1;
        else if (B_k_x < A_x_1)
            e=x-1;
        else {
            return max(A_x_1, B_k_x_1);
        }

    }
    int x=s;
    int A_x_1 = x>=0 ? A[x-1] : INT_MIN;
    int B_k_x_1 = (k-x-1)>0 ? B[k-x-1]: INT_MIN;
    return max(A_x_1, B_k_x_1);

}

int compare_eps(double a, double b) {
    double diff = (a-b)/b;
    return diff<-numeric_limits<double>::epsilon() ?
                -1 : diff>numeric_limits<double>::epsilon();
}

double Search::square_root(double x) {
    double s, e;
    if (x<1) {
        s=0;
        e=1;
    } else {
        s=1;
        e=x;
    }

    while (s<e) {
        double m = s+ ((e-s)*0.5);
        double v = m*m;
        if (compare_eps(v, x)==0)
            return m;
        else if (compare_eps(v,x)==1) {
            e = m;
        } else {
            s = m;
        }
    }
    return s;
}

double Search::division(double x, double y) {
    double s, e;
    if (x==y) return 1;
    else if (x<y) {
        s=0; e=1;
    } else {
        s=1; e=x;
    }

    while (s<e) {
        double m=s+((e-s)*0.5);
        double v=m*y;
        if (compare_eps(v, x)==0)
            return m;
        else if (compare_eps(v,x)==1) {
            e = m;
        } else {
            s = m;
        }
    }
    return s;
}

bool Search::matrix_search(const vector<vector<int> > &A, int x) {
    int r=0, c=A[0].size()-1;
    while (r<A.size() && c>=0) {
        if (A[r][c]==x)
            return true;
        else if (A[r][c]<x)
            r++;
        else
            c--;
    }
    return false;
}

// smaller: 0->s-1;
// equal: s->i-1;
// unclassified: i->e;
// larger: e-1->end
static int divideArray(vector<int>&A, int p, int s, int e) {
    int v=A[p];
    int larger=s;

    swap(A[p], A[e]);
    for (int i=0; i<e; i++) {
        if (A[i]>v)
            swap(A[i], A[larger++]);
    }
    swap(A[e], A[larger]);
    return larger;
}

int Search::find_kth_largest(vector<int> &A, int k) {
    int s=0, e=A.size()-1;

    random_device rd;
    default_random_engine gen(rd());

    while (s<=e) {
        uniform_int_distribution<int> dis(s, e);
        int p=dis(gen);
        int idx = divideArray(A, p, s, e);
        if (idx==k-1)
            return A[idx];
        else if (idx > k-1)
            e=idx-1;
        else
            s=idx+1;
    }
}

int Search::find_kth_largest_sequence(istringstream &sin, int k) {
    vector<int> M;
    int x;
    while (sin>>x) {
        if (M.size()>=2*k) {
            nth_element(M.begin(), M.begin()+k-1, M.end(), greater<int>());
            M.resize(k);
        }
        M.push_back(x);
    }
    nth_element(M.begin(), M.begin()+k-1, M.end(), greater<int>());
    cout << M[k-1];
}

int Search::find_missing_ipaddress(ifstream &sin) { //ifs
    vector<int> counter(1<<16, 0);
    int x;
    while (sin>>x) {
        ++counter[x>>16];
    }

    for (int i=0; i<counter.size(); i++) {
        if (counter[i]<(1<<16)) {
            bitset<(1<<16)> bits;
            sin.clear();
            sin.seekg(0, ios::beg);
            while (sin>>x) {
                if ((x>>16)==i)
//                    if ((x>>16)==counter[i])
                    bits.set(((1<<16)-1)& x);
            }
            sin.close();

            for (int k=0; k<(1<<16); k++) {
                if (bits.test(k)==0)
                    return (i<<16) | k;
            }

        }
    }
}

static int find_missing_ipaddress_2_helper(ifstream &ifs, int i) {
    bitset<(1<<16)> bits;
    ifs.clear();
    ifs.seekg(0, ios::beg);
    int x;
    while (ifs>> x) {
        if ((x>>16) == i) {
            bits.set(x&((1<<16)-1));
        }
    }

    for (int k=0; k<(1<<16); k++) {
        if (bits.test(k)==0)
            return (i<<16) | k;
    }
    ifs.close();
    return -1;
}

int Search::find_missing_ipaddress_2(ifstream & ifs) {
    vector<size_t> table(1<<16,0); //2^16*4(int)=2^18 byte, each unit can hold 2^32 (int) number;
                                    //1^16*1^16=2^32=4billion
    int x;
    while (ifs>>x) {
        table[x>>16]++;
    }

    // check 0-(1<<16-2) units
    for (int i=0; i<((1<<16)-1); i++) {
        if (table[i]<(1<<16)) {
            return find_missing_ipaddress_2_helper(ifs, i);
        }

    }
    // if not found so far, check (1<16)unit
    return find_missing_ipaddress_2_helper(ifs, (1<<16)-1);
}

// return {duplicate, missing}
pair<int,int> Search::find_missing_duplicate(const vector<int> &A) {
    int miss_dup_xor=0;
    for (int i=0;i<A.size(); i++)
        miss_dup_xor ^= i^A[i];

    int h = miss_dup_xor & (~(miss_dup_xor-1));

    int miss_dup=0;
    for (int i=0; i<A.size(); i++) {
        if (i&h)
            miss_dup ^= i;
        if (A[i]&h)
            miss_dup ^=A[i];
    }

    for (auto &a : A) {
        if (a==miss_dup)
            return pair<int, int>(miss_dup, miss_dup ^ miss_dup_xor);
    }
    return pair<int, int>(miss_dup^miss_dup_xor, miss_dup);
}

int Search::find_element_appear_once(const vector<int> &A) {
    int one=0, two=0, next_one, next_two;
    for (auto &i : A) {
        next_one=i&~one | ~i & one;
        one=next_one;
        cout << one <<  endl;
//        next_one=i&~one&~two | ~i & one;
//        next_two=i&one | ~i & two;
//        one=next_one;
//        two=next_two;
//        cout << one << "," << two << endl;
    }
    return one;
}

pair<int,int> Search::search_covering_segment(const vector<string> &A, const vector<string> &Q) {
    unordered_map<string, int> table;
    unordered_set<string> qtable(Q.begin(), Q.end());

    int l=0, r=0;
    pair<int, int> res(0, A.size());
    while (l<r && r<A.size()) {
        while (r<A.size() && table.size()<qtable.size()) {
            if (qtable.find(A[r]) != qtable.end()) {
                table[A[r]]++;
            }
            r++;
        }

        if (table.size()==qtable.size() && ((r-l-1) < (res.second-res.first) || res.first==-1 && res.second==-1)) {
            res=pair<int, int>(l, r-1);
        }

        while (l<r && table.size()==qtable.size()) {
            if (table.find(A[l]) != table.end()) {
                auto it = table.find(A[l]);
                it->second--;
                if (it->second==0) {
                    table.erase(it);
                    if (res.first==-1 && res.second==-1 || (r-l-1) < (res.second-res.first)) {
                        res=pair<int, int>(l, r-1);
                    }
                }
            }
            l++;
        }
    }
    return res;
}

pair<int, int> Search::search_sequence_covering_segment(const vector<string> &A, const vector<string> &Q) {
    unordered_map<string, int> qtable;
    vector<int> L(Q.size(), -1), D(Q.size(), INT_MAX);

    for (int i=0; i<Q.size(); i++) {
        qtable[Q[i]]=i;
    }

    pair<int, int> res(-1, A.size());
    for (int i=0; i<A.size(); i++) {
        if (qtable.find(A[i]) != qtable.end()) {
            int k=qtable[A[i]];
            L[k]=i;
            if (k==0)
                D[k]=1;
            else if (D[k-1] != INT_MAX) {
                D[k]=D[k-1]+i-L[k-1];
            }
            if (k==Q.size()-1 && res.second-res.first>D.back())
                res={L[0], L[k]};
        }
    }

    return res;
}
