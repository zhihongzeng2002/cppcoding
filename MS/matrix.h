#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

//enum Direction2D
//{
//    UP,DOWN, LEFT, RIGHT, UNDECIDED
//};

struct Point2D
{
    int x, y;
    Point2D(int _x, int _y)
    : x(_x), y(_y)
    {}

    bool isAvailable(vector<vector<int> > & arr)
    {
        if (y<0 || y>=arr.size() || x<0 || x>=arr[0].size())
            return false;
        if (arr[y][x]!=0)
            return false;
        else
            return true;
    }
};

class Matrix
{
public:
    Matrix();

    int findMaxRectSum(vector<vector<int> > &arr2D);

    int findMaxSquareWithBlackBolder(vector<vector<int> > &arr2D);

    void rotateMatrix(vector<vector<int> > &arr);

    void findPathBetweenPoints(vector<vector<int> > & arr, Point2D start, Point2D end);
};

#endif // MATRIX_H
