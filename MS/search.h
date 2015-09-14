#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <exception>
#include <vector>

using namespace std;

struct CellPosition
{
    int x, y;
    CellPosition(): x(-1), y(-1) {}
    CellPosition(int _x, int _y): x(_x), y(_y)
    {

    }
    void print()
    {
        cout << y<< "," <<x << endl;
    }
};

class Search
{
public:
    Search(){}

    int findMagicIndex_nondistinctiveIntegers(vector<int> &arr, int low, int high);
    int findMagicIndex(vector<int> & arr, int low, int high);
    CellPosition findNumIn2DArray(vector<vector<int> > & arr, int x, CellPosition leftTop, CellPosition rightBottom);

    int findNumInRotatedSortedArray(vector<int> & data,int left, int right, int x);
    void mergeTwoSortedData(vector<int> & dataA, vector<int> & dataB);
    static void sortAge(int *seq, int length);
    static bool findSumOfTwoNumbers(int * numArray, size_t length, int targetSum);
    // time: nlogn (best and average), n^2 (worst), memory: logn;
    static void quickSort(int * numArray, int start, int end);
    static int partition(int * numArray, int start, int end);

    // time: nlogn (best, average, worst), memory : depend, n(worst)
    static void mergeSort(int * numArray, int start, int end);
    static void merge(int * numArray, int start, int middle, int end);
    static void print(int * numArray, const int length);

    static void findOnceNum(const int * numArray, const int length);
    static void findOnceNumBetter(const int * numArray, const int length, int &num1, int &num2);

    // heapsort, time: nlogn (best, average, worst), memory: 1

    // bubble sort: time: n(best), n^2 (average and worst), memory: 1

    // binary tree sort: time: n (best), nlogn(average and worst), memory: n

    // radix sort: time O(kn) (k digits)
    // http://en.wikipedia.org/wiki/Radix_sort#Example_in_C.2B.2B

    static int BinarySearch(int * numArray, int x, int start, int end);
};

#endif // SEARCH_H
