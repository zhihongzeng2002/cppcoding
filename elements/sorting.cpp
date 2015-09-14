#include "sorting.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <map>
#include <iterator>

Sorting::Sorting()
{
}

void Sorting::flipSort(vector<int> &A) {
    int idx = 0;
    while (idx<A.size()) {
        auto it = max_element(A.begin(), A.end()-idx);
        reverse(A.begin(), it+1);

        reverse(A.begin(), A.end()-idx);
        idx++;
    }
}

static void radixSort_helper(vector<int> &A, int exp, int base) {
    vector<int> count(base, 0);
    for (auto &a : A) {
        count[(a/exp)%base]++;
    }

    int idx=0;
    for (int i=0; i<count.size(); i++) {
        int tmp = count[i];
        count[i] = idx;
        idx += tmp;
    }
    vector<int> output(A.size());
    for (auto &a : A) {
        output[count[(a/exp)%base]]=a;
        count[(a/exp)%base]++;
    }
    A = output;
}

void Sorting::radixSort(vector<int> &A) {
    int maxV = *max_element(A.begin(), A.end());
    cout << maxV << endl;
    int base =10;
    for (int exp=1; maxV/exp>0; exp *= base)
        radixSort_helper(A, exp, base);
}

vector<int> Sorting::findMinVisit(vector<Task> &tasks) {
    sort(tasks.begin(), tasks.end());

    vector<int> ret;
//    int tstart=-1;
    int tend=-1;
    for (auto & t: tasks) {
        cout << t.startT << " " << t.endT << endl;
        if (t.startT>=tend) {   // start a new one
            if (tend!=-1)    // record the old one
                ret.push_back(tend);

//            tstart=t.startT;
            tend=t.endT;
        }
        if (t.endT<tend) {
            tend=t.endT;
        }
//        cout << tstart << "-> " << tend << endl;
    }
    if (tend!=-1) ret.push_back(tend);
    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, ","));
    cout << endl;
    return ret;
}

vector<Sorting::Task> Sorting::calcUnionTasks_better(vector<Task> &tasks) {
    vector<Task> ret;
    if (tasks.empty()) return ret;
    sort(tasks.begin(), tasks.end());

    Task curr(tasks[0]);
    for (int i=1; i<tasks.size(); i++) {
        if (tasks[i].startT > curr.endT) {
            ret.emplace_back(curr);
            curr = tasks[i];
            continue;
        }
        if (tasks[i].endT > curr.endT)
            curr.endT=tasks[i].endT;
    }
    ret.emplace_back(curr);
    return ret;
}

vector<Sorting::Task> Sorting::calcUnionTasks(const vector<Task> &tasks) {
    vector<int> tbegin, tend;
    for (auto & t: tasks) {
        tbegin.push_back(t.startT);
        tend.push_back(t.endT);
    }
    sort(tbegin.begin(), tbegin.end());
    sort(tend.begin(), tend.end());
    int i=0, j=0;
    int curTask=0, curStart=0;
    vector<Task> unionSet;
    while (i<tbegin.size() && j<tend.size()) {
        if (tbegin[i] < tend[j]) {
            if (curTask==0) {
                curStart=tbegin[i];
            }
            curTask++;
            i++;
        }
        else if (tbegin[i]==tend[j]) {
            i++;
            j++;
        } else {
            curTask--;

            if (curTask==0) {
                Task t(curStart, tend[j]);
                unionSet.push_back(t);
            }
            j++;
        }

    }
    if (j<tend.size()) {
        Task t(curStart, tend.back());
        unionSet.push_back(t);
    }

    return unionSet;
}

void Sorting::testMaxNumTasks() {
    vector<Task> tasks;
    tasks.emplace_back(0, 2);
    tasks.emplace_back(1, 2);
    tasks.emplace_back(2, 4);
    tasks.emplace_back(4, 7);
    tasks.emplace_back(5, 6);
    tasks.emplace_back(8, 10);

    vector<int> unionSet = findMinVisit(tasks);
//    for (auto & x: unionSet)
//        cout << x << endl;
//    cout << calcMaxNumTasks(tasks) << endl;
}

int Sorting::calcMaxNumTasks(const vector<Task> &tasks) {
    vector<int> tbegin, tend;
    for (auto & t: tasks) {
        tbegin.push_back(t.startT);
        tend.push_back(t.endT);
    }
    sort(tbegin.begin(), tbegin.end());
    sort(tend.begin(), tend.end());
    int i=0, j=0;
    int maxTask=0, curTask=0;
    while (i<tasks.size() && j<tasks.size()) {
        if (tbegin[i] < tend[j]) {
            curTask++;
            i++;
        }
        else if (tbegin[i]==tend[j]) {
            i++;
            j++;
        } else {
            curTask--;
            j++;
        }
        if (curTask>maxTask)
            maxTask=curTask;
    }
//    while (j<tasks.size())

    return maxTask;
}

void Sorting::stableSortPersons(vector<Person> & people) {
    // support the index range (0-255)
    vector<vector<string> > ret(256, vector<string>());
    for (auto &x : people)
        ret[x.key].push_back(x.name);

    for (int i=0; i<256; i++) {
        if (ret[i].size()>0) {
            for (auto &t: ret[i])
                cout << t << endl;
        }
    }

}

void Sorting::calcCharFrequency_nomap(string s) {
//    vector<int> table(256, 0);
//    for (auto &x : s)
//        table[x]++;
//    for (int i=0; i<256; i++) {
//        if (table[i])
//            cout << char(i) << table[i] << endl;
//    }

    if (s.empty()) return;

    sort(s.begin(), s.end());
    int count=1;
    for (int i=1; i<s.length(); i++) {
            if (s[i]==s[i-1])
                count++;
            else {
                cout << s[i-1] << count << endl;
                count=1;
            }
    }
    cout << s[s.length()-1]<< count << endl;

}

vector<int> Sorting::findIntersectionSortedArrays(vector<int> &A, vector<int> &B) {
    int iA=0, iB=0;
    vector<int> ret;
    while (iA<A.size() && iB<B.size()) {
        if (A[iA]==B[iB] && (iA==0 || A[iA-1] !=A[iA])) {
            ret.push_back(A[iA]);
            iA++;
            iB++;
        }
        else if ((A[iA]>B[iB])) {
            iB++;
        } else
            iA++;
    }
    return ret;
}

void Sorting::indirect_sort(const string &src, const string &des) {
    ifstream sin(src.c_str());

    string x;
    vector<string> arr;
    while (sin>>x)
        arr.emplace_back(x);

    vector<string *> P;
    for (auto &t : arr)
        P.push_back(&t);

    sort(P.begin(), P.end(), [](const string *a, const string *b)->bool{return (*a).length()<(*b).length();});

    ofstream sout(des.c_str());
    for (auto &t : P)
      sout << *t << " ";
    sout << endl;
}

void Sorting::sortStringWithLargeLengthVariation(string &filename)
{
    ifstream infile(filename.c_str());

    int buff;
    vector<int> arr;
    while (infile>>buff)
    {
        arr.emplace_back(buff);
    }

    vector<int *> ref;
    for (auto &s : arr)
        ref.emplace_back(&s);

    sort(ref.begin(), ref.end(), [](int *a, int *b){ return *a <*b;});

    ofstream outfile(filename.c_str());
    for (auto &x : ref)
      outfile << *x << endl;

}

void Sorting::count_sort_person_with_key(vector<Person> &people)
{
    unordered_map<int, int> keyCount;
    for (auto &p : people)
        keyCount[p.key]++;

    unordered_map<int, int> keyOffset;
    int offset=0;
    for (auto &v : keyCount)
    {
        keyOffset[v.first] = offset;
        offset += v.second;
    }

    while (!keyOffset.empty())
    {
        auto from = keyOffset.begin();
        auto to = keyOffset.find(people[from->second].key);
        swap(people[from->second], people[to->second]);

        if ( --keyCount[to->first])
        {
            to->second++;
        }
        else
            keyOffset.erase(to->first);
    }

}

void Sorting::count_sort_person_with_key2(vector<Person> & people) {
    map<int, int> keyCount;
    for (auto &t: people)
        keyCount[t.key]++;

    map<int, int> keyOffset;
    int offset=0;
    for (auto &t : keyCount) {
        keyOffset[t.first]=offset;
        offset+=t.second;
    }

    while (!keyOffset.empty()) {
        auto from = keyOffset.begin();
        auto to = keyOffset.find(people[from->second].key);
        swap(people[from->second], people[to->second]);
        if (--keyCount[to->first])
            to->second++;
        else
            keyOffset.erase(to);
    }

}

void Sorting::testCountPerson() {
    vector<Person> people;

    string name("a");
    for (int i=0; i<10; i++) {
        people.emplace_back(Person(i, name));
    }
    people.emplace_back(Person(5,name));
    people.emplace_back(Person(5,name));

    count_sort_person_with_key2(people);

    for (auto &x : people)
        cout << x.key << endl;
}
