#include "bits.h"
#include <sstream>
#include <iostream>

using namespace std;

Bits::Bits()
{
}

int Bits::mergeTwoNumbers(int N, int M, int i, int j)
{
    // test: N=10100011(128+32+3), M=00001011(8+3)
    // check inputs: j must be larger or equal i
    if (i > j)
    {
        int temp = i;
        i=j;
        j=temp;
    }

    // create a mask to clear Bit i to j in N: test: i=2, j=5
    int x1 = ~0 << (j+1);  // 11000000
    int x2 = (1 << i) -1;  // 00000011
    int mask = x1 | x2;   //  11000011
    N &= mask;            //  10000011

    // shift M by i
    M = M << i;           //  00101100

    //merge
    return N | M;         //  10101111 (128+32+15=)

}

std::string Bits::printBinary(double x)
{
    // check inputs
    if (x>1 || x <0)
    {
        return "ERROR";
    }

    // loop for each bit
    std::stringstream str;
    str << '.';
//    std::cout << str.str().length() << " at the begin" << std::endl;
    while (x>0)
    {
        if (str.str().length()>32)
        {
            std::cout << str.str().length() << ":" << str.str() << std::endl;
            return "ERROR";
        }

        // shift 1 bit and check
//        cout << x << endl;
        x = x * 2;
        if (x>=1)
        {
            str << "1";
            x=x-1;
        }
        else
            str << "0";

    }
    return str.str();
}

static int bitSwapRequired(int a, int b)
{
    int count =0;
//    for (int c = a^b; c != 0; c = c>>1)
//        count += c & 1;

    for (int c=a^b; c != 0; c=c&(c-1))
        count++;

//    int c=a^b;
//    while (c != 0)
//    {
//        c=c>>1;
//        count += c & 1;
//    }

    return count;
}

static int swapOddEvenBits(int x)
{
    return ((x & 0xaaaaaaaa)>>1) | ((x & 0x55555555) <<1);
}
