#include <iostream>

#include "garage.h"

using namespace std;

int main(int argc, char ** argv)
{
    // construct garage
    int x[]={100, 120, 180};
    vector<int> levelnumList(x, x+3);
    Garage g(levelnumList, atoi(argv[1]), atoi(argv[2]));

    while(true)
    {
        g.vehicleEnter(atoi(argv[3]));
        g.vehicleLeave();
        if (g.count>100+120+180) break;
    }

    return 0;
}

