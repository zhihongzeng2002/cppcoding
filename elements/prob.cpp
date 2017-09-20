#include "prob.h"
#include <random>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <fstream>

static vector<int> randomSequence(vector<int> &A, int k) {
    random_device m;
    default_random_engine gen(m());
    for (int i=0; i<k; i++) {
        uniform_int_distribution<int> t(i, A.size()-1);
        int x=t(gen);
        swap(A[i], A[x]);
    }
    A.resize(k);
}

static int generateRandomAB(int a, int b) {
    int l=b-a+1;
    int res=0;
    default_random_engine eng;
    uniform_int_distribution<int> t(0,1);
    do {
        res=0;
        for (int i=0;(1<<i)<l; i++) {
            res = res<<1 | t(eng);
        }
    } while (res>=l);
    return a+res;
}

static vector<int> getRandomPermutation_k_space(int n, int k) {
    unordered_map<int, int> table;
    default_random_engine eng;

    for (int i=0; i<k; i++) {
        uniform_int_distribution<int> t(0, n-1-i);
        int r=t(eng);
        auto it1=table.find(r);
        auto it2=table.find(n-1-i);
        if (it1==table.end() && it2==table.end()) {
            table[r]=n-1-i;
            table[n-1-i]=r;
        } else if (it1 !=table.end() && it2==table.end()) {
            table[n-1-i]=it1->second;
            it1->second=n-1-i;
        } else if (it1 == table.end() && it2 != table.end()) {
            table[r] = it2->second;
            it2->second = r;
        } else {
            int temp=it1->second;
            it1->second = it2->second;
            it2->second = temp;
        }
    }

    vector<int> res;
    for (int i=0; i<k; i++)
        res.push_back(table[n-1-i]);
    return res;
}

static double MajorVotes_recursive_helper(const vector<double> &p, int r, int n, vector<vector<double> > &table) {
    if (r>n || r<0 || n<0)
        return 0;
    if (r==0 && n==0)
        return 1;

    if (table[r][n]==-1) {
        table[r][n]=MajorVotes_recursive_helper(p, r-1, n-1, table)*p[n-1]
                +MajorVotes_recursive_helper(p, r, n-1, table)*(1.-p[n-1]);
    }
    return table[r][n];
}

static double MajorVotes_recursive(const vector<double> &p) {
    int n=p.size();
    vector<vector<double> > table(n+1, vector<double>(n+1, -1));

    double res;
    for (int i=ceil((n+1)/2); i<=n; i++)
        res += MajorVotes_recursive_helper(p, i, n, table);
    return res;
}

static double MajorVotes(const vector<double> &p) {
    vector<double> votes(p.size()+1, 0);
    votes[0]=1;
    for (auto &x : p) {
        for (int i=votes.size()-1; i>=1; i--) {
            votes[i]=votes[i-1]*x + votes[i]*(1-x);
        }
    }
    double res=0;
    for (int i=votes.size()>>1+(votes.size()&1 ? 1 :0); i<votes.size(); i++)
        res+=votes[i];
    return res;
}

int generateDataFromHistogram(vector<pair<int, double> > &hist) {
    vector<double> p;
    for (auto &x: hist)
        p.push_back(x.second);
    vector<double> pvect;
    pvect.push_back(0);
    partial_sum(p.begin(),p.end(), back_inserter(pvect));

    default_random_engine eng;
    uniform_real_distribution<double> t(0,1);
    double sample=t(eng);

    auto it=upper_bound(pvect.begin(), pvect.end(), sample);
    int i = distance(pvect.begin(), it);
    return hist[i-1].first;

}

vector<int> getSubSet(fstream &sin, int k) {
    vector<int> res;
    int x;
    for (int i=0; i<k && sin>>x; i++)
        res.push_back(x);

    int num=k;
    default_random_engine eng;
    while (sin>>x) {
        uniform_int_distribution<int> d(0, num++);
        int tar = d(eng);
        if (tar<k)
            res[tar]=x;
    }
    return res;
}

Prob::Prob()
{
}

double static house_majority_helper(const vector<double> & probs, int r, int n, vector<vector<double> > &table)
{
    if (r<0)
        return 0;
    if (!r && !n)
        return 1;
    if (r>n)
        return 0;

    if (table[r][n] == -1)
        table[r][n] = house_majority_helper(probs, r, n-1, table) * (1-probs[n-1]) + house_majority_helper(probs, r-1, n-1, table) * probs[n-1];

    return table[r][n];
}

double Prob::house_majority(const vector<double> &repubProbs)
{
    int n = repubProbs.size();
    vector<vector<double> > table(n+1, vector<double>(n+1, -1));

    double totalProb=0;
    for (int i=n/2+1; i<=n; i++)
        totalProb += house_majority_helper(repubProbs, i, n, table);

    return totalProb;
}

vector<int> Prob::off_sampling(vector<int> A, int k)
{

    random_device m;
    default_random_engine eng(m());

    int n=k;
//    if (k>A.size()/2)
//        n=A.size()-k;

    for(int i=0; i<n; i++)
    {
        uniform_int_distribution<int> dist(i, A.size()-1);
        int x = dist(eng);
        swap(A[i], A[x]);
    }

//    if (k>A.size()/2)
//    {
//        return vector<int>(A.begin()+n, A.end());
//    }

    A.resize(k);

    return A;
}

int Prob::generateRandomInt_in_a_b(int a, int b)
{
    int k = b-a+1;

    default_random_engine eng;
    uniform_int_distribution<int> dist(0,1);

    int res;
    do {
        res=0;
        for (int i=0; (1<<i) < k; i++)
        {
            res = (res<<1) | dist(eng);
        }
    } while (res>=k);

    return a+res;
}

double Prob::nonuniform_random_generation(vector<double> &arr, vector<double> &prob)
{
    vector<double> accProb;
    accProb.push_back(0);
    partial_sum(prob.begin(), prob.end(), back_inserter(accProb));

    default_random_engine eng;
    uniform_real_distribution<double> dist(0, 1);

    vector<double>::iterator itr=upper_bound(accProb.begin(), accProb.end(), dist(eng));
    return arr[distance(accProb.begin(), itr)-1];
}

vector<int> Prob::reservoir_sampling(istringstream &s, int k)
{
    vector<int> pool;
    int x;
    for (int i=0; i<k && s>>x; i++)
    {
        pool.emplace_back(x);
    }

    default_random_engine eng;
    int numSample = k+1;

    while(s>>x)
    {
        uniform_int_distribution<int> dist(0, numSample++);
        int i = dist(eng);

        if (i<k)
            pool[i]=x;
    }

    return pool;
}

vector<int> Prob::online_sampling(int n, int k)
{
    unordered_map<int, int> table;
    default_random_engine eng;

    for (int i=0; i<k; i++)
    {
        uniform_int_distribution<int> dist(i, n-1);
        int x = dist(eng);

        auto it0 = table.find(i);
        auto it1 = table.find(x);
        if (it0==table.end() && it1 == table.end())
        {
            table[i]=x;
            table[x]=i;
        }
        else if(it0==table.end() && it1 != table.end())
        {
            table[i]=it1->second;
            table[x]=i;
        }
        else if(it0!=table.end() && it1 == table.end())
        {
            table[x]=it0->second;
            table[i]=x;
        }
        else if(it0!=table.end() && it1 != table.end())
        {
            int temp = it0->second;
            table[i]=it1->second;
            table[x]=temp;
        }
    }

    vector<int> result;
    for (int i=0; i<k; i++)
        result.push_back(table[i]);

    return result;
}

static int rand5() {
    return 1;
}

int Prob::rand7Fromrand5(){
    int x=0;
    do {
        x=5*rand5()+rand5();
    } while (x>20);
    return x%7;
}
