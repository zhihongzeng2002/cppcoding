#ifndef RECURSION_H
#define RECURSION_H

#include <map>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <iostream>

using namespace std;

enum Direction
{
    LEFT, RIGHT, UP, DOWN, UNDECIDED
};

struct Position
{
    int x, y;
    Position(int _x, int _y):x(_x), y(_y)
    {}
    bool isConflict(vector<Position> & solution)
    {
        for (int i=0; i<solution.size(); i++)
        {
            if (x==solution[i].x || y==solution[i].y || x-solution[i].x==y-solution[i].y || x-solution[i].x==solution[i].y-y)
                return true;
        }
        return false;
    }
    Position & operator=(const Position & p1)
    {
        if (this==&p1) return *this;

        x=p1.x;
        y=p1.y;
        return *this;
    }
};

struct circusPerson
{
    int size, height, weight;
    circusPerson():size(0), height(0), weight(0) {}
    circusPerson(int _size, int _height, int _weight): size(_size), height(_height), weight(_weight) {}
    bool canBeAbove(circusPerson & another)
    {
        if (another.size==0) return true;
        return size<another.size && height<another.height && weight < another.weight;
    }
    static bool PersonComparator(circusPerson a, circusPerson b)
    {
        return a.size < b.size;
    }
    bool operator <(const circusPerson&x) const
    {
        return size<x.size;
    }
    void print()
    {
        cout << size << "," << height << "," << weight << endl;
    }
};

enum Color
{
    RED, GREEN, BLUE
};

class Recursion
{
public:
    Recursion(){}

    void paintFill(vector<vector<Color> > &screen, Position p, Color newColor);
    void paintFill(vector<vector<Color> > &screen, Position p, Color oldColor, Color newColor);
    int combinationOfCoins(int n, int index, vector<int> & comb);
    void HanoiTower(const int numPlate);
    void testBuildTower(int argc, char **argv);
    vector<circusPerson> getTallestCircusTower_exhaustive(vector<circusPerson> &team);
    vector<circusPerson> getTallestCircusTower_greedy(vector<circusPerson> &team);
    vector<vector<Position> > getQueenPosition();
    set<string> getAllParentheses(int n);
    void getPermutation(string & str, int index, vector<string> & results);
    vector<vector<int> > getSubSet(vector<int> &arr, int index);
    void print2DPath(vector<vector<int> > &board, int y, int x, int y_start, int x_start);
    int countWaysofStair(int numStair, map<int, int> &table);
    int count2DBoardPathes(vector<vector<int> > &board, int y, int x, map<pair<int,int>, int> &table);
    bool find2DBoardPathesStartEndWith4Direction(vector<vector<int> > &board, int y, int x, int y_start, int x_start);
//    int count2DBoardPathesStartEndWith4Direction(vector<vector<int> > &board, int y, int x, int y_start, int x_start, map<pair<int,int>, int> &table);
};

#endif // RECURSION_H
