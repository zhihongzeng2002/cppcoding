#ifndef MODERATE_H
#define MODERATE_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Moderate
{
public:
    Moderate();

    int countFactorialZeroTrailing(int n){}

    int calcMax(int a, int b);

    void masterMind(string guess, string solution);

    void findSubarrayToSorted(vector<int> &A);

    void printInterger(int x);
    string printInterger_better(int x);

    int findMaxSubarray(const vector<int> &A);

    int rand5(){}
    int Rand7_rand5(){
        while(true) {
            int x = 5*rand5()+rand5();
            if (x<21)
                return x%7;
        }
    }

    //from the book "cracking...", it has a bug
    void parseSentence(string sentence, unordered_set<string> &dict);
    // it is working programe
    void parseSentence2(string sentence, unordered_set<string> &dict);
};

#endif // MODERATE_H
