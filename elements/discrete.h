#ifndef DISCRETE_H
#define DISCRETE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Discrete
{
public:
    Discrete();

    string find_closest_palindrome(const unsigned a);
    // problem 21.13
    int find_max_floor(int ncase, int ndrop);
    /* Function to get minimum number of trails needed in worst
      case with n eggs and k floors */
    int eggDrop(int negg, int nfloor);

    // 21.13.2: find the last item after continue removing the nth item
    int find_last_deletedItem(int len, int k);
    int josephus(int n, int k);// same problem as the above
    int josephus_start(int n, int k, int survivor)
    {
        int survivor0 = josephus(n, k);
        int diff=survivor0-survivor;
        if (diff>=0)
            return (1+diff);
        else
            return (n+1+diff);
    }

    map<int, int> pairProfessorStudent(vector<vector<int> > & student_preference, vector<vector<int> > & professor_preference);

    //21.19 we can use the above method, by building preference with amount. i.e.,
    // bidder_preference is based on the money the bidder offer for each celebraty, high money high preference.
    // celebraty_preference is based on the money the money from bidder, high money high priority
    vector<pair<int, int> > biddersCelebrities(){}

    // remove the last word which could be 1byte (English) or 2byte(Chinese),
    //  and first bit of each word is the indicate of English (0) or Chinese (1).
    //  The first bit of second byte of Chinese could be 0 or 1;
    void removeLastWord(vector<char> & words);

    int findCelebrityLinearTime(vector<vector<int> > &relationTable);

    // problem 21.12
    int find_max_product_without_one(vector<int> &arr);
    int find_max_product_without_one_1space(const vector<int> &arr);

    // 21.10
    int find_start_city(const vector<int> &gas, const vector<int> &dist);
};

#endif // DISCRETE_H
