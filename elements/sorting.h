#ifndef SORTING_H
#define SORTING_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Sorting
{
public:
    Sorting();

    void radixSort(vector<int> &A);
    void flipSort(vector<int> &A);
    struct Task {
        int startT, endT;
        Task(int _s, int _e) : startT(_s), endT(_e) {}
        bool operator<(const Task & that) const {
            return startT < that.startT;
        }
    };

    vector<int> findMinVisit(vector<Task> &tasks);
    int calcMaxNumTasks(const vector<Task> & task);
    vector<Task> calcUnionTasks(const vector<Task> &task);
    vector<Sorting::Task> calcUnionTasks_better(vector<Task> &tasks);
    void testMaxNumTasks();

    void calcCharFrequency_nomap(string s);

    void indirect_sort(const string &src, const string &des);

    void sortStringWithLargeLengthVariation(string & filename);

    vector<int> findIntersectionSortedArrays(vector<int> &A, vector<int> &B);

    //13.4
    struct Person
    {
        int key;
        string name;
        Person(int _key, string _name) : key(_key), name(_name) {}
    };

    void stableSortPersons(vector<Person> &people);

    struct HashPerson
    {
        int operator()(const Person &p) const
        {
            return hash<int>()(p.key) ^ hash<string>()(p.name);
        }
    };

    void count_sort_person_with_key(vector<Person> &people);
    void count_sort_person_with_key2(vector<Person> &people);
    void testCountPerson();

    struct Player
    {
        bool operator<(const Player&that) const
        {
            return height < that.height;
        }
        int height;
    };

    class Team
    {
    public:
        Team(vector<int> heights)
        {
            for (auto &h : heights)
            {
                team.emplace_back(Player{h});
            }
        }

    vector<Player> sortPlayer()
    {
        sort(team.begin(), team.end());
        return team;
    }

    bool operator<(Team & that)
    {
        vector<Player> thisTeam = sortPlayer();
        vector<Player> thatTeam(that.sortPlayer());
        for (int i=0;i<thisTeam.size() && i<thatTeam.size(); i++)
            if ( thisTeam[i].height <= thatTeam[i].height)
                return false;

        return true;

    }

    private:
        vector<Player> team;
    };

};

#endif // SORTING_H
