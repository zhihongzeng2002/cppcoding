#include "mystring.h"
#include <string.h>
#include <iostream>
#include <stack>
#include <list>
#include <limits.h>
#include <algorithm>
#include <unordered_map>

using namespace std;

static string computeKey(string &word_original)
{
    string word(word_original);
    std::transform(word_original.begin(), word_original.end(), word.begin(), ::tolower);
    sort(word.begin(), word.end());
    return word;
}

void MyString::sortAnagramsByhashing(vector<string> &words)
{
//    printWords(words);

    // build hashing with collison
    unordered_map<string, list<string> > hashTable;
    for (int i=0; i<words.size(); i++)
    {
        string key=computeKey(words[i]);
        if (hashTable.find(key) == hashTable.end())
        {
            list<string> wordlist;
            wordlist.push_back(words[i]);
            hashTable.insert(pair<string, list<string> >(key, wordlist));
        }
        else
            hashTable.find(key)->second.push_back(words[i]);
    }

    // print
    for (unordered_map<string, list<string> >::iterator itr=hashTable.begin(); itr != hashTable.end(); itr++)
    {
        list<string> t=itr->second;
        for (list<string>::iterator itrlist=t.begin(); itrlist != t.end(); itrlist++)
            cout << *itrlist << " ";
    }
    cout << endl;


}

static int convertStringToInt(string &x)
{
    int sum=0;
    for (int i=0; i<x.size(); i++)
    {
        char c=x[i];
        c=std::tolower(c)-'a';
        sum |= 1<<c;
    }
    return sum;
}

static bool anagramComparator(string x, string y)
{
    int sumx=convertStringToInt(x);
    int sumy=convertStringToInt(y);
    return sumx < sumy;
}

void MyString::printWords(vector<string> &words)
{
    for (int i=0; i<words.size(); i++)
        cout << words[i] << endl;
    cout << endl;
}

void MyString::sortAnagrams(vector<string> &words)
{
    printWords(words);
    std::sort(words.begin(), words.end(), anagramComparator);
    printWords(words);
}

void MyString::deleteChars(char *pSource, char *pDelete)
{
    if (!pSource || !pDelete) return;

    int hashTable[256]; // assum ASCII
    memset(hashTable, 0, sizeof(hashTable));

    for (char * temp=pDelete; *temp != '\0'; temp++)
        hashTable[*temp]++;

    char *pFast=pSource, *pSlow=pSource;
    while (*pFast != '\0')
    {
        if (!hashTable[*pFast])
        {
            *pSlow = *pFast;
            pSlow++;
        }
        pFast++;
    }
    *pSlow = '\0';

    cout << pSource << endl;

}

void MyString::combination(char *str)
{
    if (!str) return;

    list<string> mySet;

    for (char *cur = str; *cur != '\0'; cur++)
    {
//        char t=*cur;
        string myChar(1, cur[0]);
        list<string> smallSet;
        // add to the exist set
        for (list<string>::iterator itr=mySet.begin(); itr != mySet.end(); itr++)
        {
            string temp(*itr);
            temp += myChar;
            smallSet.insert(smallSet.end(), temp);
        }

        // merge
        mySet.splice(mySet.end(), smallSet);
            // add itself
        mySet.insert(mySet.end(), myChar);
    }

    // print
    for (list<string>::iterator itr = mySet.begin(); itr != mySet.end(); itr++)
        cout << (*itr).c_str() << endl;

}

void MyString::combination_2(char *str, std::vector<char> &seq)
{
    if (!str) return;
    if (*str=='\0')
    {
        if (seq.empty()) return;
        for (int i=0; i< seq.size(); i++)
            printf("%c", seq[i]);
        printf("\n");
        return;
    }

    seq.push_back(*str);
    combination_2(str+1, seq);
    seq.pop_back();
    combination_2(str+1, seq);

}

void permutation_rec(char *str, char *begin)
{
    if (!str || !begin) return;

    if ( *begin=='\0' )
    {
        cout << str << endl;
    }
    else
    {
        for (char *cur = begin; *cur != '\0'; cur++)
        {
            char temp = *cur;
            *cur = *begin;
            *begin = temp;

            permutation_rec(str, begin+1);

            temp = *cur;
            *cur = *begin;
            *begin = temp;
        }
    }
}

void MyString::permutation(char *str)
{
    // check
    if (!str) return;

    permutation_rec(str, str);
}

void MyString::reverseBuffer(char *buff, int start, int end)
{
    if (!buff) return;
    while (start<end)
    {
        char temp=buff[start];
        buff[start]=buff[end];
        buff[end]=temp;

        start++;
        end--;
    }
}

void MyString::reverseSentence(char *sentence)
{
    if (!sentence) return;

    int length = strlen(sentence);

    // reverse all chars
    reverseBuffer(sentence, 0, length-1);

    // reverse each word
    int start=0; int end=0;
    while (end < length)
    {
        while (sentence[start] == ' ' && end <= length-1 )
        {
            start++;end++;
        }

        while (sentence[end] != ' ' && end <= length-1) end++;

        end--;
        reverseBuffer(sentence, start, end);

        start=end+1;
        end=start;

    }
}

enum decreaseDir{
    Dirinit=0,
    Dirleftup,
    Dirleft,
    Dirup
};

void print_LCS(char * seq1, int * direction, int len1, int len2, int row, int col, stack<char> & cLCS)
{
    if (!seq1 || !direction || len1<=0 || len2<=0 || row<0 || col<0) return;

    // using stack to reverse seq

    if (direction[row*len2+col]==Dirleftup)
    {
        cLCS.push(seq1[row]);
//        cout << seq1[row] << ' ';
        print_LCS(seq1, direction, len1, len2, row-1, col-1, cLCS);
    }
    else if (direction[row*len2+col]==Dirup)
    {
        if (row>0)
        print_LCS(seq1, direction, len1, len2, row-1, col, cLCS);
    }
    else if (direction[row*len2+col]==Dirleft)
    {
        if (col>0)
        print_LCS(seq1, direction, len1, len2, row, col-1, cLCS);
    }
}

void MyString::LCS(char *seq1, char *seq2)
{
    // check inputs
    if (!seq1 || !seq2 ) return;
    int len1=strlen(seq1);
    int len2=strlen(seq2);

    // initialize the direction matrix
    int * direction = new int[len1*len2];
    for (int i=0; i<len1; i++)
        for (int j=0; j<len2; j++)
            direction[i*len2+j]=Dirinit;

    // initialize the distance matrix
    int * distance = new int[len1*len2];
    for (int i=0; i<len1; i++)
        for (int j=0; j<len2; j++)
        {
            if (seq1[i]==seq2[j])
            {
                distance[i*len2+j]=1;
                if (j==0 || i==0)
                    direction[i*len2+j]=Dirleftup;
            }
            else
                distance[i*len2+j]=0;
        }

    for (int i=1; i<len1; i++)
        for (int j=1; j<len2; j++)
        {
            if (distance[i*len2+j]==1)
            {
                distance[i*len2+j]=distance[(i-1)*len2+j-1]+1;

                direction[i*len2+j]=Dirleftup;
            }
            else if (distance[(i-1)*len2+j] > distance[i*len2+j-1])
            {
                distance[i*len2+j]=distance[(i-1)*len2+j];
                direction[i*len2+j]=Dirup;
            }
            else
            {
                distance[i*len2+j]=distance[i*len2+j-1];
                direction[i*len2+j]=Dirleft;
            }
        }

    cout << "The size of LCS = " << distance[(len1-1)*len2+len2-1] << endl;

    stack<char> cLCS;
    print_LCS(seq1, direction, len1, len2, len1-1, len2-1, cLCS);

    while (cLCS.size())
    {
        cout << cLCS.top() << ' ';
        cLCS.pop();
    }

    cout << endl;

    delete [] distance;
    delete [] direction;

}

void MyString::LCSubstring(char *seq1, char *seq2)
{
    // check inputs
    if (!seq1 || !seq2) return;

    // initialize the length matrix
    int len1=strlen(seq1);
    int len2=strlen(seq2);
    int *lcsLength=new int [len1*len2];

    for (int i=0; i<len1; i++)
        for (int j=0; j<len2; j++)
        {
            if (seq1[i]==seq2[j])
                lcsLength[i*len2+j]=1;
            else
                lcsLength[i*len2+j]=0;
        }

    // update the length matrix
    for (int i=1; i<len1; i++)
        for (int j=1; j<len2; j++)
        {
            if (lcsLength[i*len2+j]==1)
                lcsLength[i*len2+j] += lcsLength[(i-1)*len2+j-1];
        }

    // print outputs, including LCSubstring size and substring
    // find the largest length
    int maxValue=INT_MIN;
    int x=0, y=0;
    for (int i=0; i<len1; i++)
        for (int j=0; j<len2; j++)
        {
            if (maxValue<lcsLength[i*len2+j])
            {
                maxValue=lcsLength[i*len2+j];
                y=i;
                x=j;
            }
        }

    cout << "size of LCSubstring = " << maxValue << endl;

    // use stack to reverse LCS
    stack<char> lcs;
    for (int i=0; i<maxValue; i++)
        lcs.push(seq1[y-i]);

    while (lcs.size())
    {
        cout << lcs.top();
        lcs.pop();
    }
    cout << endl;

    delete [] lcsLength;
}

void MyString::rotation(char *seq1, int numRotation)
{
    if (!seq1 || numRotation<=0) return;

    int len=strlen(seq1);

    //handle if numRotation>len;
    numRotation %= len;
    if (!numRotation) return;

    int firstStart=0;
    int firstEnd=numRotation-1;
    int secondStart=numRotation;
    int secondEnd=len-1;

    reverseBuffer(seq1, firstStart, firstEnd);
    reverseBuffer(seq1, secondStart, secondEnd);
    reverseBuffer(seq1, firstStart, secondEnd);

}
