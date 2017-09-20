#include "primitive.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <stdexcept>
#include <bitset>
#include <stdexcept>
#include <iterator>
#include <set>

Primitive::Primitive()
{
}

void Primitive::printlastKlines(ifstream &ifs, int k) {
    vector<string> buff(k);
    string line;
    int i=0;
    for (; ifs>>line; i++) {
        buff[i%k]=line;
    }
    if (i<k) throw invalid_argument("File is small");
    int start= max((i-k)%k , 0);
    int count = min(i, k);

    for (int j=start; j<start+count; j++)
        cout << buff[j%k] << endl;
}

//static int findMissingIn4BillInts(int num, ifstream & istr) {
//    bitset<(1<<29)> table; // only valid for bitset<29 or less>
//    int buf;
//    while (istr>>buf) {
//        table.set(buf);
//    }
//    istr.close();

//    for (int i=0; i<table.size(); i++)
//            if (table.test(i)!= 0)
//                return i;
//    return -1;
//}

int Primitive::findMissingIn4BillInts10MBmemo(int num, ifstream & istr) {
    // divide block and count, then bit search
    // 4B=2^32 int, 10MB=2^23byte=2^21 int,
    // blockSize>2^32/2^21=2^11, choose 2^12
    // blockNum = 2^32/2^12 = 2^20
    // for less memory: 2^16 int (4byte) = 2^18 = 1k*2^8=256k
    int blockNum=1<<20; // 2^20
    int blockSize = 1<<12; // 2^32/2^20=2^12
//    int byteSize = bitSize / 8;
    vector<int> blocks(blockNum, 0);
//    vector<char> byteChunk(byteSize, 0);
    int buf;
    while(istr>> buf) {
        blocks[buf/blockSize]++;
    }

    int start=-1;
    for (int i=0;i<blockNum; i++) {
        if (blocks[i]<blockSize) {
            start=i*blockSize;
            break;
        }
    }

    if (start==-1) throw invalid_argument("there is no missing number");

    istr.clear();
    istr.seekg(0, ios::beg);
    blocks.clear();
    vector<char> bitVect(blockSize/8, 0);
    while (istr>>buf) {
        if (buf>=start && buf< start+blockSize) {
            int x=buf-start;
            bitVect[x/8] |= x%8;
        }
    }
    for ( int i=0; i<bitVect.size(); i++)
        for ( int j=0; j<8; j++) {
            if (bitVect[i] && (1<<j) ==0)
                return start+i*8+j;
        }
    return -1;
}

int Primitive::findMissingIn4BillInts1GBmemo(int num, ifstream & istr) {
    // 4Billon = 2^32 int
    // 1GB = 2^30 Byte = 2^30*8bit = 2^33 bit
    vector<char> table(num/8, 0);
    int buf;
    while (istr>>buf) {
        table[buf/8] |= 1<<(buf%8);
    }
    istr.close();

    for (int i=0; i<table.size(); i++)
        for (int j=0; j<8; j++) {
            if (table[i] & (1<<j) == 0)
                return i*8+j;
        }
    return -1;
}

bool Primitive::parity(unsigned long long x)
{
    int num=0;
    while (x)
    {
        x &= x-1;
        num ^= 1;
    }

    if (num&1) return true;
    else
        return false;
}

short Primitive::parity_best(unsigned long long x) {
    x ^= x>>32;
    x ^= x>>16;
    x ^= x>>8;
    x ^= x>>4;
    x ^= x>>2;
    x ^= x>>1;
    return x&1;
}

static void print64Bits(long long x)
{
    for (int i=63; i>=0; i--)
    {
        cout << (x>>i & 1) ;
    }
    cout << endl;

}

unsigned long long Primitive::swap_bits(unsigned long long x, int i, int j)
{
//    cout << x << " " << i << " " << j << endl;
    unsigned long long y=x;
    if ((x>>i &1) != (x>>j & 1))
    {
//        cout << "swap" << " " << i << " " << j << " " << (x>>i &1) << " " << (x>>j &1) << endl;
        unsigned long long mask=(1LL<<i | 1LL<<j);
//        print64Bits(y);
//        print64Bits(mask);
        y ^= mask;
//        print64Bits(y);
    }
    return y;
}

unsigned long long Primitive::reverse_bits(unsigned long long x)
{
    print64Bits(x);
    unsigned long long y=x;
    int low=0, high=63;
    while (low < high)
    {
//        cout << low << " " << high << endl;
        y=swap_bits(y, low, high);
        low++;
        high--;
    }
    print64Bits(y);
    return y;
}

unsigned long long Primitive::closest_int_same_bits(unsigned long long x)
{
    print64Bits(x);
    for (int i=0; i<63; i++)
    {
        if (((x>>i)&1) ^ (x>>(i+1) & 1))
        {
            unsigned long long mask = (1LL << i) | (1LL << (i+1));
            x ^= mask;
            print64Bits(x);
            return x;
        }
    }
    throw string("invalide input");
}

void Primitive::print_power_set(const vector<int> &S, int i, vector<int> & oneset)
{
    if (S.empty()) return;
    if (i==S.size())
    {
        if (!oneset.empty())
        {
        for (int k=0; k<oneset.size(); k++)
            cout << oneset[k] << " ";
        cout << endl;
        }
        return;

    }
        oneset.push_back(S[i]);
        print_power_set(S, i+1, oneset);
        oneset.pop_back();
        print_power_set(S, i+1, oneset);
}

void Primitive::print_power_set_k_recursive(const vector<int> &S, int i, int k, vector<int> &oneset) {
    if (S.empty()) return;
    if (i==S.size()) {
        if (oneset.size()==k) {
            copy(oneset.begin(), oneset.end(), ostream_iterator<int>(cout, ","));
            cout << endl;
        }
        return;
    }
    oneset.push_back(S[i]);
    print_power_set_k_recursive(S, i+1, k, oneset);;
    oneset.pop_back();
    print_power_set_k_recursive(S, i+1, k, oneset);
}

void Primitive::print_power_set_2(const vector<int> &S) {
    if (S.empty())
        return;
    vector<vector<int> > table;//(1, vector<int>(1, S[0]));
    table.emplace_back(vector<int>(1,S[0]));
    cout << table[0][0] << endl;
    for (int i=1; i<S.size(); i++) {
        for (auto &t: table)
            t.emplace_back(S[i]);
        table.emplace_back(vector<int>(1, S[i]));

        for (auto &t: table) {
            copy(t.begin(), t.end(), ostream_iterator<int>(cout, ","));
            cout << endl;
        }
    }

}

void Primitive::print_power_set_better(const vector<int> &S) {
    for (int i=0; i<(1<<S.size()); i++) {
        int x = i;
        while (x) {
            int y = x & ~(x-1);
            int k = log2(y);
            cout << S[k] << ",";
            x &= x-1;
        }
        cout << endl;
    }

}

string Primitive::intToString(int x) {
    if (x==0)
        return "0";
    bool isNegative=false;
    if (x<0)  {
        isNegative=true;
        x=-x;
    }
    stringstream s;
    while (x) {
        s<<(x%10);
        x /=10;
    }
    string str = s.str();
    if (isNegative)
        str.push_back('-');
    reverse(str.begin(), str.end());
    return str;
}

int Primitive::stringToInt(string s) {
    if (s.empty())
        throw invalid_argument("empty string");
    int i;
    for ( i=0; i<s.size(); i++) {
        if (s[i]!=' ')
            break;
    }
    s=s.substr(i);
    bool isNegative=false;
    if (s[0]=='-')
        isNegative=true;
    int x=0;
    for (int i=isNegative; i<s.size(); i++) {
        if (!isdigit(s[i]))
            throw invalid_argument("not digit");
        x=x*10+s[i]-'0';
    }
    return isNegative?-x : x;
}

static bool isDigit(char x)
{
    return x>='0' && x <= '9';
}

static bool isValid(char x, int base)
{
    cout << int(x) << endl;
    if (base <= 10)
        return (x>='0' && x < '0'+ base);
    else
        return (x>='0' && x <= '9') || (x>='A' && (x<'A'+char (base-10))) ;
}

/* note: 1. check s="0", check invalid bit, check negative,
 */
string Primitive::convert_base(const string &s, int b1, int b2)
{
    cout << s << " " << b1 << " " << b2 << endl;
    if (s[0]=='0') return string("0");

    int num=0;
    bool negative= false;
    int i=0;
    if (s[i]=='-')
    {
        negative=true;
        i++;
    }

    for (int k=i; k<s.size(); k++)
    {
        if (isValid(s[k], b1))
        {
            if (isDigit(s[k]))
                num=num*b1+(s[k]-'0');
            else
                num=num*b1+10+(s[k]-'A');
            cout << "num=" << num << endl;
        }
        else
            throw string("invalid input");
    }

    string result;
    while (num)
    {
        int x=num % b2;
        result.push_back(x<=10? char (x+'0'): char(x-10+'A'));
        num = num / b2;
    }

    if (negative) result.push_back('-');
    std::reverse(result.begin(), result.end());

    return result;

}

static string convert_bit_str(unsigned int x)
{
    if (x==0) return string("0");
    string result;
    while (x)
    {
        cout << x << endl;
        if (x&1) result.push_back('1');
        else result.push_back('0');
        x>>=1;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// A should not contain 0 or negative
string Primitive::encode_ints_to_string(const vector<unsigned int> &A)
{
    if (A.empty()) return string();

    string result;
    for (int i=0; i<A.size(); i++)
    {
        // convert to bits
        string s=convert_bit_str(A[i]);

        // add the length
        string len(s.size(), '0');

        string ss = len+s;
        result.insert(result.end(), ss.begin(), ss.end());
    }
    return result;

}

vector<unsigned int> Primitive::decode_string_to_ints(const string &s)
{
    vector<unsigned int> result;
    if (s.empty()) return result;

    int i=0;
    while (i<s.size())
    {
        // get the length
        int len=0;  // forget =0
        while (s[i]=='0' && i<s.size())
        {
            len++;
            i++;
        }
        unsigned int x=0;
        int k=i;
        while (k<i+len && k<s.size())
        {
            x = (x<<1) + s[k]-'0';
            k++;
        }
        i=k;
        result.push_back(x);
    }

    return result;
}

int Primitive::GCD(int x, int y)
{
    if (min(x,y)==0) return max(x, y);
    else if (x&1==0 && y&1==0)
        return GCD(x>>1, y>>1) <<1;
    else if (x&1==0 && y&1 !=0)
        return GCD(x>>1, y);
    else if (x&1 !=0 && y&1==0)
        return GCD(x, y>>1);
    else
        return GCD(min(x, y), abs(x-y));

}

bool Primitive::is_prime(int x)
{
    if (x<2) return false;
    if (x==2 || x==3) return true;
    if (x%2==0 || x%3==0) return false;

    int maxDivisor= sqrt(x);
    for (int i=5; i<=maxDivisor; i+=6)
    {
        if (x%i==0 || x%(i+2)==0) return false; // exclude x%(i+4) because (5+(1+3)+6*n+)%3 ==0
    }
    return true;
}

vector<int> Primitive::generate_primes_from_1_n(int n)
{
    vector<int> result;
    if (n==1) return result;
    result.push_back(2);
    if (n==2) return result;
    for (int i=3; i<=n; i+=2)
    {
        if (is_prime(i))
            result.push_back(i);
    }
    return result;
}

// I don't
vector<int> Primitive::generate_primes_efficient(int n)
{
    if (n<=1)throw std::invalid_argument("invalid input");
    if (n==2) return vector<int>(1,2);

    int num=floor((n-3)/2)+1;
    vector<int> primes;
    primes.push_back(2);
    vector<bool> is_prime_vect(num, true);

    for (int i=0; i<num; i++)
    {
        if (is_prime_vect[i]) {
            int p = (i<<1)+3;
            primes.push_back(p);
            for (int j=p*p; j<num; j+=2*p)
                is_prime_vect[j]=false;
        }
    }
    primes;
}

vector<int> Primitive::generate_primes_sieveofEratosthenes(int n) {
    if (n<2) throw invalid_argument("invalid input");
    vector<bool> is_prime(n+1, true);
    vector<int> ret;
    ret.push_back(2);
    for (int i=3; i<=n; i+=2) {
        if (is_prime[i]) {
            ret.push_back(i);
            for (int j=i*i; j<=n; j+=i) {
                is_prime[j]=false;
            }
        }
    }
    return ret;
}

struct ComplexComp {
    bool operator()(const complex<double> &a, const complex<double> &b) const {
        return abs(a) != abs(b) ?
                    abs(a) < abs(b) : a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
    }
};

static bool is_unit(complex<double> &a) {
    return a==complex<double>(1, 0) || a==complex<double>(-1, 0) || a== complex<double>(0, 1)
            || a == complex<double>(0, -1);
}

vector<complex<int> > Primitive::generate_gaussian_primes(int n) {
    set<complex<double>, ComplexComp> candidates;
    vector<complex<int> > ret;

    for (int i=-n; i<=n; i++)
        for (int j=-n; j<=n; j++) {
            complex<double> x(i, j);
            if (!is_unit(x) && abs(x) != 0 && norm(x) < 2*pow(n, 2))
                candidates.insert(x);
        }

    while (!candidates.empty()) {
        auto p = *(candidates.begin());
        candidates.erase(candidates.begin());
        ret.push_back(p);
        int max_multiplier = ceil(sqrt(2) * n / abs(p));

        for (int i=-max_multiplier; i<=max_multiplier; i++)
            for (int j=-max_multiplier; j<=max_multiplier; j++) {
                complex<double> t(i, j);
                if (!is_unit(t) && abs(t) != 0 && norm(t*p) < 2*pow(n, 2))
                    candidates.erase(t*p);
            }
    }
    return ret;
}

Primitive::Rectangle Primitive::intersect_rectangle(const Rectangle &R, const Rectangle &S)
{
    if (R.x<=S.x+S.width && S.x <= R.x+R.width && R.y <= S.y+S.width && S.y <= R.y+R.height)
    {
        return Rectangle(max(S.x, R.x), max(S.y, R.y), min(S.x+S.width, R.x+R.width)-max(S.x, R.x),
                         min(S.y+S.height, R.y+R.height)-max(S.y, R.y));
    }
    else
        return Rectangle(0,0,-1,-1);
}

bool Primitive::isRectangle(vector<Point> &vertices)
{
    if (vertices.size()!=4) return false;
    sort(vertices.begin(), vertices.end(), Point::compareX);
    if (vertices[0].x != vertices[1].x || vertices[2].x != vertices[3].x)
        return false;
    sort(vertices.begin(), vertices.end(), Point::compareY);
    if (vertices[0].y != vertices[1].y || vertices[2].y != vertices[3].y)
        return false;
    return true;

}

bool Primitive::pointIntersect(const Point &p, const pair<int,int> &xRange, const pair<int, int> &yRange) {
    return p.x >= xRange.first && p.x <= xRange.second && p.y >= yRange.first && p.y<= yRange.second;
}

bool Primitive::RectanglesIntersect_noxyalign(vector<Point> &r1, vector<Point> &r2)
{
    sort(r1.begin(), r1.end(), Point::compareX);
    pair<int, int> xRange(pair<int, int>(r1[0].x, r1[3].x));
    sort(r1.begin(), r1.end(), Point::compareY);
    pair<int,int> yRange(pair<int, int>(r1[0].y, r1[3].y));

    for (int i=0; i<4; i++)
    {
        if (pointIntersect(r2[i], xRange, yRange))
            return true;
    }

    return false;
}

int Primitive::divided_x_y(int x, int y)
{
    if (y==0) throw string("Error:divisor is zero");
    if (x==0) return 0;
    if (x<y) return 0;

    return 1+divided_x_y(x-y, y);

}

int Primitive::divided_x_y_efficient(int x, int y)
{
    if (y==0) throw string("Error:divisor is zero");
    if (x==0) return 0;

    if (x<y) return 0;

    int power=0;
    while (x>=(y<<power))
        power++;

    return (1<<(power-1)) | divided_x_y_efficient(x-(y<<(power-1)), y);
//    return (1<<(power-1)) + divided_x_y_efficient(x-(y<<(power-1)), y);
}

unsigned Primitive::add_no_operator(unsigned x, unsigned carry)
{
    if (carry==0) return x;
    if (x==0) return carry;

    int y=x^carry;
    int carry1=((x&carry)<<1);
    return add_no_operator(y, carry1);

}

unsigned Primitive::multiply_no_operator(unsigned x, unsigned y)
{
    if (!x || !y) return 0;

    int sum=0;
    while (x)
    {
        if (x&1)
            sum=add_no_operator(sum, y);
        x>>=1;
        y<<=1;
    }
    return sum;

}

/**
 * @brief Primitive::sqrt_no_operator
 * theory: f(x)=x^2-y=0 the tangent line at a guess x0 is y=f'(x0)(x-x0)+f(x0), and x-intercept is 0=f'(x0)(x-x0)+f(x0)
 * So x=x0-f(x0)/f'(x0).
 * For sqrt, x=x0-(x0*x0-y)/(2*x0);
 * @param x
 * @return
 */
double Primitive::sqrt_no_operator(double y)
{
    double x0;
    for (x0=1; x0<y/2; x0++)
    {
        if (x0*x0==y) return x0;
        if (x0*x0>y) break;
    }

    double error=1;
    double x=x0;
    int iternum=0;
    while (error > 0.000001 && iternum<50)
    {
        x=x0-(x0*x0-y)/(2*x0);
        error=fabs(x*x-y);
        iternum++;
        x0=x;

    }
    return x;

}

double Primitive::sqrt_binary_search(double x, double errCriterion, int numIteration)
{
   double small=0, large=x;
   double error=x;
   int num=0;
   double middle;
   while (error>errCriterion && num<numIteration) {
       middle=(small+large)/2; // small + ((large-small)>>2);
       if (middle*middle>x)
           large=middle;
       else if (middle*middle<x)
               small=middle;
       else
            return middle;
   }
   return middle;
}

