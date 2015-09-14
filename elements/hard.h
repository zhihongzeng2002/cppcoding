#ifndef HARD_H
#define HARD_H

#include <vector>
#include <string>

using namespace std;

class Hard
{
public:
    Hard();

    int addTwoInts(int a, int b);

    void shuffleCards(vector<int> & cards, int k);

    int countDigit_bruteforce(int n, int digit);
    int countDigit_efficient(int n, int digit);

    string findLongestWordBuiltInDict(vector<string> &dic);

    void searchString_trie(const string str, const vector<string> & A);

    vector<string> buildLargestWordRectangle(vector<string> &dict);

    // time: O(M2N2)
    int findMaxSub2DArray(vector<vector<int> > & A);
    // time: O(M2N)
    int findMaxSub2DArray_efficient(vector<vector<int> > &A);

    // find the max square with black border
    tuple<int, int, int> findMaxBlackBorderSquare(const vector<vector<int> > &A);
};
#endif // HARD_H
