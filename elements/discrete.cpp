#include "discrete.h"
#include <stdlib.h>
#include <climits>
#include <deque>
#include <algorithm>
#include <queue>

Discrete::Discrete()
{
}

string Discrete::find_closest_palindrome(const unsigned a)
{
    string str=to_string(a);

    copy(str.begin(), str.begin()+(str.length()>>1), str.rbegin());
    string mirror=str;
    int idx=str.length()>>1;
    if (stoul(str)>a)
    {
        while (idx>=0)
        {
            if (str[idx]==0)
                str[idx--]='9';
            else
            {
                --str[idx];
                break;
            }
        }
        if (str[0]==0)
        {
            str = to_string(stoul(str));
            fill(str.begin(), str.end(), '9');
        }

    }
    else
    {
        while(idx>=0)
        {
            if (str[idx]==9)
                str[idx--]='0';
            else
            {
                str[idx]++;
                break;
            }
        }

    }

    copy(str.begin(), str.begin()+(str.length()>>1), str.rbegin());
    int x=abs(10);
    return abs(int(stoul(mirror)-a)) > abs(int(stoul(str)-a)) ? mirror : str;

}

static int find_max_floor_helper(vector<vector<int> > &table, int ncase, int ndrop)
{
    if (ndrop==0)
        return 0;
    else if (ncase==1)
        return ndrop;
    else
    {
        if (table[ncase][ndrop]==-1)
        {
            table[ncase][ndrop] = find_max_floor_helper(table, ncase-1, ndrop-1)+1+
                    find_max_floor_helper(table, ncase, ndrop-1);
        }
        return table[ncase][ndrop];
    }

}

int Discrete::find_max_floor(int ncase, int ndrop)
{
    vector<vector<int> > table(ncase+1, vector<int>(ndrop+1, -1));
    return find_max_floor_helper(table, ncase, ndrop);
}

int Discrete::eggDrop(int negg, int nfloor)
{
    if (nfloor==1 || nfloor==0)
        return nfloor;
    else if (negg==1)
        return nfloor;
    else
    {
        int res=INT_MAX;
        for (int i=1; i<=nfloor; i++)
        {
            res = min(res, max(eggDrop(negg-1, i-1), eggDrop(negg, nfloor-i)));
        }
        return res+1;
    }

}

int Discrete::find_last_deletedItem(int len, int k)
{
    vector<int> arr(len);
    int i=0;
    for (auto &x : arr)
        x=i++;

    int start=0;
    while (arr.size()>1)
    {
        arr.erase(arr.begin()+(start+k)%arr.size());
        start+=k;
    }
    return arr[0];
}

int Discrete::josephus(int n, int k)
{
    if (n==1)
        return 1;
    return (josephus(n-1, k)+ (k-1))%n+1;
}

map<int, int> Discrete::pairProfessorStudent(vector<vector<int> > &student_preference,
                                           vector<vector<int> > &professor_preference)
{
    deque<int> free_students;
    for (int i=0; i<student_preference.size(); i++)
        free_students.push_back(i);

    vector<int> student_prof_index(student_preference.size(), 0);
    vector<int> professor_choose(professor_preference.size(), -1);

    while (!free_students.empty())
    {
        int studentID = free_students.front();
        int professorID = student_preference[studentID][student_prof_index[studentID]];

        if (professor_choose[professorID]==-1)
        {
            professor_choose[professorID]=studentID;
            free_students.pop_front();
        }
        else
        {
            int prof_pref_new = distance(professor_preference[professorID].begin(),
                                         find(professor_preference[professorID].begin(), professor_preference[professorID].end(), studentID));
            int prof_pref_old =  distance(professor_preference[professorID].begin(),
                                          find(professor_preference[professorID].begin(), professor_preference[professorID].end(), professor_choose[professorID]));
            if (prof_pref_new< prof_pref_old)
            {
                free_students.push_back(professor_choose[professorID]);
                professor_choose[professorID]=studentID;
                free_students.pop_front();
            }
        }
        student_prof_index[studentID]++;
    }

    map<int, int> prof_student_pair;
    for (int i=0; i<professor_choose.size(); i++)
    {
        prof_student_pair.insert(pair<int, int>(i, professor_choose[i]));
    }

    return prof_student_pair;

}

vector<pair<int, int> > pairStudentProf(const vector<vector<int> > & studentPreference, const vector<vector<int> > & profPreference) {
    queue<int> freeStudents;
    for (int i=0; i<studentPreference.size(); i++) {
        freeStudents.push(i);
    }
    vector<int> student_pref(studentPreference.size(), 0);
    vector<int> profChoice(profPreference.size(), -1);

    while (!freeStudents.empty()) {
        int i = freeStudents.front();
        int profID = studentPreference[i][student_pref[i]];
        if (profChoice[profID]==-1) {
            profChoice[profID]=i;
            freeStudents.pop();
        } else {
            int newOrder = distance(profPreference[profID].begin(), find(profPreference[profID].begin(), profPreference[profID].end(), i));
            int oldOrder = distance(profPreference[profID].begin(), find(profPreference[profID].begin(), profPreference[profID].end(), profChoice[profID]));
            if (newOrder< oldOrder) {
                freeStudents.push(profChoice[profID]);
                profChoice[profID]=i;
                freeStudents.pop();
            }
        }
        student_pref[i]++;
    }

    vector<pair<int, int> > res;
    for (int i=0; i<profChoice.size(); i++)
        res.emplace_back(profChoice[i],i);
    return res;

}

static bool headIndicate(char word)
{
    return (word>>7) & 1;
}

void Discrete::removeLastWord(vector<char> &words)
{
    if (words.empty()) return;

    auto itr=words.rbegin();
    if (headIndicate(*itr))
    {
        if (words.size()<2)
            throw string("Invalid input");

        words.pop_back();
        words.pop_back();
        return;
    }
    else
    {
        itr++;
        int nOne=0;
        while (itr!=words.rend())
        {
            if (headIndicate(*itr))
            {
                nOne++;
                itr++;
            }
            else
            {
                break;
            }

        }

        words.pop_back();
        if (nOne&1)
        {
            words.pop_back();
        }

    }
}

int Discrete::findCelebrityLinearTime(vector<vector<int> > &relationTable)
{
    int i=0, j=1;
    while (i<relationTable.size() && j<relationTable[0].size())
    {
        if (relationTable[i][j]==1)
        {
            i=j++;
        }
        else
            j++;
    }
    return i;
}

int Discrete::find_max_product_without_one(vector<int> &arr)
{
//    vector<int> leftproduct(arr.size(), 1), rightproduct(arr.size(), 1);
//    for (int i=1; i<arr.size(); i++)
//    {
//        leftproduct[i]=leftproduct[i-1]*arr[i-1];
//    }
//    for (int i=arr.size()-2; i>=0; i++)
//    {
//        rightproduct[i]=rightproduct[i]*arr[i+1];
//    }

//    int maxV = leftproduct[0]*rightproduct[0];
//    for (int i=1; i<arr.size(); i++)
//        maxV = max(maxV, leftproduct[i]*rightproduct[i]);

//    return maxV;

    vector<int> leftproduct, rightproduct(arr.size());
    partial_sum(arr.begin(), arr.end(), back_inserter(leftproduct), multiplies<int>());
    partial_sum(arr.begin(), arr.end(), rightproduct.rbegin(), multiplies<int>());

    int maxproduct=INT_MAX;
    for (int i=0; i<arr.size(); i++)
    {
        maxproduct=max(maxproduct, (i==0 ? 1: leftproduct[i-1])* (i==arr.size()-1 ? 1: rightproduct[i+1]));
    }
    return maxproduct;
}

int Discrete::find_max_product_without_one_1space(const vector<int> &arr)
{
    int nZero=0, nPos=0, nNeg=0;
    int idx_zero=-1, idx_s_pos=-1, idx_s_neg=-1, idx_b_neg=-1;

    for (int i=0; i<arr.size(); i++)
    {
        if (arr[i]==0)
        {
            nZero++;
            idx_zero=i;
        }
        else if (arr[i])
        {
            nPos++;
            if (idx_s_pos==-1 || arr[i]<arr[idx_s_pos])
                idx_s_pos = i;
        }
        else
        {
            nNeg++;
            if (idx_s_neg==-1 || arr[i] < arr[idx_s_neg])
                idx_s_neg=i;
            if (idx_b_neg==-1 || arr[i]>arr[idx_b_neg])
                idx_b_neg=i;
        }
    }

    int idx=0;
    if (nZero==2)
        return 0;
    else if (nZero==1)
    {
        if (nNeg&1)
            return 0;
        else
            idx=idx_zero;
    }
    else
    {
        if (nNeg%1)
            idx = idx_b_neg;
        else {
            if (nPos>0)
                idx=idx_s_pos;
            else
                idx=idx_s_neg;
        }

    }
    int res=1;
    for (int i=0; i<arr.size(); i++)
    {
        if(idx!=i)
            res *= arr[i];
    }
    return res;
}

int Discrete::find_start_city(const vector<int> &gas, const vector<int> &dist)
{
//    vector<int> s;
//    for (int i=0; i<gas.size(); i++)
//        s.push_back(gas[i]-dist[i]);
//    vector<int> psum;
//    partial_sum(s.begin(), s.end(), back_inserter<int>(psum));
//    auto it = max_element(psum.begin(), psum.end());
//    return distance(psum.begin(), it)-1;

    int carry=0;//gas[gas.back()-dist.back()];
    pair<int,int> start(0,carry);
    for (int i=1; i<gas.size(); i++)
    {
        carry += gas[i-1]-dist[i-1];
        if (carry<start.second)
            start=pair<int,int>(i, carry);
    }
    return start.first;
}
