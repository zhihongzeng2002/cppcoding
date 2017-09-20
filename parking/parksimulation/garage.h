#ifndef GARAGE_H
#define GARAGE_H

#include <vector>
#include <time.h>
#include <stdlib.h>

#include "level.h"
#include "vehicle.h"

class Garage
{
public:
    int count;
    Garage(std::vector<int> & levelNumList, int _minTime, int _maxTime):
        minTime(_minTime), maxTime(_maxTime)
    {
        count = 0;
        for (std::vector<int>::iterator itr=levelNumList.begin(); itr!=levelNumList.end(); itr++)
        {
            Level x(*itr);
            levelList.push_back(x);
        }
        srand(time(NULL));
    }

    void vehicleEnter(const int numVehicle=3)
    {
        for (int i=0; i< numVehicle; i++)
        {
            int remainTime = minTime + rand()%(maxTime-minTime);
            Vehicle x(count, Status_SEARCH, remainTime);
            Level y = levelList.front();
            y.addVehicle(x);
            count++;
        }
    }

    void vehicleLeave()
    {
        Level y = levelList.front();
        Vehicle x = y.removeVehicle();
//        if (x.getID() != -1)
//            delete x;
    }

private:
    std::vector<Level> levelList;
    int minTime, maxTime;
};

#endif // GARAGE_H
