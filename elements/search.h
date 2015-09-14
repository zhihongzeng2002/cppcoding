#ifndef SEARCH_H
#define SEARCH_H

#include <vector>

using namespace std;

class Search
{
public:
    Search();

    // 11.4.1
    pair<int, int> findSubtractionPairInSortedArray(const vector<int> &A, int k);
    float sqrt_bySearch(float x);

//    http://stackoverflow.com/questions/12238241/find-local-minima-in-an-array
    //A[0]>A[1] and A[n-2]<A[n-1], not sorted array
//    Use a divide-and-conquer algorithm. Let m = n/2, and examine the value A[m] (that is, the element in the middle of the array).
//    Case 1: A[m−1] < A[m]. Then the left half of the array must contain a local minimum, so recurse on the left half. We can show this by contradiction: assume that A[i] is not a local minimum for each 0 ≤ i < m. Then A[m−1] is not a local minimum, which implies that A[m−2] < A[m−1]. Similarly, A[m −3] < A[m −2]. Continuing in this fashion, we obtain A[0] < A[1]. But then A[0] is a local minimum, contrary to our initial assumption.
//    Case 2: A[m + 1] > A[m]. Then the right half of the array must contain a local minimum, so recurse on the right half. This is symmetrical to Case 1.
//    Case 3: A[m − 1] > A[m] and A[m + 1] < A[m]. Then A[m] is a local minimum, so return it. The running time recurrence is T(n) = T(n/2) + Θ(1), which yields T(n) = Θ(log n).
    int findLocalMin(vector<int> & arr){}

    // same method as the above
    int findMaxinAscendDescendArray(vector<int> & arr){}

    // burget plan
    double computeUpperBoundForBurget(vector<double> &salaries, double burget);

    pair<int, int> find_pair_positivenegativeArray(const vector<int> & A, int k);

    int find_start_circular_sorted_array(const vector<int> &A);
//    int find_start_circular_sorted_array_duplicates(const vector<int> &A, int s, int e);

    int binary_search_unknown_len(const vector<int> &A, int k);

    double plan_for_budget(vector<double> &A, double budget);

    int find_kth_two_sorted_arrays(const vector<int> &A, const vector<int> &B, int k);

    double square_root(double x);
    double division(double x, double y);

    bool matrix_search(const vector<vector<int> > &A, int x);

    int find_kth_largest(vector<int> &A, int k);

    int find_kth_largest_sequence(istringstream &sin, int k);

    int find_missing_ipaddress(ifstream &sin);
    int find_missing_ipaddress_2(ifstream &sin);

    pair<int, int> find_missing_duplicate(const vector<int> &A);

    int find_missing_num_bits(vector<int> &A, int bitNum);

    int find_element_appear_once(const vector<int> &A);

    pair<int,int> search_covering_segment(const vector<string> & A, const vector<string> & Q);
    pair<int,int> search_sequence_covering_segment(const vector<string> & A, const vector<string> & Q);

    void drawLine(vector<char> & screen, int width, int y, int x1, int x2);
};

#endif // SEARCH_H
