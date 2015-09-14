#ifndef BITS_H
#define BITS_H

#include <string>
#include <iostream>

using namespace std;

class Bits
{
public:
//    Bits();

    void printTest(){cout << "Test null object" << endl;}
    static void insert(int &N, int &M, const int i, const int j);
    static void insert2(int &N, int &M, const int i, const int j);
    static string convertDecimalToBinary(const double x);

    static string printBit(int x);

    static int addTwoNum(int x, int y);
};

#endif // BITS_H
