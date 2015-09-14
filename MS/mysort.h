#ifndef MYSORT_H
#define MYSORT_H

#include <vector>

using namespace std;

class MySort
{
public:
    MySort();

    static void quickSort(vector<int> &seq, int low, int high);
    static void mergeSort(vector<int> &seq, int low, int high);
    static void radixSort(vector<int> &seq);
};

#endif // MYSORT_H
