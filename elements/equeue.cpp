#include "equeue.h"
#include <queue>
#include <string>
#include <iostream>

Equeue::Equeue()
{
}

void Equeue::find_closest_k_stars(stringstream &ss, int k)
{
    priority_queue<Star, vector<Star> > min_queue;
    string line;

    while (std::getline(ss, line))
    {
        stringstream line_stream(line);
        string buf;
        getline(line_stream, buf, ',');

        int id=std::stoi(buf);
        vector<int> data(3);
        for (int i=0; i<3; i++)
        {
            getline(line_stream, buf, ',');
            data[i]=stoi(buf);
        }
        Star t(id, data[0], data[1], data[2]);

        if (min_queue.size()==k)
        {
            Star far_star=min_queue.top();
            if (far_star.distance>t.distance)
            {
            min_queue.pop();
            min_queue.push(t);
            }
        }
        else
            min_queue.push(t);
    }

    while (!min_queue.empty())
    {
        cout << min_queue.top().distance << endl;
        min_queue.pop();
    }

}
