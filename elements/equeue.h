#ifndef EQUEUE_H
#define EQUEUE_H

#include <sstream>
#include <vector>

using namespace std;

class Star
{
    int ID;
    int x, y, z;

public:
    Star(int _id, int _x, int _y, int _z) : ID(_id), x(_x), y(_y), z(_z)
    {
        distance=x*x+y*y+z*z;
    }
    bool operator<(const Star &h) const
    {
        return distance < h.distance;
    }
    int distance;
};

class Equeue
{
public:
    Equeue();

    void find_closest_k_stars(stringstream &ss, int k);
};

#endif // EQUEUE_H
