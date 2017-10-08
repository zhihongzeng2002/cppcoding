#ifndef TIMELINE_H
#define TIMELINE_H

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class TimeLine
{
    // array of rush time slots. It is empty at initial
    vector<pair<float, float> > rush_intervals;

public:
    TimeLine(){}
    void AddTimeSpan(float start_time, float end_time);
    bool IsRuchHour(float time);

};

#endif // TIMELINE_H
