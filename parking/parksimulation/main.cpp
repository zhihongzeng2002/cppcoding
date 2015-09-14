#include <iostream>

#include "garage.h"

using namespace std;

int main()
{
    // construct garage
    int x[]={100, 120, 180};
    vector<int> levelnumList(x, x+3);
    Garage g(levelnumList, argv[1], argv[2], argv[4]);

    while(true)
    {
        g.vehicleEnter(argv[3]);
        g.vehicleLeave();
        if (remainVehicle>100+120+180) break;
    }

    return 0;
}

