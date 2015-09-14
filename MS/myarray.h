#ifndef MYARRAY_H
#define MYARRAY_H

#include <vector>

using namespace std;

class MyArray
{
public:
    MyArray();

    void static printMaxElementsOfSubArray(vector<int> arr, int k);
    void static printSubarrayWithSumClose0(vector<int> arr);
};

#endif // MYARRAY_H
