#ifndef ARRAYSTRING_H
#define ARRAYSTRING_H

#include <vector>
#include <string>

using namespace std;

class ArrayString
{
public:
    ArrayString();

    void dutch_flag_partition(vector<int> &A, int i);
    // from MS interviw
    bool isChineseSequence(const vector<char> &A);
    //6.21
    void replace_remove(string &s);
    void rotate2DArray_recursive(vector<vector<int> > &A);
    void rotate2DArray(vector<vector<int> > & A);
    void printMatrixInSpiralOrder(vector<vector<int> > &arr);

    int subStringSearch_Rabin_Karp(string & t, string &s);
    pair<int,int> sub2DSquareSearch_Rabin_Karp(vector<vector<int> > & t, vector<vector<int> > &s);

    string deleteBreplaceA(string s);

    void convertPhoneNumberToString(string &num, string &s, vector<string> &result);

    // actually it should be regex search becase it is to find matched subarray
    bool regexMatch(string &r, string &s);

    int maxProfitKBuySell(const vector<int> & price, int k);
    int maxProfit2BuySell(const vector<int> & price);
    int maxProfitUnlimitBuySell(const vector<int> & price);

    vector<int> find_0_mod_sum_subset(const vector<int> &A);

    pair<int, int> find_longest_increase_subarray(const vector<int> &A); // O(n)
    pair<int, int> find_longest_increase_subarray_efficient(const vector<int> &A); // best case O(max(L, n/L0)). L longest inc subarray

    // problem 6.7
    vector<int> compute_equivalence_classes(int n, const vector<int> &A, const vector<int> &B);

    void apply_permutation( vector<int> &A,  vector<int> &perm);

    // 6.9
    class BigInteger {
    private: // public:???
        int sign; //1 or -1
        vector<int> digit;

    public:
        BigInteger(int capacity): sign(1), digit(capacity, 0) {}
        BigInteger(const string & x) : sign(x.front()=='-'? -1 : 1), digit(x.size()-(x.front()=='-')) {
            for (int i= x.front()=='-', j=digit.size()-1; i<x.size(); i++, j--)
                digit[j]=x[i]-'0';
        }

        // part of code can be used for product of two link-representing integers
        // 1: compute the sign; 2: reverse the link list or convert the link lists into vectors;
        // 3. two while loop with carry, save the result in array (for access convenience)
        BigInteger operator * (const BigInteger & y) const {
            BigInteger res(digit.size()+y.digit.size());
            res.sign = sign * y.sign;

            for (int i=0; i<digit.size(); i++) {
                if (digit[i]) {
                    int carry=0;
                    for (int j=0; j<y.digit.size() || carry; j++) {
                        res.digit[i+j] = res.digit[i+j] + carry + j<y.digit.size() ? digit[i] * y.digit[j] :0;
                        carry = res.digit[i+j]/10;
                        res.digit[i+j] %= 10;
                    }
                }
            }

            if ((digit.size()==1 && digit.front()==0) || (y.digit.size()==1 && y.digit.front()==0))
            {
                res.sign=-1;
                res.digit.resize(1);
            } else {
                res.digit.resize(digit.size()+y.digit.size()-1);
            }
            return res;
        }
    };

    class RotateMatrix {
        vector<vector<int> > A;

    public:
        RotateMatrix(vector<vector<int> > & arr) : A(arr) {}

        int read(int y, int x) {
            return A[A.size()-1-x][y];
        }

        void wrtite(int y, int x, int v) {
            A[A.size()-1-x][y]=v;
        }
        size_t Size() {
            return A.size();
        }
    };
};

#endif // ARRAYSTRING_H
