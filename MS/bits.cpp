#include "bits.h"
#include <algorithm>
#include <iostream>
#include <bitset>
#include <sstream>

using namespace std;

int Bits::addTwoNum(int x, int carry)
{
    if (carry==0) return x;
    int z=x^carry;
    int high=(x&carry)<<1;
    return addTwoNum(z, high);
}

// x is positive
string Bits::convertDecimalToBinary(const double x)
{
    int intPart = int(x);
    double fraction = x-intPart;

    string result;
    // for integer part
    while (intPart>0)
    {
        string oneBit;
        int t = intPart % 2;
        if (t!=0) oneBit="1";
        else oneBit="0";
        result=oneBit + result;
        intPart = intPart/2;
    }

    // for fraction
    stringstream decimal;
    while (fraction!=0)
    {
        if (decimal.str().size()>32) return "Error";
        fraction = fraction * 2;
        if (fraction>=1)
        {
            decimal<<'1';
            fraction -=1;
        }
        else
        {
            decimal << '0';
        }
    }

    return result+'.'+decimal.str();

}

//Bits::Bits()
//{
//}

/** insert M to N from j to i bits
 * @param N the main string to insert
 * @param M the string which is inserted
 * @param i the end bit
 * @param j the start bit
 **/
void Bits::insert(int &N, int &M, const int i, const int j)
{
    if (i>j) return; // check inputs

    // set the mask: 1's throught bit j+1, then 0's
    int mask1 = ~((1<<(j+1)) -1);  // 1110000
    cout << bitset<16>(mask1) << endl;

    // set the mask: 0's through bit i-1, then 1's
    int mask2 = (1<<i) -1;  //0001111
    cout << bitset<16>(mask2) << endl;

    mask1 |= mask2; // mask: 0 between bit j to i
    cout << bitset<16>(mask1) << endl;

    N &= mask1; // 0's between between Bit i and j in N
    cout << bitset<16>(N) << endl;

    M = M << i; // move the M to Bit i and j
    cout << bitset<16>(M) << endl;

    N |= M;  // merge

}

string Bits::printBit(int x)
{
    stringstream num;
    for (int i=31; i>=0; i--)
    {
        if (x & 1<<i )
        num << 1;
        else
            num<< 0;
    }
    cout << bitset<32>(x) << endl;
//    while (x)
//    {
//        num.push_back((1&x)+'0');
//        x=x>>1;
//    }

//    if (num.empty())num.push_back('0');
//    else
//        reverse(num.begin(), num.end());

    return num.str();
}

void Bits::insert2(int &N, int &M, int low, int high)
{
    cout << bitset<16>(N) << endl;
    cout << bitset<16>(M) << endl;
    int mask = (1<<(high+1))-1;
    cout << bitset<16>(mask) << endl;
    int m2 = (1<< (low)) -1;
    cout << bitset<16>(m2) << endl;
    mask ^=m2;

//    for (int i=low; i<=high; i++)
//        mask |= 1<<i;
//    cout << bitset<16>(mask) << endl;
//    mask ^= (-1);
    mask = ~mask;
    cout << bitset<16>(mask) << endl;

    N &= mask;
    cout << bitset<16>(N) << endl;

    M = M <<low;
    cout << bitset<16>(M) << endl;

    N |= M;
    cout << bitset<16>(N) << endl;

}

string convertIntToString(int num)
{
    if (num==0) return "0";

    string result;
    while (num>0)
    {
        if (num & 1==1)
            result.push_back('1');
        else
            result.push_back('0');

        num>>1;
    }

    reverse(result.begin(), result.end());

    return result;
}

string convertFloatToString(double num)
{
    if (num==0) return string("0");

    string result;
    while (result.size()<32 && num != 0)
    {
        if (int(num*2)==1)
            result.push_back('1');
        else
            result.push_back('0');
        num = num*2-(int)num*2;
    }

    return result;
}

string convertDoubleToString(double num)
{
    bool negative=false;
    if (num<0)
    {
        negative=true;
        num = -num;
    }

    // get the integer part
    int intPart=num;
    string intString = convertIntToString(intPart);

    double doublePart=num-intPart;
    string doubleString=convertFloatToString(doublePart);

    if (negative)
        return "-"+ intString + "." + doubleString;
    else
        return intString+"."+doubleString;


}
