#include "heap.h"
#include <unordered_set>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <iterator>

Heap::Heap()
{
}

static int findNthSmallestElement_helper(vector<int> &A, int s, int e, int pivot) {
    int pivot_value = A[pivot];
    int smallIndex=s;
    swap(A[pivot], A[e]);
    for (int i=s; i<e ; i++) {
        if (A[i]<pivot_value)
            swap(A[i], A[smallIndex++]);
    }
    swap(A[e], A[smallIndex]);
    return smallIndex;
}

static int findNthLargestElement_helper(vector<int> &A, int s, int e, int pivot) {
    int pivot_value = A[pivot];
    int largestIndex=s;
    swap(A[pivot], A[e]);
    for (int i=s; i<e; i++)
        if (A[i]>pivot_value)
            swap(A[i], A[largestIndex++]);
    swap(A[e], A[largestIndex]);
    return largestIndex;
}

// note: kth is from 0, 1, 2 which is different from the book which result to wrong result (Prob10.7, P267)
int Heap::findNthElement(vector<int> &A, int k){
    default_random_engine gen;

    int s=0, e=A.size()-1;
    while (s<=e) {   // got this bug s<e
        uniform_int_distribution<int> dis(s, e);
        int t = dis(gen);
        int p = findNthLargestElement_helper(A, s, e, t);
//        int p = findNthSmallestElement_helper(A, s, e, t);
        if (p==k) {
            return A[p];
        }
        else if (p>k)
            e=p-1;
        else
            s=p+1;
    }
}

double Heap::getMedian(vector<int> &A) {
    int n = A.size()>>1;
    double x = findNthElement(A, n);
    cout << "x=" << x << endl;
//    nth_element(A.begin(), A.begin()+n, A.end());
    if (A.size() & 1)
        return x;
    else {
        cout << "x-1=" << findNthElement(A, (A.size()>>1)-1) << endl;
        return 0.5*(x+findNthElement(A, (A.size()>>1)-1));
    }

}

vector<int> Heap::findKClosestMedian(vector<int> &A, int k) {
    double median = getMedian(A);
    cout <<"median=" << median << endl;
//    nth_element(A.begin(), A.begin()+k-1, A.end(), CompMedian(median));
nth_element(A.begin(), A.begin()+k-1, A.end(), [median](const int & x, const int & y){return abs(x-median) < abs(y-median); });
    return vector<int>(A.begin(), A.begin()+k);
}

struct Comp_fstream {
    bool operator()(const tuple<int, shared_ptr<ifstream>, string> &a, const tuple<int, shared_ptr<ifstream>, string> &b) const {
        return get<0>(a) > get<0>(b);
    }
};

static int getFirstToken(const string &s) {
    stringstream ss(s);
    string token;
    getline(ss, token, ',');
    return stoi(token);
}

void Heap::mergeSortedFiles(const vector<string> &fins, const string &fout) {
    priority_queue<tuple<int, shared_ptr<ifstream>, string>, vector<tuple<int, shared_ptr<ifstream>, string> >, Comp_fstream> Q;

    for (auto &s : fins) {
        shared_ptr<ifstream> f(new ifstream(s.c_str()));
        if (!f->is_open())
            throw invalid_argument("input file does not exist");
        string tmp;
        if (!getline(*f, tmp)) {
            f->close();
            continue;
        }
        int timestamp = getFirstToken(tmp);
        Q.emplace(timestamp, f, tmp);
    }

    ofstream out(fout.c_str());
    if (!out.is_open())
        throw invalid_argument("cannot save file");

    while(!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        out << get<2>(it) << endl;
        string line;
        if (!getline(*get<1>(it), line)) {
            get<1>(it)->close();
            continue;
        } else {
            int timestamp = getFirstToken(line);
            Q.emplace(timestamp, get<1>(it), line);
        }
    }

    out.close();
}

int Heap::find_local_minimum(const vector<int> &A, int s, int e) {
    if (e<=s) return -1;
    int half=s+((e-s)>>1);
    if (A[half-1]>=A[half] && A[half]<=A[half+1])
        return half;

    if (A[half-1]>=A[half])
        return find_local_minimum(A, s, half);
    else
        return find_local_minimum(A, half-1, e);

}

static void compare_kth_largest_heap_helper(const vector<int> & max_heap, int k, int x, int idx, int &larger, int &equal) {
    if (larger>=k || idx>=max_heap.size() || max_heap[idx] < x)
        return;
    else if (max_heap[idx]==x) {
        if (++equal>=k)
            return;
    } else {
        ++larger;
    }

    compare_kth_largest_heap_helper(max_heap, k, x, (idx<<1)+1, larger, equal);
    compare_kth_largest_heap_helper(max_heap, k, x, (idx<<1)+2, larger, equal);
}

int Heap::compare_kth_largest_heap(const vector<int> &max_heap, int k, int x) {
    int larger=0, equal=0;
    compare_kth_largest_heap_helper(max_heap, k, x, 0, larger, equal);
    return larger>k ? 1 : (larger+equal>=k ? 0 : -1);
}

vector<Heap::Num> Heap::generate_first_k(int k) {
    priority_queue<Num> min_heap;
    unordered_set<Num, HashNum> hash;
    vector<Num> smallest;
    min_heap.emplace(0,0);
    hash.emplace(0,0);

    while (smallest.size()<k) {
        Num t = min_heap.top();
        min_heap.pop();
        hash.erase(t);
        smallest.emplace_back(t);

        Num c1(t.a+1, t.b), c2(t.a, t.b+1);
        if (hash.emplace(c1).second)
            min_heap.emplace(c1);
        if (hash.emplace(c2).second)
            min_heap.emplace(c2);
    }

    return smallest;
}

void Heap::online_median(istringstream &sin) {
    priority_queue<int, vector<int>, less<int> > L;//max heap
    priority_queue<int, vector<int>, greater<int> > H; // min heap

    int x;
    while (sin >> x) {
        if (!L.empty() &&  x>L.top())
            H.emplace(x);
        else
            L.emplace(x);

        if (L.size()> H.size()+1) {
            H.emplace(L.top());
            L.pop();
        } else if (L.size()+1 < H.size()) {
            L.emplace(H.top());
            H.pop();
        }

        if (L.size()==H.size())
            cout << 0.5* (L.top()+H.top()) << endl;
        else
            cout <<( H.size()>L.size() ? H.top() : L.top()) << endl;
    }
}

vector<int> Heap::merge_arrays(const vector<vector<int> > &s) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, Compare > min_heap;
    vector<int> idx(s.size(), 0);

    for (int i=0; i<s.size(); i++) {
        if (!s[i].empty()) {
            min_heap.emplace(s[i][0], i);
            idx[i]=1;
        }
    }

    vector<int> ret;
    while (!min_heap.empty()) {
        pair<int, int> top = min_heap.top();
        min_heap.pop();
        ret.push_back(top.first);
        if (idx[top.second]<s[top.second].size()) {
            min_heap.emplace(s[top.second][idx[top.second]++], top.second);
        }
    }
    return ret;
}

vector<int> Heap::sort_k_increase_decrease_array(const vector<int> &s) {
    if (s.size() <=1 ) return s;
    vector<vector<int> > ret(1, vector<int>(1, s[0]));
    int i=1;
    int start=0;
    bool isIncrease=true;
    while (i < s.size()) {
        if ((s[i-1] > s[i] && isIncrease) || (s[i-1] < s[i] && !isIncrease)) {
            if (isIncrease) {
                ret.emplace_back(s.cbegin()+start, s.cbegin()+i);
            } else {
                ret.emplace_back(s.crbegin()+s.size()-i, s.crbegin()+s.size()-start);
            }
            start=i;
            isIncrease != isIncrease;
            i++;
        }
    }
    if (start<s.size()) {
        if (isIncrease) {
            ret.emplace_back(s.cbegin()+start, s.cend());
        } else {
            ret.emplace_back(s.crbegin(), s.crbegin()+s.size()-start);
        }
    }

    return merge_arrays(ret);
}

//this is min_heap instead of max_heap
void Heap::find_kth_largest_stream(istringstream &sin, int k) {
    priority_queue<int, vector<int>, greater<int> > min_heap;
//    priority_queue<int, vector<int>, less<int> > max_heap;

    int buf;
    while (sin >> buf) {
        if (min_heap.size() < k) {
            min_heap.emplace(buf);
        } else {
            if (buf>min_heap.top()) {
                min_heap.pop();
                min_heap.emplace(buf);
            }
            cout << min_heap.top();
        }
    }
}

static double find_median(vector<int> &s) {
    int half = s.size()>>1;
    nth_element(s.begin(), s.begin()+half, s.end());
    int x=s[half];
    if (s.size() & 1)
        return x;
    else {
        nth_element(s.begin(), s.begin()+half-1, s.end());
        return 0.5*(x+s[half-1]);
    }
}

struct Compare_median {
    Compare_median(const double _m) : m(_m) {}
    bool operator()(const int x, const int y) const {
        return fabs(m-x)<fabs(m-y);
    }
    double m;
};

vector<int> Heap::find_k_closest_median(vector<int> &s, int k) {
    nth_element(s.begin(), s.begin()+k-1, s.end(), Compare_median{find_median(s)});
return vector<int>(s.begin(), s.begin()+k);
}

// using maxheap to keep smallest ones
vector<Star> find_closest_stars(istringstream &sin, int k) {
    priority_queue<Star> max_heap;
    string line;
    while (getline(sin, line)) {
        stringstream linestream(line);
        string buf;
        getline(linestream, buf, ',');
        int id = stoi(buf);
        vector<double> data;
        while (getline(linestream, buf, ',')) {
            data.push_back(stoi(buf));
        }
        Star star(id, data);
        if (max_heap.size()==k) {
            if (star < max_heap.top()) {
                max_heap.pop();
                max_heap.emplace(star);
            }
        } else {
            max_heap.emplace(star);
        }

    }
    vector<Star> ret;
    while (!max_heap.empty()) {
        ret.emplace_back(max_heap.top());
        max_heap.pop();
    }
    return ret;
}
