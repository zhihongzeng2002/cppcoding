#ifndef VEHICLE_H
#define VEHICLE_H

enum Status
{
    Status_SEARCH,
    Status_LEAVE,
    Status_STAY
};

class Vehicle
{
public:
    Vehicle():ID(-1) {}
    Vehicle(const int _ID, const Status _status, const int _remainTime):
        ID(_ID), status(_status), remainTime(_remainTime) {}
    int getID() const {return ID;}
    Status getStatus() const {return status; }
    void changeStatus(const _status) { status = _status; }
    int getRemainTime()
    {
        if (remainTime) remainTime--;
        return remainTime;
    }

private:
    int ID;
    Status status;
    int remainTime;
};

#endif // VEHICLE_H
