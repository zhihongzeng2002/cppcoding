#include "test.h"
#include <iostream>
#include <sstream>
#include "recursion.h"
#include <map>
#include <algorithm>
#include <queue>
#include <limits.h>
#include <math.h>
//#include <ctype.h>

Test::Test()
{
}

static int diffBits(vector<int> &code0, vector<int> & code1)
{
    int count=0;
    for (int i=0; i< code0.size(); i++)
    {
        if (code0[i]!=code1[i])
         count++;
    }
    cout << "diffBits =" << count << endl;
    return count;
}

static bool belongContainer(vector<int> & code, vector<vector<int> > & bucket)
{
    for (int i=0; i<bucket.size(); i++)
    {
        if (diffBits(code, bucket[i])<=2)
            return true;
    }
    return false;
}

static void insertContainers(vector<int> &code, vector<vector<vector<int> > >& containers)
{
    if (containers.empty())
    {
        vector<vector<int> > bucket(1, code);
        containers.push_back(bucket);
        return;
    }

    int i=0;
    for (i=0; i<containers.size(); i++)
    {
        if (belongContainer(code, containers[i]))
        {
            containers[i].push_back(code);
            break;
        }
    }
    if (i==containers.size())
    {
        vector<vector<int> > bucket(1, code);
        containers.push_back(bucket);
        return;
    }

}

static int dist(vector<int> x, vector<int> y)
{
    int sum=0;
    for (int i=0; i<x.size(); i++)
    {
        if (x[i] != y[i])
            sum++;
    }
    return sum;

}

static bool needMerge(vector<vector<int> > & c0, vector<vector<int> > &c1)
{
    for (int i=0; i<c0.size(); i++)
    {
        for (int j=0; j<c1.size(); j++)
        {
            if (dist(c0[i], c1[j])<=2)
                return true;
        }
    }
    return false;
}

static vector<vector<int> > merge(vector<vector<int> > & c0, vector<vector<int> > &c1)
{
    return vector<vector<int> >();
}

static void mergeContainers(vector<vector<vector<int> > > &containers)
{
    // pair containers
        int i=0, j;
        while (true)
        {
            int len=containers.size();
            cout << "container size=" << len << endl;
            for (i=0; i<containers.size(); i++)
            {
                for ( j=i+1; j<containers.size(); j++)
                {
                    bool flag=needMerge(containers[i], containers[j]);
                    if (flag)
                    {
                        containers[i].insert(containers[i].end(), containers[j].begin(), containers[j].end());
                        containers.erase(containers.begin()+j);
                        break;
                    }
                }
                if (len!=containers.size()) break;
            }
            if (len==containers.size()) return;
        }
}

/**
 * @brief Amazon::numBagHoldBarCodes

First line contains two space separated integers, N and B.
N : no of items to be carried, B : length of each bar code.
Next N lines each contain B space separated integers (0's and 1's only) denoting Bar Code of corresponding items.

OUTPUT :
Minimum no. of bags required.

CONSTRAINTS :
1 <= N <= 10,000
1 <= B <= 32

 * @param barcodes
 * @return
 */
int Amazon::numBagHoldBarCodes(vector<vector<int> > &barcodes)
{
    vector<vector<vector<int> > > containers;

    for (int i=0; i<barcodes.size(); i++)
    {
        vector<vector<int> > code=vector<vector<int> >(1, barcodes[i]);
        containers.push_back(code);
//        insertContainers(code, containers);
//        cout << "containsize=" << containers.size() << endl;
    }
    mergeContainers(containers);

    return containers.size();
}

string Amazon::compressString(string str)
{
    if (str.empty()) return string();

    stringstream result;

    int i=0;
    while (i<str.size())
    {
        int count=1;
        int j;
        for ( j=i+1; j<str.size(); j++)
        {
            if (str[i]==str[j])
                count++;
            else
                break;
        }
        result << count << str[i];
        i = j;
    }
    return result.str();
}

static bool isAvailable(Position p, vector<vector<int> > & visited)
{
    if (p.x<0 || p.x >= visited[0].size() || p.y<0 || p.y >= visited.size())
        return false;
    if (visited[p.y][p.x] != 0) return false;

    return true;
}

void Amazon::printMatrixFromOutToInside(vector<vector<int> > &arr)
{
    if (arr.empty()) return;

    vector<vector<int> > visited(arr.size(), vector<int>(arr[0].size(), 0));

    Position p(0,0);
    while (true)
    {
        cout << arr[p.y][p.x] << " ";
        visited[p.y][p.x]=1;

        Position neighbor(p.x+1, p.y);
        if (isAvailable(neighbor, visited))
        {
            p=neighbor;
            continue;
        }
        neighbor=Position(p.x, p.y+1);
        if (isAvailable(neighbor, visited))
        {
            p=neighbor;
            continue;
        }
        neighbor=Position(p.x-1, p.y);
        if (isAvailable(neighbor, visited))
        {
            p=neighbor;
            continue;
        }
        neighbor=Position(p.x, p.y-1);
        if (isAvailable(neighbor, visited))
        {
            p=neighbor;
            continue;
        }

        break;
    }
}

static void generateDigits(int num, int currentDigit)
{
    if (currentDigit==0)
    {
        cout << num << endl;
        return;
    }
    int x=num*10+max(0, num%10-1);
    if (num%10 != x%10)
    generateDigits(x, currentDigit-1);
    int y=num*10+min(9, num%10+1);
    if (num%10 != y%10)
    generateDigits(y, currentDigit-1);

}

void Amazon::printNumbersWithDigitDiff1(int rangeDigits)
{
    if (rangeDigits<=0) return;
    for (int i=1; i<=9; i++)
        generateDigits(i, rangeDigits-1);
}

static bool isSnakePart(int y, int x, vector<vector<int> > & arr, vector<vector<int> > &visited, int reference)
{
    bool flag=false;
    if (y<0 || y>=arr.size() || x <0 || x>=arr.size() || visited[y][x]!=0) flag=false;
    else if (arr[y][x]==reference+1 || arr[y][x]==reference-1) flag=true;
    else flag=false;
//    cout << y << "," << x << "," << flag << endl;
//    cin.get();
    return flag;
}

vector<int> findSnake(int y, int x, vector<vector<int> > & arr, vector<vector<int> > & visited)
{
    vector<int> longestSnake;
    visited[y][x]=1;

//    cout << y << x << endl;
    for (int i=-1; i<=1; i+=2)
            if (isSnakePart(y+i, x, arr, visited, arr[y][x]))
            {
                vector<int> snake=findSnake(y+i, x, arr, visited);
                if ( longestSnake.size()<snake.size())
                {
                    longestSnake=snake;
                }
            }
    for (int i=-1; i<=1; i+=2)
            if (isSnakePart(y, x+i, arr, visited, arr[y][x]))
            {
                vector<int> snake=findSnake(y, x+i, arr, visited);
                if ( longestSnake.size()<snake.size())
                {
                    longestSnake=snake;
                }
            }
    longestSnake.push_back(arr[y][x]);

    return longestSnake;
}

void Amazon::printLongestSnake(vector<vector<int> > &arr)
{
    if (arr.empty()) return;

    int maxLen=0;
    vector<vector<int> > longestSnakes;
    for (int i=0; i<arr.size(); i++)
        for (int j=0; j<arr[0].size(); j++)
        {
            vector<vector<int> > visited(arr.size(), vector<int>(arr[0].size(), 0));
            vector<int> snake = findSnake(i, j, arr, visited);
            if (maxLen<snake.size())
            {
                maxLen=snake.size();
                longestSnakes.clear();
                longestSnakes.push_back(snake);
            }
            else if (maxLen==snake.size())
            {
                maxLen=snake.size();
                longestSnakes.push_back(snake);
            }

        }

    // print
//    cout << "numSnake=" << longestSnakes.size() << endl;
    for (int i=0; i<longestSnakes.size(); i++)
    {
        for (int j=0; j<longestSnakes[i].size(); j++)
        {
            if (j !=0 ) cout << "->";
            cout << longestSnakes[i][j];
        }
        cout << endl;
    }

}

void Amazon::printAnagrams(vector<string> &strvector)
{
    multimap<string, string> table;
    for (int i=0;i<strvector.size(); i++)
    {
        string str=strvector[i];
        string key(str);
        std::transform(str.begin(), str.end(), key.begin(), ::tolower);
        sort(key.begin(), key.end());
        table.insert(pair<string, string>(key, str));
    }

    for (multimap<string, string>::iterator itr=table.begin(); itr != table.end(); itr++)
    {
        cout << itr->second << " ";
    }
    cout << endl;
}

static int convertInt(vector<int> & barcode)
{
    int num=0;
    for (int i=0;i<barcode.size(); i++)
    {
        num = (num<<1) + barcode[i];
    }
    return num;
}

static int checkDistance(int x, int y)
{
    int z=x^y;
    int count=0;
    for (; z!=0; z=z&(z-1))
        count++;
    return count;
}

int Amazon::numBagHoldBarCodes_better(vector<vector<int> > &barcodes)
{
    if (barcodes.empty()) return 0;

    // convert to interges, put them into a queue;
    deque<int> bag_original;
    for (int i=0; i<barcodes.size(); i++)
    {
        int num=convertInt(barcodes[i]);
        bag_original.push_back(num);
//        cout << num << endl;
    }

//    cout << "bagSize=" << bag_original.size() << endl;

    // build match multimap
    multimap<int, int> table;
    for (int i=0; i<bag_original.size(); i++)
    {
        int key=bag_original[i];
        for (int j=0; j<bag_original.size(); j++)
        {
            int num=bag_original[j];
            int dist=checkDistance(key, num);
            if (dist<=2)
            {
                table.insert(pair<int, int>(key, num));
//                cout << i << "-" << j << ":" << dist << endl;
            }
        }
    }

//    cout << "tableSize=" << table.size() << endl;

//    // show table
//    for (multimap<int, int>::iterator i=table.begin(); i != table.end(); i++)
//        cout << i->first << "," << i->second << "-> ";
//    cout << endl << "after erase" << endl;
//    table.erase(table.find(2));
//    for (multimap<int, int>::iterator i=table.begin(); i != table.end(); i++)
//        cout << i->first << "," << i->second << "-> ";
//    cout << endl;

    // merge
    vector<deque<int> > finalBags;
    while (!bag_original.empty())
    {
        int key= bag_original.front();
        bag_original.pop_front();
//        cout << "key" <<key <<endl;

        deque<int> bag;
        queue<int> buff;
        buff.push(key);

        while (!buff.empty())
        {
            int num=buff.front();
            buff.pop();
            bag.push_back(num);

            while (table.find(num)!=table.end())
            {
                multimap<int, int>::iterator itr=table.find(num);
                int num2=itr->second;
//                cout << "num2=" << num2 << endl;
                deque<int>::iterator i=std::find(bag_original.begin(), bag_original.end(), num2);
                if (i!=bag_original.end())
                {
                    bag_original.erase(i);
                    buff.push(num2);
                }
                table.erase(itr);
//                for (multimap<int, int>::iterator i=table.begin(); i != table.end(); i++)
//                    cout << i->first << "," << i->second << "-> ";
//                cout << endl;
            }
        }
//        while (table.find(key) != table.end())
//        {
//            multimap<int, int>::iterator itr=table.find(key);
//            int num=itr->second;
//            cout << "num=" << num << endl;
//            deque<int>::iterator i=std::find(bag_original.begin(), bag_original.end(), num);
//            if (i!=bag_original.end())
//            {
//                bag_original.erase(i);
////                table.insert(pair<int, int>(key, num));
//                cout << "merge: " << key << "," << num <<endl;
//                bag.push_back(num);
//            }
//            table.erase(itr);
//        }
        for (deque<int>::iterator it=bag.begin(); it!=bag.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        finalBags.push_back(bag);
    }
    cout << "finalBagSize=" << finalBags.size() << endl;
}

static bool canBePart(string subWord, string word)
{
    return subWord.find(word)==0;
}

static int findWordCombination(string & str, int start,  vector<string> &dict)
{
    if (start>=str.size()) return 0;

    int numMax=-1;
    for (int i=0; i<dict.size(); i++)
    {
        string candidate=dict[i];
        if(canBePart(str.substr(start), candidate))
        {
            int numWords=findWordCombination(str, start+candidate.size(), dict);
            if (numWords != -1 && numMax<numWords+1)
                numMax=numWords+1;
        }
    }

    return numMax;

}

string Amazon::findWordMadeOfMaxWords(vector<string> &dict)
{
    if (dict.empty()) return string();

    int numMax=0;
    string wordMax;
    for (size_t i=0; i<dict.size(); i++)
    {
        string str=dict[i];
        int numWords = findWordCombination(str,0, dict);
        if (numWords>numMax)
        {
            numMax=numWords;
            wordMax=str;
        }
    }

    return wordMax;
}

static bool isPrime(int n)
{
    if (n==1) return false;
    if (n==2) return true;

    for (int i=2; i<=sqrt(n); i++)
    {
        if (n/i-double(n)/i==0) return false;
    }
    return true;

}

void Amazon::printPrimePairsLessThanNum(int n)
{
    if (n<=4) return;

    for (size_t i=2; i<n/2; i++)
    {
        if (isPrime(i))
        {
            for (size_t j=n/i; j>=2; j--)
            {
                if (isPrime(j))
                    cout << i << "," << j << endl;
            }
        }
    }
}

void Amazon::printKthLargestNumInBST(shared_ptr<TreeNode> & root, int k, int & count)
{
    if (!root || k<0) return;

    printKthLargestNumInBST(root->right, k, count);
    if (count==k)
    {
        cout << root->value << endl;
        return;
    }
    printKthLargestNumInBST(root->left, k, count);

}

/**
 * @brief Amazon::findMinIterationToDistributeApple

Problem: N boys are sitting in a circle. Each of them have some apples in their hand.
You find that the total number of the apples can be divided by N.
So you want to divide the apples equally among all the boys.
But they are so lazy that each one of them only wants to give one apple to one of the neighbors at one step.
Calculate the minimal number of steps to make each boy have the same number of apples.

Input Given:
1. A number N => number of children.
2. Sequence of N numbers, each representing number of apples a child has.

<<P.S.>>
Passing an apple means a child giving away one apple to one of its neighbour.
Even if 2 separate children can pass apples simultaneously or one child can pass 1-1 apple to each of its neighbours then that will still be counted as 2 steps and not 1 step.

Methodology:
1) convert to non-evenly distribute integer array to evenly-distributed array
2) using graph from start state to goal state, using DFS with queue, maybe two queues in order to count the iteration
3) each iteration: change two integers only, one is ++ and the neighbor is --, verse vice
   Possible way is: loop for each integer in the array,
                        If the integer is less than targeted number (number of apples / number of children), try to get one apple from one of two neighbors who has more apples to pass (update the array, push to queue), otherwsie do nothing
                        If the integer is larger than targeted number (number of apples / number of children), pass one apples to one of two neighbors who need more apples (update the array, push to queue), otherwise do nothing
                        If the integer equals targeted number (number of apples / number of children), do nothing

4) the solution is the path which is the first arrival to goal state

 * @param apples
 * @return
 */
int Amazon::findMinIterationToDistributeApple(vector<int> &apples)
{
    if (apples.empty()) return 0;
}

/**
 * @brief Amazon::caclNumToSwapBits
Given an array containing sequence of bits (0 or 1), you have to sort this array in the ascending order i.e. all 0' in first part of array followed by all 1's. The constraints is that you can swap only the adjacent elements in the array. Find the minimum number of swaps required to sort the given input array.
Example: Given the array (0,0,1,0,1,0,1,1) the minimum number of swaps is 3.
Note: You just need to complete the function given below for this task. The function is given a binary string as input and returns the required answer.
 * @param arr
 * @return
 */
int Amazon::caclNumToSwapBits(string &arr)
{
    if (arr.empty()) return 0;
    cout << arr << endl;

    int count=0, swap=0;
    for(int i=arr.size()-1; i>=0; i--)
    {
        if (arr[i]=='0')
            count ++;
        else
            swap += count;

//        cout << i << "," << arr[i] << "," << count << "," << swap << endl;
//        cin.get();

    }
    return swap;
}

/**
 * @brief Amazon::sortStringWithMap
 *Given a sorted string s1 and an unsorted string s2. Sort s2 based on the sorting algorithm applied in s1.
Ex:
s1 = fghab
s2 = abfmgfghnaixcv

Output: ffgghaabmnixcv

 * @param arr s2
 * @param order s1
 */
void Amazon::sortStringWithMap(string arr, string order)
{
    if (arr.empty() || order.empty())return;

    map<char, int> table;
    for (int i=0; i<order.size(); i++)
    {
        table[order[i]]=0;
    }

    string remain;
    for ( int i=0; i<arr.size(); i++)
    {
        if (table.find(arr[i]) != table.end())
        {
            table[arr[i]]++;
        }
        else
            remain = remain + arr[i];
    }

    int index=0;
    for (int i=0; i<order.size(); i++)
    {
        for (int j=0; j<table[order[i]]; j++)
        {
            arr[index++]=order[i];
        }
    }

    for (int i=index; i<arr.size(); i++)
        arr[i]=remain[i-index];

    cout << arr << endl;

}

/**
 * @brief Amazon::printSourceCode
 *How do you write a program which produces its own source code as output?
 */
void Amazon::printSourceCode()
{
    char str[] = "#include <stdio.h>%cchar str[] = %c%s%c;%cint main() { printf(str, 10, 34, str, 34, 10); return 0; }";
    printf(str, 10, 34, str, 34, 10);
}

static bool existX(vector<vector<int> > & arr, int y, int x, int len)
{
    if (arr.empty() || y<0 || y+len> arr.size() || x<0 || x+len > arr[0].size()) return false;

    for (int i=y, j=x; i<y+len && j<x+len; i++, j++)
        {
            if (arr[i][j] != 1 || arr[i][x+len-1-j] != 1) return false;
        }
    return true;
}

int Amazon::findBiggestX(vector<vector<int> > &arr)
{
    if (arr.empty()) return 0;

    int maxLen = std::min(arr.size(), arr[0].size());
//    cout << maxLen << endl;

    for (int len=maxLen; len>=1; len--)
    {
        if (len%2==0) continue; // even number

        for (int i=0; i<arr.size()-len+1; i++)
        {
            for (int j=0; j<arr[0].size()-len+1; j++)
            {
                bool find=existX(arr, i, j, len);
                if (find) return len;
            }
        }
    }

    return 0;
}

static int findMinElement(vector<vector<int> > & arr, vector<int> & pointers)
{
    int minV=INT_MAX;
    int index=0;
    for (int i=0; i<arr.size(); i++)
    {
        if (pointers[i] == -1) continue;

        int x=arr[i][pointers[i]];
        if (x<minV)
        {
            minV=x;
            index=i;
        }
    }

    pointers[index]++;
    if (pointers[index]>=arr[index].size())
        pointers[index]=-1;

    return minV;

}

/**
 * @brief Microsoft::sortMultipleArray: sort n sorted array into one array
 * @param arr
 */
void Microsoft::sortMultipleArray(vector<vector<int> > &arr)
{
    if (arr.empty()) return;

    vector<int> pointers(arr.size());
    for (int i=0; i<arr.size(); i++)
        pointers[i]=0;
    vector<int> result;
    while (true)
    {
        int x=findMinElement(arr, pointers);
        if (x != INT_MAX)
            result.push_back(x);
        else
            break;
    }

    for (int i=0; i<result.size(); i++)
        cout << result[i] << endl;
}

/**
 * @brief Microsoft::sortBigData
 *Given an array having 16000 unique integers, each lying within the range 1<x<20000, how do u sort it. U can load only 1000 numbers at a time in memory.
 * assume that the data unique (using bit operation), otherwise using hashtable to count the frequency
 * Here are generalized case:
 * 1) range are found by reading data to get maxValue and minValue
 * 2) the integer in data are not unique (duplicates). SO using map to count frequence, otherwise using bit operation
 *
 * @param data
 * @param range
 */
void Microsoft::sortBigData(vector<int> &data, const bool unique)
{
    if (data.empty()) return;

    if (!unique)
    {
        map<int, int> table;

        for (int i=0; i<data.size(); i++)
        {
            table[data[i]]++;
        }

        for (map<int, int>::iterator itr=table.begin(); itr != table.end(); itr++)
        {
            for (int i=0; i<itr->second; i++)
                cout << itr->first;
        }
    }
    else
    {
        int minV=INT_MAX,maxV=INT_MIN;

        for (int i=0; i<data.size(); i++)
        {
            int x=data[i];
            if (minV>x) minV=x;
            if (maxV<x) maxV=x;
        }

        int range = maxV-minV+1;
        int numMap = ceil(double(range)/32); // required integers;
        int *table=new int[numMap];
        for (int i=0; i<numMap; i++)
            table[i]=0;

        for (int i=0; i<data.size(); i++)
        {
            int x=data[i];
            int id = x/32;
            int bit = (x/32)%32;
            table[id] |= (1<<bit);
        }

        for (int i=0; i<numMap; i++)
        {
            int x=table[i];
            for (int j=0; j<32; j++)
            {
                if ((x>>j & 1) == 1)
                    cout << i*32+j << " ";
            }
        }
        cout << endl;

        delete [] table;
    }



}

double Microsoft::sqrtImplementation(double x, int iterNum)
{
    if (x<=0) return 0;

    double cur=1, pre=INT_MAX;
    for (int i=0; i<iterNum; i++)
    {
        pre=cur;
        cur=pre/2+x/(2*pre);

        if (cur==pre)
            break;
    }

    return cur;
}

//There is a buffer which could contain one-byte-long ASCIIs and/or two-byte-long Chinese characters. The first bit of ASCII is 0, and first bit of Chinese character is 1 (note: that means the first bit of the first byte of this chinese is 1, but the first bit of the second byte could be 0/1).
//Write a function to delete last ASCII or Chinese character. No addition data structure is allowed

//It looks simple, but the tricky part of this problem is to judge the last part of the buffer is ASCII or chinese character. For example, the first bit of the last byte is 0, the first bit of the last second byte is 1 which could combine with the last byte to become Chinese character or could combine with the last third character to become chinese character, So you need go backward further.
//It turn out to need a recursive method.

//Here is an example:

//...1xxxxxxx 1xxxxxxx 1xxxxxxx 1xxxxxxx 0xxxxxxx
//The last part could be chinese+ascii or chinese+chinese

//So, you cannot make decision until we find 0 bit (that means this byte is end of chinese or end of ascii) or reach the start of the buffer.

//The solution sems to use recursion:
//if we reach 0, the next byte is start of chinese or ascii, we can make decision;
//if we reach 1, we go backward to get another byte, and continue this recursion.
//if we reach the beginning of the buffer, we can make decision

//Can you believe it, this is a coding test I met. The above-mentioned solution seems what the interviewer like to see.

//You may feel that a simple solution is to start at the beginning of buffer, and continue until reaching the end of the buffer. Yes. But the interviewer wanted to test the complexity thinking. Crazy?
















