#ifndef RANDOMNUM_H
#define RANDOMNUM_H

#include <vector>

using namespace std;

class RandomNum
{
public:
    RandomNum();

    void shuffleCards(vector<int> & cards);
    void shuffleCards_2(vector<int> & cards);
    void shuffleCards(const int cardNum);
    int generateRand7();

    vector<int> pickRandomly(vector<int> & arr, const int m);
};

#endif // RANDOMNUM_H
