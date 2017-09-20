#ifndef PROB_H
#define PROB_H

#include <vector>
#include <sstream>

using namespace std;

class Prob
{
public:
    Prob();

    double house_majority(const vector<double> & repubProbs);

    // problem 2.2: off-sampling subset of size k
    vector<int> off_sampling(vector<int> A, int k);
    // problem 2.7
    vector<int> online_sampling(int n, int k);

    // problem 2.4: generate random integer between [a, b]
    int generateRandomInt_in_a_b(int a, int b);

    // problem 2.5:
    double nonuniform_random_generation(vector<double> &arr, vector<double> &prob);

    // problem 2.6
    vector<int> reservoir_sampling(istringstream &s, int k);

    // crack problem 17.11
    int rand7Fromrand5();

};

#endif // PROB_H
