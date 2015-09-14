#ifndef PARTY_H
#define PARTY_H

#include "room.h"
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <tr1/unordered_map>

// singleton design pattern to make sure only one instance, and globel access
class Party
{
public:
    static boost::shared_ptr<Party> instance();
    void makeParty(const int numberOfRooms, const int numberOfPersons);
    bool interaction();

    void printRoomInfo() const;
    bool printPersonInfo(const int personID) const;

private:
    Party(){};
    static boost::shared_ptr<Party> _instance;
    std::vector<boost::shared_ptr<RoomBase> > roomList;

};

#endif // PARTY_H
