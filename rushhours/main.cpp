#include <iostream>
#include "timeline.h"
#include <assert.h>
#include <exception>


using namespace std;

void testCases(TimeLine &A, vector<pair<float, bool> > &T) {
    for (auto &a : T)
        assert(A.IsRuchHour(a.first)==a.second);
}

int main()
{
    TimeLine A;

    try {
        A.AddTimeSpan(-1, 0);
    } catch(exception &e) {
        string str = e.what();
        assert(str.compare("invalid input")==0);
    }

    try {
        A.IsRuchHour(-5);
    } catch(exception &e) {
        string str = e.what();
        assert(str.compare("invalid input")==0);
    }

    cout << "Test invalid input: succeed" << endl;

    vector<pair<float, bool> > T;
    T.emplace_back(0, false);
    T.emplace_back(3, false);
    T.emplace_back(5, false);
    T.emplace_back(7, false);
    T.emplace_back(11, false);
    T.emplace_back(15, false);
    T.emplace_back(20, false);
    T.emplace_back(23, false);
    testCases(A, T);

    cout << "Test initialization: succeed" << endl;

    A.AddTimeSpan(2.00, 4.00);
    T[1].second = true;
    testCases(A, T);

    cout << "Test AddTimeSpan(2, 4): succeed" << endl;

    A.AddTimeSpan(7.00, 9.00);
    T[3].second = true;
    testCases(A, T);

    cout << "Test AddTimeSpan(7, 9): succeed" << endl;

    A.AddTimeSpan(8.00, 12.00);
    T[4].second = true;
    testCases(A, T);

    cout << "Test AddTimeSpan(8, 12): succeed" << endl;

    A.AddTimeSpan(21.00, 15.00);
    T[5].second = true;
    T[6].second = true;
    testCases(A, T);

    cout << "Test AddTimeSpan(21, 11): succeed" << endl;

    A.AddTimeSpan(0.00, 1.00);
    T[0].second = true;
    testCases(A, T);

    cout << "Test AddTimeSpan(0, 1): succeed" << endl;
    return 0;
}

