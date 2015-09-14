#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <string>
#include <vector>
#include <fstream>
#include <complex>

using namespace std;

class Primitive
{
public:
    Primitive();

    void printlastKlines(ifstream & ifs, int k);
    int findMissingIn4BillInts1GBmemo(int num, ifstream & istr);
    int findMissingIn4BillInts10MBmemo(int num, ifstream & istr);

    /// compute the parity of a large number of 64-bit nonnegative integers (the number of 1s is odd, return true, otherwise false)
    // long = int (32bit), long long = 64bit
    bool parity(unsigned long long x);
    short parity_best(unsigned long long x);

    /// swaps the bits of indices i and j of a 64-bit integer x
    unsigned long long swap_bits(unsigned long long x, int i, int j);

    /// take a 64-bit integer x and returns a 64-bits integer consisting of bits of x in reverse order
    unsigned long long reverse_bits(unsigned long long x);

    /// suppose x is belong to Sk (set whose weight (number of 1 bits) is k), and k is not 0 or 64. How would you compute y which belong to Sk
    /// such that |y-x| is minimum.
    unsigned long long closest_int_same_bits(unsigned long long x);

    /// print the power (combination) of a set S. Print the subsets one line, with elements separated by commas.
    void print_power_set(const vector<int> & S, int i, vector<int> & oneset);
    void print_power_set_2(const vector<int> & S);
    void print_power_set_k_recursive(const vector<int> &S, int i, int k, vector<int> &oneset);
    void print_power_set_better(const vector<int> &S);

    string intToString(int x);
    int stringToInt(string s);
    /// base conversion
    string convert_base(const string& s, int b1, int b2);

    /// convert Excel column ids to the corresponding integer, with "A" corresponding to 1
//    int decodeExcelColID(const string & col){};

    /// encode function to return a string representing the concatenation of Elias gamma codes (bits) for int array,
    /// decode function to return the array that was passed to the encode function
    string encode_ints_to_string(const vector<unsigned int> & A);
    vector<unsigned int> decode_string_to_ints(const string & s);

    /// compute GCD(greatest common divisor) of two ints without using multiplication, divsion or modulus operators
    int GCD(int x, int y);

    /// return all the primes between 1 and n
    vector<int> generate_primes_from_1_n(int n);
    bool is_prime(int x);
    vector<int> generate_primes_efficient(int n);

    //14.18
    vector<complex<int> > generate_gaussian_primes(int n);

    /// R and S are xy-aligned rectangles. test if R and S have nonempty intersection. If yes, return the intersection rect
    struct Rectangle
    {
        int x, y, width, height;
        Rectangle(int _x, int _y, int _width, int _height): x(_x), y(_y), width(_width), height(_height){}
    };
    Rectangle intersect_rectangle(const Rectangle &R, const Rectangle &S);
    struct Point
    {
        int x, y;
        static bool compareX(Point t, Point other)
        {
            return t.x<other.x;
        }
        static bool compareY(Point t, Point other)
        {
            return t.y<other.y;
        }
    };

    bool isRectangle(vector<Point> & vertices);
    bool RectanglesIntersect_noxyalign(vector<Point> & r1, vector<Point> & r2);
    bool pointIntersect(const Point &p, const pair<int,int> &xRange, const pair<int, int> &yRange);

    /// multiply two unsigned positive integers using >>, <<, |, &, ~, ^, without increment and decrement)
    unsigned multiply_no_operator(unsigned x, unsigned y);
    unsigned add_no_operator(unsigned x, unsigned y);

    /// compute x/y using only addition, subtraction and shifting
    int divided_x_y(int x, int y);
    int divided_x_y_efficient(int x, int y);

    /// implement sqrt(x)
    double sqrt_no_operator(double x);
    double sqrt_binary_search(double x, double errCriterion, int numIteration);

    template<typename T, size_t N>
    class InitArray {
    private:
        T A[N];
        int P[N], S[N];
        int t=0;

        bool isValid(int i) {
            return P[i]>=0 && P[i]<t && S[P[i]]==i;
        }

    public:
        bool read(int i, T &v) {
            if (isValid(i)) {
                v=A[i];
                return true;
            }
            return false;
        }

        bool write(int i, T &v) {
            if (!isValid(i)) {
                S[t]=i;
                P[i]=t++;
            }
            A[i]=v;
        }

    };

};

#endif // PRIMITIVE_H
