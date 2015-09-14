#include "search.h"
#include <string.h>

/**
 * @brief Search::findMagicIndex in the sorted array. Find arr[i]=i;
 * @param arr distinctive integer arr
 * @return magic index if exist, otherwise -1;
 */
int Search::findMagicIndex(vector<int> &arr, int low, int high)
{
    if (arr.empty() || low>high) return -1;

    int middle=(low+high)/2;
    if (arr[middle]==middle)
        return middle;
    else if (arr[middle]<middle)
        return findMagicIndex(arr, middle+1, high);
    else
        return findMagicIndex(arr, low, middle-1);

}

/**
 * @brief Search::findMagicIndex2 with non-distinctive integers. Find arr[i]=i;
 * @param arr non-distinctive integer arr
 * @return magic index if exist, otherwise -1;
 */
int Search::findMagicIndex_nondistinctiveIntegers(vector<int> &arr, int low, int high)
{
    if (arr.empty() || low>high) return -1;

    int middle=(low+high)/2;
    if (arr[middle]==middle)
        return middle;
    else if (arr[middle]<middle)
    {
        int result=findMagicIndex_nondistinctiveIntegers(arr, middle+1, high);
        if (result==-1)
        {
            return findMagicIndex_nondistinctiveIntegers(arr, low, arr[middle]);
        }
    }
    else
    {
        int result= findMagicIndex_nondistinctiveIntegers(arr, low, middle-1);
        if (result==-1)
        {
            return findMagicIndex_nondistinctiveIntegers(arr, arr[middle], high);
        }
    }

}

CellPosition Search::findNumIn2DArray(vector<vector<int> > &arr, int x, CellPosition leftTop, CellPosition rightBottom)
{
//    leftTop.print();
//    rightBottom.print();

    if (arr.size()==0 || arr[0].size()==0 || leftTop.x>rightBottom.x || leftTop.y>rightBottom.y) return CellPosition();

    CellPosition middle;
    middle.x=(leftTop.x+rightBottom.x)/2;
    middle.y=(leftTop.y+rightBottom.y)/2;

//    middle.print();

    if (arr[middle.y][middle.x]==x) return middle;
    else if (arr[middle.y][middle.x]>x)
    {
        return findNumIn2DArray(arr, x, leftTop, middle);
    }
    else
    {
        CellPosition result=findNumIn2DArray(arr, x, CellPosition(middle.x+1, leftTop.y), rightBottom);
        if (result.x==-1)
            result=findNumIn2DArray(arr, x, CellPosition(leftTop.x, middle.y+1), CellPosition(middle.x, rightBottom.y));
        return result;
    }

}

static int searchSortedNum(vector<int> &data, int left, int right, int x)
{
//    cout << left << ";" << right << endl;
    if (left>right) return -1;
//    if (data[left]==x) return left;
//    if (data[right]==x) return right;

    int middle=left+(right-left)/2;
    if (data[middle]==x)
        return middle;
    else if (data[middle]>x)
        return searchSortedNum(data, left, middle-1, x);
    else
        return searchSortedNum(data, middle+1, right, x);

}

int Search::findNumInRotatedSortedArray(vector<int> &data, int left, int right, int x)
{
    if (data.size()==0 || left>right) return -1;
    // find the sorted part

    int middle=left+(right-left)/2;
    if (data[middle]==x) return middle;

    bool leftSorted = data[left] < data[middle];
    bool rightSorted = data[right] > data[middle];


    if (leftSorted)
    {
        if (x>=data[0] && x<=data[middle])
            return searchSortedNum(data, left, middle, x);
        else
            return findNumInRotatedSortedArray(data, middle+1, right, x);
    }
    else if (rightSorted)//
    {
            if (x>=data[middle+1] && x<=data[data.size()-1])
                return searchSortedNum(data, middle+1, data.size()-1, x);
            else
                return findNumInRotatedSortedArray(data, left, middle, x);

    }
    else if (data[left]==data[middle]) // {2 2 2 3 4 2}
    {
        if (data[right] != data[middle])
        {
            return findNumInRotatedSortedArray(data, middle+1, right, x);
        }
        else // we have to seach both side
        {
            int result=findNumInRotatedSortedArray(data, left, middle-1, x); // note middle-1
            if (result==-1)
                result=findNumInRotatedSortedArray(data, middle+1, right, x);

            return result;
        }
    }
}

static void printVector(vector<int> & data)
{
    //print result
    for (int i=0; i<data.size(); i++)
        cout << data[i] << " ";
    cout << endl;
}

void Search::mergeTwoSortedData(vector<int> &dataA, vector<int> &dataB)
{
    vector<int> A(dataA);
    A.insert(A.end(), dataB.begin(), dataB.end());
    printVector(A);

    int lastA=dataA.size()-1;
    int lastB=dataB.size()-1;
    int current=A.size()-1;

    while(lastA>=0 && lastB>=0)
    {
        if (dataA[lastA]>dataB[lastB])
        {
            A[current]=dataA[lastA];
            lastA--;
        }
        else
        {
            A[current]=dataB[lastB];
            lastB--;
        }

        current--;
    }
        while(lastB>=0)
        {
//            cout << current << "," << lastB << endl;
            A[current]=dataB[lastB];
            current--;
            lastB--;
        }

    //print result
    printVector(A);
}

void Search::sortAge(int ages[], int length)
{
    if (!ages || length<=0) return;
    const int oldest=99;
    int ageTable[oldest+1];
    memset(ageTable, 0, sizeof(ageTable));

    for (int i=0; i<length; i++)
    {
        int instance = ages[i];
        if (instance <0 || instance>oldest) throw " out of range"; //   try {....}catch (const char *s){cout << s << endl;}  better is throw myexception, and override char *what()
        ageTable[instance]++;
    }

    int index=0;
    for (int i=0; i<=oldest; i++)
        for (int j=0; j<ageTable[i]; j++)
        {
            ages[index]=i;
            index++;
            cout << i << '-';
        }
    cout << endl;
}

static int find1Bit(const int checker)
{
    int count=0;
    for (int i=checker; i!=0; i=i>>1, count++)
    {
        if (i & 1) break;
    }
    return count;
}

static bool isBitMatch(const int x, const int firstBit)
{
    return (x >> firstBit == 1);
}

/**
 * @brief Search::findOnceNumBetter: all number except two numbers appear twice, find that number
 * @param numArray
 * @param length
 * @param num1
 * @param num2
 */
void Search::findOnceNumBetter(const int * numArray, const int length, int &num1, int &num2)
{
    if (!numArray || length <= 3) return;

    int checker=0;
    for (int i=0; i<length; i++)
    {
        checker ^= numArray[i];
//        cout << numArray[i]<< '-' << checker << ' ';
    }
    int firstBit = find1Bit(checker);
//            cout << checker << ":" << firstBit << endl;

    num1=0; num2=0;
    for (int i=0; i<length; i++)
    {
        int x = numArray[i];
        if ( (x >> firstBit &1) )
            num1 ^= x;
        else
            num2 ^= x;

    }

}

/**
 * @brief Search::findOnceNum: find the numbers in an array which apprear once. Using bit operation or hashing table. I think that I should use hashingtable
 * @param numArray
 * @param length
 */
void Search::findOnceNum(const int * numArray, const int length)
{
    if (!numArray || length<=0) return;

    int flag=0;
    for (int i=0; i<length; i++)
    {
        int x = numArray[i];
        flag ^= 1<<x;
    }
    int count=0;
    for (int i=flag; i!=0; i=i>>1, count++)
    {
        if (i&1) cout << "num=" << count << endl;
    }
//    cout << "count = " << count << endl;

//    cout << "flag=" << flag << endl;
//    int moveBit=0;
//    unsigned int mask=1<<moveBit;
//    while (mask )
//    {
//        int x = flag & (mask);
//        if (x) cout << "num=" << moveBit << endl;

//        moveBit++;
//        mask = 1<< moveBit;
//    }
}

/**
 * @brief Search::findSumOfTwoNumbers: print the number pair whose sum is targetSum
 * @param numArray
 * @param length
 * @param targetSum
 * @return
 */
bool Search::findSumOfTwoNumbers(int *numArray, size_t length, int targetSum)
{
    if (!numArray || length<=1) return false;

    int start=0, end=length-1;
    while (start < end)
    {
        int sum = numArray[start]+numArray[end];
        if (sum < targetSum ) start++;
        else if (sum>targetSum) end--;
        else
        {
            cout << numArray[start] << ':' << numArray[end] << endl;
            return true;
        }
    }
    return false;
}

int Search::BinarySearch(int *numArray, int x, int start, int end)
{
    while (start<end)
    {
        int middle= (start+end)/2;
        if (numArray[middle]>x) return BinarySearch(numArray, x, start, middle-1);
        else if (numArray[middle]<x) return BinarySearch(numArray, x, middle+1, end);
        else
            return numArray[middle];
    }
    throw "there is no targeted number";
    return -1;
}

// Time: average: O(nlogn), worst: (n^2), memory in-place
void Search::quickSort(int *numArray, int start, int end)
{
    int index = partition(numArray, start, end);
    // check
    if (start < index) quickSort(numArray, start, index);
    if (index+1 < end) quickSort(numArray, index+1, end);

}

int Search::partition(int *numArray, int start, int end)
{
    assert(start<=end);

    // pick a pivot
    int pivot = numArray[(start+end)/2];
    while (start < end)
    {
        while (numArray[start]<pivot) start++;
        while (numArray[end]>pivot) end--;

        if (start<end)
        {
            swap(numArray[start], numArray[end]);
            start++;
            end--;
        }
    }
    return start;
}

void Search::print(int * numArray, const int length)
{
//    cout << "array size=" << length << endl;
    for (int i=0; i<length; i++)
        cout << numArray[i] << ' ';

    cout << endl;
}

// time (avarage & worst): nlogn, memory : depend
void Search::mergeSort(int *numArray, int start, int end)
{
    int middle = (start+end)/2;
    if (middle>start)
        mergeSort(numArray, start, middle);
    if (middle<end)
        mergeSort(numArray, middle+1, end);

    merge(numArray, start, middle, end);

}

void Search::merge(int *numArray, int start, int middle, int end)
{
    if (start>end) return;
    int arrayLen = end-start+1;
//    cout << "array size=" << arrayLen << endl;

    // get buffer
    int * helper = new int [arrayLen];
    for (int i=0; i<arrayLen; i++)
        helper[i]=numArray[start+i];

    int helperLeft=0;
    int helperRight=middle-start+1;
    int current=start;

    while (helperLeft<=middle-start && helperRight <= end-start)
    {
        if (helper[helperLeft] <= helper[helperRight])
        {
            numArray[current]=helper[helperLeft];
            helperLeft++;
        }
        else
        {
            numArray[current]=helper[helperRight];
            helperRight++;
        }
        current++;
    }

    // process remaining elements
    int remaining = middle-start-helperLeft;
    for (int i=0; i<=remaining; i++)
        numArray[current+i]=helper[helperLeft+i];

    delete [] helper;
}
