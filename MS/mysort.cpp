#include "mysort.h"
#include <iostream>
#include <algorithm>

MySort::MySort()
{
}

void MySort::radixSort(vector<int> &seq)
{
    if (seq.empty()) return;

    vector<int> helper(seq);

    // find max
    int maxV=*std::max_element(helper.begin(), helper.end());
    int exp=1;

    while (maxV/exp>0)
    {
        vector<int> digits(10, 0);

        for (int i=0; i<helper.size(); i++)
            digits[(helper[i]/exp) % 10]++;
        for (int i=1; i<helper.size(); i++)
            digits[i] += digits[i-1];

        for (int i=seq.size()-1; i>=0; i--)
        {
            helper[digits[(seq[i]/exp)%10]]=seq[i];
            digits[seq[i]/exp%10]--;
        }

        seq=helper;
        exp *=10;
    }
}

static void merge(vector<int> & seq, int low, int middle, int high)
{
    if (seq.empty() || low >=high)return;
    vector<int> helper(seq);

    int helperLeft=low;
    int helperRight=middle+1;
    int current=low;

    while(helperLeft<=middle && helperRight <=high)
    {
        if (helper[helperLeft] <= helper[helperRight])
        {
            seq[current]=helper[helperLeft];
            helperLeft++;
        }
        else
        {
            seq[current]=helper[helperRight];
            helperRight++;
        }
        current++;
    }
    int remaining=middle-helperLeft;
    for (int i=0; i<=remaining; i++)
    {
        seq[current+i]=helper[helperLeft+i];
    }
}

void MySort::mergeSort(vector<int> &seq, int low, int high)
{
    if (seq.empty() || low >=high) return;
    int middle=(low+high)/2;
    mergeSort(seq, low, middle);
    mergeSort(seq, middle+1, high);
    merge(seq, low, middle, high);
}

static void printSeq(vector<int> &data)
{
    for (int i=0; i<data.size(); i++)
    {
        cout << data[i] << " ";
    }
    cout<< endl<< endl;

}

static int partition(vector<int> &seq, int low, int high)
{
    int pivot=seq[(low+high)/2];
    while (low <=high)
    {
        while (seq[low]< pivot) low++;
        while (seq[high]>pivot) high--;

        if (low<=high)
        {
            int temp=seq[low];
            seq[low]=seq[high];
            seq[high]=temp;
            low++;
            high--;
        }

    }
    return low;
}

void MySort::quickSort(vector<int> &seq, int low, int high)
{
    if (seq.empty() || low > high) return;
    int index = partition(seq, low, high);

    if (low < index-1)
        quickSort(seq, low, index-1);
    if (index<high)
        quickSort(seq, index, high);
}
