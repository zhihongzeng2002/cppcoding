#include "timeline.h"
#include <algorithm>

///
/// \brief find_lower_bound
/// \param A:  array of rush hour intervals
/// \param time:  time is used to find likely overlapped rush hour interval.
/// \return : index of first element which could overlap the time
///
static int find_lower_bound(vector<pair<float, float> >&A, float time) {
    for (int i=0; i<A.size(); i++) {
        if (A[i].second>=time)
            return i;
    }
    return A.size();
}

///
/// \brief isOverlapped check whether two intervals have overlap
/// \param x rush hour slot
/// \param y rush hour slot
/// \return true if overlapped, otherwise false
///
static bool isOverlapped(pair<float, float> &x, pair<float, float> &y) {
    if ( x.second < y.first || y.second < x.first)
        return false;
    else
        return true;
}

///
/// \brief TimeLine::AddTimeSpan a rush hour interval to array rush hour intervals
/// \param start_time
/// \param end_time
///
void TimeLine::AddTimeSpan(float start_time, float end_time){
    if (start_time < 0 || start_time>=24 || end_time<0 || end_time>=24)
        throw invalid_argument("invalid input");

    if (end_time < start_time) {
        swap(start_time, end_time);
    }
    pair<float, float> slot(start_time, end_time);
    if (rush_intervals.empty()) {
        rush_intervals.push_back(slot);

        return;
    }

    // find the first element which is likely to overlap the slot.
    int idx = find_lower_bound(rush_intervals, start_time);
    if (idx == rush_intervals.size()) {
        // no element to overlap the slot. So add the slot at the end
        rush_intervals.push_back(slot);
    } else {
        // define a new array ans which is initialized with first no-overlapped elements
        vector<pair<float, float> > ans(rush_intervals.begin(), rush_intervals.begin()+idx);

        // traverse from the likely-overlapped element
        for (int i = idx; i < rush_intervals.size(); i++) {
            pair<float, float> x (rush_intervals[i]);
            if (isOverlapped(x, slot)){
                // if new rush hour interval is overlapped with the current element, stretch the rush hour interval to cover both
                slot.first = min<float>(x.first, slot.first);
                slot.second = max<float>(x.second, slot.second);
                // if the current element is the last in the array
                if (i==rush_intervals.size()-1)
                    ans.push_back(slot);
            } else {
                // if the new rush hour interval is not overlapped with current element
                ans.push_back(slot);
                ans.insert(ans.end(), rush_intervals.begin()+i, rush_intervals.end());
                break;
            }
        }
        // replace rush_intervals array with ans
        rush_intervals = ans;
    }
//    cout << rush_intervals.size() << endl;
}

///
/// \brief TimeLine::IsRuchHour check whether the time is in the rush hours
/// \param time
/// \return true if the time is in the rush hours, otherwise false
///
bool TimeLine::IsRuchHour(float time) {
    if (time<0 || time >=24)
        throw invalid_argument("invalid input");

    // find the fist element which is likely to cover the time
    int idx = find_lower_bound(rush_intervals, time);
    if (idx == rush_intervals.size()) {
        return false;
    } else {
        if (rush_intervals[idx].first <= time)
            return true;
        else
            return false;
    }

}
