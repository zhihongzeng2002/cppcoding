#include "randomnum.h"
#include <random>
#include <time.h>
#include <iostream>

static int rand5()
{
    return rand()%5;
}

int RandomNum::generateRand7()
{
    srand(time(NULL));
    while (true)
    {
        int x=rand5()*5+rand5();
        if (x<21)
            return x%7;
    }
}

RandomNum::RandomNum()
{
}

void RandomNum::shuffleCards(vector<int> &cards)
{
    if (cards.size()==0)
    {
        cout << endl;
        cin.get();
        return;
    }


        int randNum = rand()%cards.size();

        int temp = cards[randNum];
        cards[randNum]=cards[0];
        cards[0]=temp;

        cout << temp << ",";
        vector<int> remainder(cards.begin()+1, cards.end());
        shuffleCards(remainder);

}

void RandomNum::shuffleCards(const int cardNum)
{
    vector<int> cards(cardNum);
    for (int i=0; i< cards.size(); i++)
        cards[i] =i;

    srand(time(NULL));
    shuffleCards_2(cards);

    for (int i=0; i< cards.size(); i++)
        cout << cards[i] << " ";
    cout << endl;
}

void RandomNum::shuffleCards_2(vector<int> &cards)
{
    if (cards.size()==0)
    {
        cout << endl;
        return;
    }

    for (size_t i=0; i< cards.size(); i++)
    {

        int randNum = rand()%(cards.size()-i)+i;

        int temp = cards[randNum];
        cards[randNum]=cards[i];
        cards[i]=temp;

    }
}

vector<int> RandomNum::pickRandomly(vector<int> &arr, const int m)
{
    if (arr.empty() || m==0) return vector<int>();

    srand(time(NULL));
    vector<int> arr_copy(arr);

    for (int i=0; i< m; i++)
    {
        int randNum = rand() % (arr.size()-i) + i;
        int temp = arr_copy[randNum];
        arr_copy[randNum]=arr_copy[i];
        arr_copy[i]=temp;

    }

    return vector<int>(arr_copy.begin(), arr_copy.begin()+m);
}
