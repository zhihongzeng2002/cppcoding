#ifndef LEVEL_H
#define LEVEL_H

#include <list>

#include "vehicle.h"

class Level
{
public:
    Level(const int _numLots): numLots(_numLots){}

    ///add vehicle to the level, return true if success, otherwise false;
    bool addVehicle(const Vehicle x)
    {
        if (vehicleList.size()<numLots)
        {
            vehicleList.push_back(x);
            return true;
        }
        else
            return false;
    }

    // remove a car if the car's remaintime is 0. each time only at most one car is removed
    Vehicle removeVehicle()
    {
        Vehicle remVehicle;
        if (vehicleList.empty()) return remVehicle;

        for (std::list<Vehicle>::iterator itr=vehicleList.begin(); itr != vehicleList.end(); itr++)
        {
            Vehicle x = *itr;
            if (!x.getRemainTime())
            {
                remVehicle = x;
                vehicleList.erase(itr);
                return remVehicle;
            }
        }
        return remVehicle;
    }

private:
    int ID;
    int numLots;
    std::list<Vehicle> vehicleList;
};

#endif // LEVEL_H
