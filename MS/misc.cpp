#include "misc.h"
#include <iostream>
#include <unordered_map>
#include <exception>
#include <limits.h>
#include <string.h>
#include <limits>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <sstream>

unsigned int Misc::concatenateInts(unsigned int x, unsigned int y)
{
    int temp=y;
    do
    {
        temp /= 10;
        x *=10;
    } while (temp>0);

    return x+y;
}

static void caclNumProbs(int numDice, int maxDice, int current, int sum, vector<float> & probs)
{
    if (current ==0)
    {
        probs[sum-numDice]++;
//        cout << __LINE__ << ":" << sum << ", "<<  sum-numDice << endl;
        return;
    }

    for (int i=1; i<=maxDice; i++)
    {
        caclNumProbs(numDice, maxDice, current-1, sum+i, probs);
    }


}

vector<float> Misc::computeProbabilitiesOfDiceSum(int numDice)
{
    if (numDice<=0) return vector<float>();

    int DiceMax=6;
    vector<float> probs(numDice*DiceMax-numDice+1, 0);

    int sum=0;
    caclNumProbs(numDice, DiceMax, numDice, sum, probs);

    int total=pow(DiceMax,numDice);
    cout << total << endl;

    for (int i=0; i<probs.size(); i++)
    {
        probs[i] /= total;
        cout << probs[i] << " ";
    }
    cout << endl;

    return probs;
}

map<int, string> Misc::buildMapFromNumToExcelHeader()
{
    map<int, string> table;
    queue<string> headerQueue;
    int num=0, MaxNum=2843;
    headerQueue.push(string());
//    for (int i=0; i<26; i++)
//    {
//        string x('A'+i);
//        headerQueue.push(x);
//        table.insert(pair<string, int>(num, x));
//        num++;
//    }

    while (num<MaxNum)
    {
        string t=headerQueue.front();
        headerQueue.pop();
        for (int i=0; i<26; i++)
        {
            stringstream temp;
            temp << char('A'+i);
//            char temp=static_cast<char>();
            string x(temp.str());
            string y=t+x;
//            cout << y <<"," << num << endl;
            headerQueue.push(y);
            table.insert(pair<int, string>(num, y));
            num++;
        }
    }
    return table;
}

string Misc::mapNumToExcelHeader(int num, map<int, string> &table)
{
    if (table.find(num) != table.end())
        return table.find(num)->second;
    else
        return string();
}

int Misc::divide(int a, int b)
{
    if (b==0) throw "invalid";
    else if (a<0 || b<0)
    {
        int x=a>0 ? a: -a;
        int y=b>0 ? b: -b;
        int z = divide(x, y);
        return (a<0) ^ (b<0) ? -z : z;
    }
    else if (a<b) return 0;
    else
        return 1+divide(a-b, b);
}

static void print(int *a, int n)
{
    int i;
     for (i = 0; i < n; i++)
       printf("%d\t", a[i]);
     printf("\n");
}

void Misc::radixsort(int *a, int n)
{
    int i, m = a[0], exp = 1;
    int *b=new int [n];
    for (i = 1; i < n; i++)
    {
      if (a[i] > m)
        m = a[i];
    }

    while (m / exp > 0)
    {
      int bucket[10] =
      {  0 };
      print(bucket, 10);
      for (i = 0; i < n; i++)
        bucket[(a[i] / exp) % 10]++;
      print(bucket, 10);
      for (i = 1; i < 10; i++)
        bucket[i] += bucket[i - 1];
      print(bucket, 10);
      for (i = n - 1; i >= 0; i--)
      {
          cout << ((a[i] / exp) % 10) << "," << bucket[(a[i] / exp) % 10] << endl;
        b[--bucket[(a[i] / exp) % 10]] = a[i];
      }
      for (i = 0; i < n; i++)
        a[i] = b[i];
      exp *= 10;

        printf("PASS   : ");
        print(a, n);
    }
    delete []b;
}

double Misc::powerInt(int a, int b)
{
    if (b==0) return 1;
    if (b<0)
    {
        double x = powerInt(a, -b);
        return 1/x;
    }
    int temp= powerInt(a, b/2);
    if (b%2==0)
        return temp*temp;
    else
        return a*temp*temp;
}

static void printTeam(vector<Person> &team)
{
    for (int i=team.size()-1; i>=0; i--)
    {
        cout << team[i].height << "," << team[i].weight << endl;
    }

}

void Misc::testBuildTower(int argc, char **argv)
{
    vector<Person> team=convertStreamToPersonTeam(argc, argv);
    printTeam(team);
    vector<Person> tallestTower=buildTallestTower2(team);
    cout << " solution 2 " << endl;
    printTeam(tallestTower);
    tallestTower=buildTallestTower(team);
    cout << " solution 1 " << endl;
    printTeam(tallestTower);
}

vector<Person> Misc::convertStreamToPersonTeam(int argc, char **argv)
{
    vector<Person> team;
    for (int i=0; i<(argc-1)/2; i++)
    {
        Person x(atoi(argv[i*2+1]), atoi(argv[i*2+2]));
        team.push_back(x);
    }
    return team;
}

static int computeTowerHeight(vector<Person> & tower)
{
    int height=0;
    for (int i=0; i<tower.size(); i++)
        height += tower[i].height;
    return height;
}

static vector<Person> buildTallestTower2_sub(vector<Person> &team, int index, map<int, vector<Person> > &table)
{
    if (index==team.size())
    {
        return vector<Person>();
    }
    if (table.find(index) != table.end())
        return table.find(index)->second;

    int tallest=0;
    vector<Person> tallestTower;
    for (int i=index; i<team.size(); i++)
    {
        vector<Person> tower=buildTallestTower2_sub(team, index+1, table);
        if (tower.empty() || team[i].weight<tower.back().weight)
        {
            tower.push_back(team[i]);
        }
        int height=computeTowerHeight(tower);
        if (tallest<height)
        {
            tallest=height;
            tallestTower=tower;
//            printTeam(tallestTower);
        }
    }
    table.insert(pair<int, vector<Person> >(index, tallestTower));
    return tallestTower;
}

vector<Person> Misc::buildTallestTower2(vector<Person> &team)
{
    sort(team.begin(), team.end());

    map<int, vector<Person> > table;
    return buildTallestTower2_sub(team, 0, table);
}

static vector<Person> buildTallestTower_sub(vector<Person> &team, Person &top, map<Person, vector<Person> > &table)
{
    if (top.height!=-1 && table.find(top)!=table.end()) return table.find(top)->second;

    vector<Person> tallestTeam;
    int tallest=0;
    for (int i=0; i<team.size(); i++)
    {
        if (team[i].canBeAbove(top))
        {
            vector<Person> subTeam=buildTallestTower_sub(team, team[i], table);
            int height=computeTowerHeight(subTeam);
            if (tallest<height)
            {
                tallest=height;
                tallestTeam=subTeam;
            }
        }

    }

    if (top.height!=-1)
    {
        tallestTeam.push_back(top);
        table.insert(pair<Person, vector<Person> >(top, tallestTeam));
    }
    return tallestTeam;
}

vector<Person> Misc::buildTallestTower(vector<Person> &team)
{
    if (team.empty()) return vector<Person>();

    map<Person, vector<Person> > table;
    Person a;
    return buildTallestTower_sub(team, a, table);
}

/**
 * @brief Misc::unconcatenating: separate str by space with the combination of dict words and the
 * minimum of non dic characters
 * @param str
 * @param dict
 * @param result
 * @return
 */
int Misc::unconcatenating(string &str, set<string> &dict, string &result)
{
    if (str.size()==0)
    {
        result=string();
        return 0;
    }
    if (dict.find(str)!=dict.end())
    {
        result=str;
        return 0;
    }
    int minnum=str.size();
    string minresult=str;
    for (int i=1; i<str.size(); i++)
    {
        int num;
        string temp;
        string left=str.substr(0,i);
        string right=str.substr(i);
        if (dict.find(left)==dict.end())
            num=left.size();
        else
            num=0;
        num += unconcatenating(right, dict, temp);
        temp=left+" "+temp;
        if (minnum>num)
        {
            minnum=num;
            minresult=temp;
        }
//        cout << minnum << "," << minresult << "--" << num << "," << temp << endl;
    }
    result=minresult;
    return minnum;

}

void Misc::printAllPairsWithTargetSum(vector<int> &data, int sum)
{
    // build hashtable
    unordered_set<int> hashTable;
    for (int i=0; i<data.size(); i++)
        hashTable.insert(data[i]);

    // search
    for (int i=0; i<data.size(); i++)
    {
        if (hashTable.find(sum-data[i])!=hashTable.end() && data[i]<=sum-data[i]) // avoid duplicate
        {
            cout << data[i] << " " << sum-data[i] << endl;
        }
    }
}

void Misc::printAllPairsWithTargetSum2(vector<int> &data, int sum)
{
    // sort
    sort(data.begin(), data.end());
    int first=0, last =data.size()-1;
    while (first<last)
    {
        int s=data[first]+data[last];
        if (s==sum)
        {
            cout << data[first]<< " " << data[last] << endl;
            first++;
            last--;
        }
        else if (s<sum)
        {
            first++;
        }
        else
            last++;

    }
}

string string1000[]={"thousand", "million", "billion"};
string string10[]={"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
string stringteen[]={"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen"};
string digit[]={"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

static vector<string> print100(int num)
{
    vector<string> result;
    int remain=num % 100;
    if (remain>1 && remain<=10)
    result.push_back(digit[remain-1]);
    else if (remain>10 && remain <20)
        result.push_back(stringteen[remain%10-1]);
    else if (remain>=20 && remain<100)
    {
        if (remain%10>0)
            result.push_back(digit[remain%10-1]);
        result.push_back(string10[remain/10-2]);
    }

    num /=100;
    if (num>0)
    {
        result.push_back("hundred");
        result.push_back(digit[num-1]);
    }

    return result;
}

static void reversePrint(vector<string> & result)
{
    // print
    for (int i=result.size()-1; i>=0; i--)
        cout << result[i] << " ";
    cout << endl;

}

void Misc::printNumbers(int num)
{
    vector<string> result;
    if (num==0)
    {
        result.push_back("Zero");
    }
    else if (num<0)
    {
        cout << "Negative ";
        printNumbers(-num);
    }

    int factor=1000;
    int i=0;
    while (num>0)
    {
        int t = num%factor;
        vector<string> y=print100(t);
        result.insert(result.end(), y.begin(), y.end());

//        int x=(num%10000)/factor;
        if (num/factor>0)
        {
        result.push_back(string1000[i]);
        }
        num /= factor;
        i++;

    }
    reversePrint(result);

}

/**
 * @brief Misc::findMinDistanceToSort: find the minimum range to sort in a array
 * in order to get full sorted array
 * @param data
 * @return
 */
int Misc::findMinDistanceToSort(vector<int> &data)
{
    if (data.empty()) return 0;

    // sort from beginning
    int i;
    for (i=1; i<data.size(); i++)
    {
        if (data[i]<data[i-1])
        {
            break;
        }
    }
    int unsortedBegin=i-1;
//    cout << unsortedBegin << endl;

    // sort from end;
    for (i=data.size()-1; i>=1; i--)
        if (data[i]<data[i-1])
            break;
    int unsortedEnd=i;

    // find the min and max in between sorted parts
    if (unsortedEnd<=unsortedBegin) return 0;

    int minV=INT_MAX, maxV=INT_MIN;
    for (i=unsortedBegin; i<=unsortedEnd; i++)
    {
        if (minV>data[i]) minV=data[i];
        if (maxV<data[i]) maxV=data[i];
    }

    // find min distance
    int m=unsortedBegin, n=unsortedEnd;
    for (i=0; i<unsortedBegin; i++)
    {
        if (data[i]>minV)
        {
            m=i;
            break;
        }
    }
    for (i=data.size()-1; i>unsortedEnd; i--)
    {
        if (data[i]<maxV)
        {
            n=i;
            break;
        }
    }
    cout << m << " " << n << endl;
    return n-m;
}

static map<char, int> countColor(string & color)
{
    map<char, int> count;
    for (int i=0; i<color.size(); i++)
    {
        count[color[i]]++;
    }
    return count;
}

GuessResult Misc::guessHitGame(string &computer, string &guess)
{
    if (computer.size() != guess.size() || computer.size()==0)
    {
        cout << "Invalide Inputs" << endl;
        return GuessResult();
    }

    // compute hit
    int hit =0;
    for (int i=0; i<computer.size(); i++)
    {
        if (computer[i]==guess[i])
            hit++;
    }

    // count for guess
    map<char, int> countGuess=countColor(guess);
    map<char, int> countComputer=countColor(computer);

    // compute same color
    int pseduoHit=0;
    for (map<char, int>::iterator itr=countComputer.begin(); itr != countComputer.end(); itr++)
    {
        char key=itr->first;
        if (countGuess.find(key)!=countGuess.end())
            pseduoHit += std::min(itr->second, countGuess[key]);
    }

    // get the pseduo
    pseduoHit -= hit;

    GuessResult t(hit, pseduoHit);
    t.print();

    return t;

}

static int signInt(int a)
{
    return (a>>31 & 1)^1;
}

static int flip(int a)
{
    return a^1;
}

int Misc::getMaxWithoutIf(int a, int b)
{
    int c=a-b;
    int signa=signInt(a);
    int signb=signInt(b);
    int signc=signInt(c);
    cout << signa << " " << signb << " " << signc << endl;

    int signk=(signa^signb)*signa +flip(signa^signb)*signc;
    int signq=flip(signk);

    cout << signk << " " << signq << endl;
    return signk*a + signq*b;
}

static int convertBoardToInt(vector<vector<TicCell> > &board)
{
    int sum=0;
    int factor=1;
    for (int i=0; i<board.size(); i++)
        for (int j=0; j<board[0].size(); j++)
        {
            sum = sum*factor+board[i][j].value;
            factor *= 3;
        }
    return sum;
}

bool Misc::hasWonTicTacToe(vector<vector<TicCell> > & board)
{
    int num=convertBoardToInt(board);
    set<int> winMap;
    //......build map

    return winMap.find(num)!=winMap.end();
}

TicTacState Misc::hasWonTicTacToe2(vector<vector<TicCell> > &board)
{
    // check row
    for (int i=0; i<board.size(); i++)
    {
        if (board[i][0].value==BLANK)
            break;
        int j=0;
        for (j=0; j<board[i].size()-1; j++)
        {
            if (board[i][j].value!=board[i][j+1].value)
                break;
        }
        if (j==board[i].size()-1)
            return board[i][0].value;
    }
    // check column
    for (int i=0; i<board.size(); i++)
    {
        if (board[0][i].value==BLANK)
            break;
        int j=0;
        for (j=0; j<board[i].size()-1; j++)
        {
            if (board[j][i].value!=board[j+1][i].value)
                break;
        }
        if (j==board[i].size()-1)
            return board[i][0].value;
    }
    // check diagnol
    for (int i=0; i<board.size()-1; i++)
    {
        if (board[0][0].value==BLANK)
            break;
        int t=0;
        if (board[i][i].value==board[i+1][i+1].value)
                t++;
        if (t==board[i].size()-1)
            return board[0][0].value;
    }
    // check reverse diagnol
    for (int i=0; i<board.size()-1; i++)
    {
        if (board[board.size()-1][0].value==BLANK)
            break;
        int t=0;
        if (board[board.size()-1-i][i].value==board[board.size()-1-(i+1)][i+1].value)
                t++;
        if (t==board[i].size()-1)
            return board[board.size()-1][0].value;
    }
    return BLANK;
}

void Misc::swapTwoNumbers(int &a, int &b)
{
    a=a^b;
    b=a^b;
    a=a^b;
}

static void getOneEditDistWords(string &word, queue<string> & wordQueue, set<string> & dict)
{
    for (int i=0; i<word.size(); i++)
    {
        char t=word[i];
        for (char j='a'; j<='z'; j++)
        {
            word[i]=j;
            if (j!=t && dict.find(word)!=dict.end())
                wordQueue.push(word);
        }
    }

}

/**
 * @brief Misc::findPathBetweenTwoWord
 * @param startword
 * @param endword
 * @param dict
 */
void Misc::findPathBetweenTwoWord(string &startword, string &endword, set<string> &dict)
{
    if (startword.empty() || endword.empty() || dict.size()==0)
        return;

    stack<string> path;

    queue<string> wordQueue;
    wordQueue.push(startword);

    while (!wordQueue.empty())
    {
        string word=wordQueue.front();
        wordQueue.pop();
        if (word==endword)
        {
            while (!path.empty())
            {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
            return;
        }

        getOneEditDistWords(word, wordQueue, dict);
    }
}

enum MoveDirection
{
    MOVE_LEFT,
    MOVE_RIGHT
};

static bool comparatorInt(int x, int y)
{
    return x>y;
}

static void switchElement(vector<int> & maxHeap, vector<int> &minHeap, MoveDirection flag)
{
    if (flag==MOVE_RIGHT)
    {
        int y=maxHeap.back();
        maxHeap.pop_back();
        sort(maxHeap.begin(), maxHeap.end());

        minHeap.push_back(y);
        sort(minHeap.begin(), minHeap.end(), comparatorInt);
    }
    else
    {
        int y=minHeap.back();
        minHeap.pop_back();
        sort(minHeap.begin(), minHeap.end(), comparatorInt);

        maxHeap.push_back(y);
        sort(maxHeap.begin(), maxHeap.end());

    }

}

static float getMedian(int t, vector<int> & minHeap, vector<int> & maxHeap)
{
    if (maxHeap.empty())
    {
        maxHeap.push_back(t);
        return t;
    }
    else
    {
        if (t > maxHeap.back())
        {
            minHeap.push_back(t);
            sort(minHeap.begin(), minHeap.end(), comparatorInt);
        }
        else
        {
            maxHeap.push_back(t);
            sort(maxHeap.begin(), maxHeap.end());
        }
        // balance two heap
        if (maxHeap.size()<minHeap.size())
            switchElement(maxHeap, minHeap,MOVE_LEFT);
    }

    if(minHeap.size()+maxHeap.size() & 1 ==1)
        return (float)maxHeap.back();
    else
        return ((float)maxHeap.back()+minHeap.back())/2;
}

void Misc::getMedianInStream(vector<int> &arr)
{
    vector<int> minHeap, maxHeap;
    for (int i=0; i<arr.size(); i++)
    {
        cout << getMedian(arr[i], minHeap, maxHeap) << endl;
    }
}

static bool comparator(string w1, string w2)
{
    return w1.length()<w2.length() ;
}

static bool isWordCombination(string & word, bool isOriginal, map<string, bool> & dict)
{
    if (dict.find(word)!=dict.end() &&  !isOriginal)
        return dict.find(word)->second;

    for (int i=1; i<word.size(); i++)
    {
        string left=word.substr(0, i);
        string right=word.substr(i);
        if (dict.find(left)!=dict.end() && isWordCombination(right, false, dict))
            return true;
    }
    dict.insert(pair<string, bool>(word, false));
    return false;
}

string Misc::findLongestWordMadeofOtherWords(vector<string> &dict)
{
    // sort
    sort(dict.begin(), dict.end(), comparator);

    // build map
    map<string, bool> wordSet;
    for (int i=0; i<dict.size(); i++)
        wordSet.insert(pair<string, bool>(dict[i], true));

    // loop to check
    for (int i=dict.size()-1; i>=0; i++)
    {
        if (isWordCombination(dict[i], true, wordSet))
            return dict[i];
    }
}

/**
 * @brief Misc::findSmallestNums_heap: find n of smallest number in the heap
 * build a heap to maintain the n of smallest numbers;
 * Complexity: O(n*numSmallest)
 * @param nums
 * @param length
 * @param numSmallest
 * @return
 */
vector<int> Misc::findSmallestNums_heap(int nums[], int length, const int numSmallest)
{
    if (!nums || numSmallest<=0 || numSmallest>length)return vector<int>();

    vector<int> smallVector;
    for (int i=0; i< length; i++)
    {
        if (i<numSmallest)
            smallVector.push_back(nums[i]);
        else
        {
            sort(smallVector.begin(), smallVector.end());
            if (nums[i]<smallVector.back())
            {
                smallVector.pop_back();
                smallVector.push_back(nums[i]);
            }
        }

    }
    return smallVector;
}

/**
 * @brief Misc::findSmallestNums: complexity O(n)
 * @param nums
 * @param low_original
 * @param high_original
 * @param numSmallest
 */
void Misc::findSmallestNums(int nums[], int low_original, int high_original, const int numSmallest)
{
    if (high_original==numSmallest) return;
    int pivot=nums[(low_original+high_original)/2];

    int low=low_original;
    int high=high_original;
    while (low<high)
    {
        while (nums[low]<pivot)
        {
            low++;
        }
        while (nums[high]>pivot)
        {
            high--;
        }

        if (low<=high)
        {
            int temp=nums[low];
            nums[low]=nums[high];
            nums[high]=temp;

            low++;
            high--;
        }

    }
    int index=low;
    if (index==numSmallest) return;
    else if (index<numSmallest)
        findSmallestNums(nums, index, high_original, numSmallest);
    else
        findSmallestNums(nums, low_original, index-1, numSmallest);

}

void Misc::findSmallestNums_main(int nums[], int length, const int numSmallest)
{
    if (!nums || length<=0 || numSmallest<=0) return;
    findSmallestNums(nums, 0, length-1, numSmallest);
}

/**
 * @brief Misc::minDistanceBetween: it is based on book
 * @param book
 * @param str1
 * @param str2
 * @return
 */
int Misc::minDistanceBetween(const vector<string> &book, const string &str1, const string &str2)
{
    if (book.empty())return 0;

    int pointerStr1=-1, pointerStr2=-1;
    int minDif=INT_MAX;
    for (int i=0; i< book.size(); i++)
    {
        string word=book[i];
        if (word==str1)
        {
            pointerStr1=i;

            if (pointerStr2 <0 ) continue;

            if (i-pointerStr2<minDif)
                minDif=i-pointerStr2;
        }
        else if (word==str2)
        {
            pointerStr2=i;

            if (pointerStr1 <0) continue;

            if (i-pointerStr1<minDif)
                minDif=i-pointerStr1;
        }
    }
    return minDif;
}

/**
 * @brief countDigitsInRange_sub:
 * @param num
 * @param bit
 * @return
 */
static int countDigitsInRange_sub(const int num, const int bit, int targetDigit)
{
    int power10=10^bit;
    int power100=power10*10;
    int right=num % power10;

    int roundDown = num-num%power100;
    int roundUp = roundDown+power100;

    int digit = (num/power10)%10;
    if (digit<targetDigit)
        return roundDown/10;
    else if (digit==targetDigit)
        return roundDown/10 + right+1;
    else
        return roundUp/10;

}

/**
 * @brief Misc::countDigitsInRange :the number of targeted digit (0-9) between 0 to num;
 * @param num
 * @param digit
 * @return
 */
int Misc::countDigitsInRange(const int num, const int digit)
{
    if (num<0 || digit>9 || digit<0)
        return 0;
    // get the number of digits
    char str[33];
    sprintf(str, "%d", num);
    int numDigit=strlen(str);

    int count=0;
    for (int i=0; i<numDigit; i++)
        count += countDigitsInRange_sub(num, i, digit);

    return count;
}

static int recursiveGetMaxDiff(int *start, int *end, int &maxV, int &minV);

int Misc::getMaxDiff(int *seq, int length)
{
    if (!seq || length<2) throw "Inputs are out of range";

    int maxV=0, minV=0;
    return recursiveGetMaxDiff(seq, seq+length-1, maxV, minV);
}

int recursiveGetMaxDiff(int *start, int *end, int &maxV, int &minV)
{
    if (start==end)
    {
        maxV=minV=*start;
        return INT_MIN;
    }
    int *middle=start+(end-start)/2;
    int leftMax, leftMin, rightMax, rightMin;
    int leftMaxDiff=recursiveGetMaxDiff(start, middle, leftMax, leftMin);
    int rightMaxDiff=recursiveGetMaxDiff(middle+1, end, rightMax, rightMin);
    maxV = (leftMax>rightMax) ? leftMax : rightMax;
    minV = (leftMin<rightMin) ? leftMin : rightMin;
    int crossDiff = leftMax-rightMin;
    return max(leftMaxDiff, max(rightMaxDiff, crossDiff));
}

static bool isUgly(int x)
{
    while (x % 2 ==0) x /=2;
    while (x % 3 ==0) x /=3;
    while (x % 5 ==0) x /=5;
    return (x==1)? true: false;

}

int Misc::GetUglyNum(int index)
{
    if (index<=0) return 0;

    int number=0;
    int uglyCount=0;
    while (uglyCount < index)
    {
        number++;
        if (isUgly(number)) uglyCount++;
    }
    return number;
}

void Misc::reorderOddEven(int *seq, int length, MyFunctor &t)
{
    // check inputs
    if (!seq || length<=0) return;

    // reorder
    int *start=seq, *end=seq+length-1;

    while (start<end)
    {
        while (t(*start)) start++;

        while (!t(*end)) end--;

        // swap
        if (start<=end)
        {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
        }
    }

    // print
    for (int i=0; i<length; i++)
        cout << seq[i] << endl;
}

void printSequence(int small, int big)
{
    for (int i=small; i<=big; i++)
        cout << i << ' ';
    cout << endl;
}

/** print the unsigned int sequence which sum is targeted num
 * @param n the target sum
 */
void Misc::sequenceSum(const int n)
{
    // input check
    if (n<=2) return;

    // initialization
    int small=1, big=2;
    int sum=small+big;

    while (small < (n+1)/2 && small <big)
    {
        if (sum==n) printSequence(small, big);

        while (sum>n)
        {
            sum -= small;
            small++;

            if (sum==n) printSequence(small, big);
        }

        big++;
        sum += big;
    }
}

int Misc::numOfOnes(int n)
{
    int count=0;
    while(n)
    {
        count++;
        n = (n-1) & n;
    }
//    size_t flag=1;
//    while (flag)
//    {
//        if (n & flag ) count++;
//        flag=flag<<1;
//    }
    return count;
}

static int jumpStair(int n, unordered_map<int, int> & hashmap)
{
    if (n<0) return 0;
    if (n==0) return 1;
//    if (n==1) return 1;
//    if (n==2) return 2;

    unordered_map<int, int>::iterator itr=hashmap.find(n);
    if (itr != hashmap.end())
        return itr->second;
    else
    {
        int x=jumpStair(n-1, hashmap)+jumpStair(n-2, hashmap)+ jumpStair(n-3, hashmap);
        hashmap.insert(pair<int, int>(n, x));
        return x;
    }

}

int Misc::jumpStair_main(int n)
{
    if (n<=0) return 0;
    unordered_map<int, int> hashmap;
    return jumpStair(n, hashmap);

}

int Misc::fibonacci(const int n)
{
    if (n<0) throw "input must >= 0";
    if (n==0) return 0;
    if (n==1) return 1;

    int first=0, second=1;
    int f;
    for (int i=2; i<=n; i++)
    {
        f = first+second;
        first = second;
        second = f;

    }
    return f;
}

void Misc::findKLeastNumbers(const std::vector<int> & data, std::multiset<int> & leastNums, size_t k)
{
    if (data.size() < k || k==0 ) return;
    leastNums.clear();

    for (vector<int>::const_iterator itr=data.begin(); itr != data.end(); itr++ )
    {
        if (leastNums.size()<k) leastNums.insert(*itr);
        else
        {
            multiset<int>::iterator lastItr = leastNums.end();
            --lastItr;
            if (*itr < *(lastItr))
            {
                leastNums.erase(lastItr);
                leastNums.insert(*itr);
            }
        }
    }
    // print
    for (multiset<int>::iterator itr=leastNums.begin(); itr != leastNums.end(); itr++)
        cout << *itr << ' ';

    cout << endl;
}

bool Misc::findGreatestSumOfSubArray(int *pData, size_t nlength, int &greatestSum)
{
    if (!pData || nlength==0) return false;

    int curSum=greatestSum=0;
    for (size_t i=0; i<nlength; i++)
    {
        curSum += pData[i];

        if (curSum<0) curSum=0;

        if (curSum>greatestSum) greatestSum=curSum;

    }

    if (greatestSum==0)
    {
        greatestSum=pData[0];
        for (size_t i=1; i<nlength; i++)
        {
            if (pData[i]>greatestSum) greatestSum=pData[i];
        }
    }
    return true;
}
