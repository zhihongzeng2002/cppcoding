#include "myarray.h"
#include <deque>
#include <iostream>
#include <algorithm>
#include <climits>

MyArray::MyArray()
{
}

void MyArray::printMaxElementsOfSubArray(vector<int> arr, int k)
{
    if (arr.empty() || arr.size()< k) return;

    deque<int> buff;
    int i=0;
    for (; i<k; i++)
    {
        while (!buff.empty() && arr[i]>=arr[buff.back()])
            buff.pop_back();

        buff.push_back(i);
    }

    cout << arr[buff.front()] << " ";

    for (; i<arr.size(); i++)
    {
        if (!buff.empty() && i-k>=buff.front())
            buff.pop_front();

        while ( !buff.empty() && arr[i]>= arr[buff.back()])
            buff.pop_back();

        buff.push_back(i);

        cout << arr[buff.front()] << " ";

    }
    cout << endl;
}

struct Element
{
    int index;
    int sum;
    Element(int _index, int _sum): index(_index), sum(_sum) {}
    Element(){}
    bool operator <(const Element x) const
    {
        return sum<x.sum;
    }
};

static void printVector(vector<Element> &arr)
{
    for (int i=0; i<arr.size(); i++)
    {
        cout << arr[i].index << ":" << arr[i].sum << endl;
    }
    cout << endl;
}

void printSubArrayWithSumClose0_sub(vector<Element> &arr, int &start, int &last)
{
    std::sort(arr.begin(), arr.end());
    printVector(arr);
    int minV=INT_MAX;
    Element prev=arr[0];
    Element startElement, lastElement;
    for (int i=1; i<arr.size(); i++)
    {
        int cur=arr[i].sum;
        int dif=cur-prev.sum;
        if (dif<=minV)
        {
            cout << dif << "-" << minV << ": " ;
            minV=dif;
            startElement=prev;
            lastElement=arr[i];
            cout << startElement.index << "-" << lastElement.index << endl;
        }
        prev=arr[i];
    }
    start=(startElement.index>lastElement.index)?lastElement.index:startElement.index;
    last=(startElement.index<=lastElement.index)?lastElement.index:startElement.index;

}

/**
 * @brief MyArray::printSubarrayWithSumClose0
 *Given an array contains positive and negative values,
 *find the subarray, whose sum is most closed to zero. Require nlogn time complexity
 * @param arr
 */
void MyArray::printSubarrayWithSumClose0(vector<int> arr)
{
    if (arr.empty()) return;

    vector<Element> sumArray;
    sumArray.push_back(Element(-1, 0));

    int prev=0;
    for (int i=0; i<arr.size(); i++)
    {
        int sum=arr[i]+prev;
        sumArray.push_back(Element(i, sum));
        prev=sum;
    }
    int start=0, last=0;
    printSubArrayWithSumClose0_sub(sumArray, start, last);
    cout << "SubArray is from " << start+1 << " to " << last << endl;
    for (int i=start+1; i<=last; i++)
        cout << arr[i] << " ";
    cout << endl;


}
