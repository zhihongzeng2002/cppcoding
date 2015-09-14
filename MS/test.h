#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include "tree.h"
#include <memory>

using namespace std;

class Test
{
public:
    Test();

};

class Amazon
{
public:
    Amazon(){}
    static int numBagHoldBarCodes(vector<vector<int> > & barcodes);
    static int numBagHoldBarCodes_better(vector<vector<int> > & barcodes);
    static string compressString(string str);
    static void printMatrixFromOutToInside(vector<vector<int> > &arr);

    static void printNumbersWithDigitDiff1(int maxNum);

    static void printLongestSnake(vector<vector<int> > &arr);

    static void printAnagrams(vector<string> & strvector);

    static string findWordMadeOfMaxWords(vector<string> & dict);

    static void printPrimePairsLessThanNum(int n);

    static void printKthLargestNumInBST(shared_ptr<TreeNode> & root, int k, int &count);

    static int findMinIterationToDistributeApple(vector<int> & apples);

    static int caclNumToSwapBits(string & arr);

    static void sortStringWithMap(string arr, string order);
    static void printSourceCode();

    static int findBiggestX(vector<vector<int> > & arr);
};

class Microsoft
{
public:
    static void sortMultipleArray(vector<vector<int> > &arr);
    static void sortBigData(vector<int> & data, const bool unique=false);
    static double sqrtImplementation(double x, int iterNum);

    //
};

class Facebook
{
public:
    static void hashMapImplementation(){}
};

#endif // TEST_H
