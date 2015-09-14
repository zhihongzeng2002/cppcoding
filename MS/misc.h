#ifndef MISC_H
#define MISC_H

#include <set>
#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class MyFunctor
{
    int state;
public:
    MyFunctor(){};
    ~MyFunctor(){};
    MyFunctor(int _state): state(_state){}
    bool operator()(int x) {return (x & 1) == 1;}
};

enum TicTacState
{
    WHITE, BLACK, BLANK
};

struct TicCell
{
    TicTacState value;
    TicCell(): value(BLANK)
    {}
};

struct GuessResult
{
    int hit;
    int pseduoHit;
    GuessResult(): hit(0), pseduoHit(0)
    {}
    GuessResult(int _hit, int _pseduo): hit(_hit), pseduoHit(_pseduo)
    {}
    void print()
    {
        cout << "hit=" << hit << ": pseduoHit=" << pseduoHit << endl;
    }

};

struct Person
{
    int height, weight;
    Person():height(-1), weight(-1) {}
    Person(int x, int y): height(x), weight(y) {}
    bool canBeAbove(Person & p)
    {
        if (p.height!=-1) return true;
        return p.height<height && p.weight<weight;

        return true;
    }
    bool operator <(const Person &p) const
    {
        return height < p.height;
    }
};

class Misc
{
public:
    Misc(){}

    static vector<float> computeProbabilitiesOfDiceSum(int numDice);
    void testBuildTower(int argc, char **argv);
    vector<Person> convertStreamToPersonTeam(int argc, char **argv);
    vector<Person> buildTallestTower2(vector<Person> &team);
    vector<Person> buildTallestTower(vector<Person> & team);

    static double powerInt(int a, int b);
    static void radixsort(int *a, int n);
    static int divide(int a, int b);

    static string mapNumToExcelHeader(int num, map<int, string> &table);
    static map<int, string> buildMapFromNumToExcelHeader();

    static int unconcatenating(string &str, set<string> &dict, string &result);
    static void printAllPairsWithTargetSum2(vector<int> &data, int sum);
    static void printAllPairsWithTargetSum(vector<int> & data, int sum);
    static void printNumbers(int num);
    static int findMinDistanceToSort(vector<int> & data);
    static GuessResult guessHitGame(string & computer, string & guess);

    static int getMaxWithoutIf(int a, int b);
    static TicTacState hasWonTicTacToe2(vector<vector<TicCell> > & board);
    static bool hasWonTicTacToe(vector<vector<TicCell> > &board);
    static void swapTwoNumbers(int &a, int &b);
    static void findPathBetweenTwoWord(string &startword, string &endword, set<string> &dict );
    static void getMedianInStream(vector<int> & arr);
    static string findLongestWordMadeofOtherWords(vector<string> & dictory);
    static vector<int> findSmallestNums_heap(int nums[], int length, const int numSmallest);
    static void findSmallestNums_main(int nums[], int length, const int numSmallest);
    static void findSmallestNums(int nums[], int low, int high, const int numSmallest);
    static int minDistanceBetween(const vector<string> & book, const string & str1, const string & str2);
    static int countDigitsInRange(const int num, const int digit);
    static int getMaxDiff(int *seq, int length);
    static int GetUglyNum(int index);
    static bool findGreatestSumOfSubArray(int *pData, size_t nlength, int &greatestSum);
    static void findKLeastNumbers(const std::vector<int> & data, std::multiset<int> & leastNums, size_t k);
    static int fibonacci(const int n);
    static int jumpStair_main(int n);
    static int numOfOnes(int n);
    static void sequenceSum(const int n);
    static void reorderOddEven(int * seq, int length, MyFunctor &t);
    static void reorder(int *seq, int length){
        MyFunctor t;
        reorderOddEven(seq, length, t);
    }
    static void reorderOddEven(int * seq, int length, bool (*func)(int))
    {
        bool x = func(1);
    }
    int countBits(int num)
    {
        int count =0;
        for (; num; count++)
            num &= num-1;
    }

    static unsigned int concatenateInts(unsigned int x, unsigned int y);

};

class FinalClass1
{
    static FinalClass1 * getInstance()
    {
        return new FinalClass1;
    }
    static void DeleteInstance(FinalClass1 *instance)
    {
        delete instance;
        instance = NULL;
    }
private:
    FinalClass1(){};
    ~FinalClass1(){};
};

template <typename T>
class FinalClass
{
    FinalClass(){};
    ~FinalClass(){};
//public:
    friend T;
};

class FinalClass2 : virtual public FinalClass<FinalClass2>
{
public:
    FinalClass2(){};
    ~FinalClass2(){};

};


#endif // MISC_H
