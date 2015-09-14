#ifndef META_HPP
#define META_HPP

#include "meta.h"
#include <vector>

template<typename T>
int merge(vector<T> &arr, int s, int m, int e)
{
    int leftIndex=s, rightIndex=m;
    int countInversion=0;
    vector<T> sortedArr;

    while (leftIndex < m && rightIndex <= e)
    {
        if (arr[leftIndex] <= arr[rightIndex] )
        {
            sortedArr.push_back(arr[leftIndex++]);
        }
        else
        {
            sortedArr.push_back((arr[rightIndex++]));
            countInversion += m-leftIndex;
        }
    }
    copy(arr.begin()+leftIndex, arr.begin()+m, back_inserter(sortedArr));
    copy(arr.begin()+rightIndex, arr.begin()+e+1, back_inserter(sortedArr));

    copy(sortedArr.begin(), sortedArr.end(), arr.begin()+s);

    return countInversion;
}

template<typename T>
int count_inverted_pairs_helper(vector<T> & arr, int s, int e)
{
    if (arr.empty() || s>=e)
        return 0;

    int mid = s+((e-s)>>1);
    return count_inverted_pairs_helper(arr, s, mid-1)
            + count_inverted_pairs_helper(arr, mid, e)
            + merge(arr, s, mid, e);
}

/**
 * using merge sort to count the inverted pairs
 */
template<typename T>
int Meta::count_inverted_pairs(vector<T> & arr)
{
    return count_inverted_pairs_helper(arr, 0, arr.size()-1);

}


#endif // META_HPP
