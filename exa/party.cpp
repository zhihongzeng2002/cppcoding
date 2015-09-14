#include "party.h"
#include <iostream>

using namespace std;

/** initialize the singleton _instance=NULL
 */
boost::shared_ptr<Party> Party::_instance=boost::shared_ptr<Party>();

/** get singleton instance
 */
boost::shared_ptr<Party> Party::instance()
{
    if (!_instance)
    {
        _instance = boost::shared_ptr<Party>(new Party);
    }
    return _instance;
}

/** make a party
  @param numberOfRooms number of rooms in the party
  @param numberOfPerson number of persons in the first room
  */
void Party::makeParty(const int numberOfRooms, const int numberOfPersons)
{
    // make rooms
    roomList=vector<boost::shared_ptr<RoomBase> >(numberOfRooms);
    for (int i=0; i<numberOfRooms; i++)
    {
        boost::shared_ptr<RoomBase> roomPtr;

        if (!i) // make a room with persons (Room A)
            roomPtr = RoomFactory::instance()->makeRoom(0, i, numberOfPersons);
        else // make an empty room (Room B)
            roomPtr = RoomFactory::instance()->makeRoom(0, i);

        roomList.at(i)=roomPtr;
    }
}

/** interaction
 * @return true if interaction can continue, otherwise false
  */
bool Party::interaction()
{
    vector<boost::shared_ptr<RoomBase> >::iterator itr = roomList.begin();
    boost::shared_ptr<RoomBase> roomA = *itr;

    // randomly select two persons
    std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > _pair = roomA->selectPersonPair();

    cout << "Person IDs in the interation: " << _pair.first->getPersonID() << ", " << _pair.second->getPersonID() << endl;

    // meet
    bool interest_eq=roomA->meet(_pair);

    // if they have common interest, leave roomA and enter roomB
    if (interest_eq)
    {
        cout << " share interests and enter Room B as a group" << endl;

        // update RoomA
        roomA->leave(_pair);
        // print info: who is in which room, who is in a group
        cout << "Room A: " << endl;
        roomA->printInterestGroups();

        // update RoomB
        itr++;
        boost::shared_ptr<RoomBase> roomB = *itr;
        roomB->enter(_pair);
        cout << "Room B: " << endl;
        roomB->printInterestGroups();

        // check whether there is possible grouping
        return roomA->IsPossibleGrouping();
    }

    // no update
    cout << " don't share interests and rejoin the pool at Room A" << endl;
    return true;
}

/** print person information, including interest and room ID
  @param personID person ID
  @return true if personID is valid, otherwise false;
  */
bool Party::printPersonInfo(const int personID) const
{
    for (unsigned int i=0; i<roomList.size(); i++)
    {
        boost::shared_ptr<RoomBase> room=roomList.at(i);
        std::tr1::unordered_map<int, boost::shared_ptr<Person> > _personList=room->getPersonList();
        std::tr1::unordered_map<int, boost::shared_ptr<Person> >::const_iterator itr=_personList.find(personID);
        if (itr != _personList.end())
        {
            char location=char(i)+'A';
            std::cout << "PersonID=" << personID << "; Location=" << location
                      << "; Interest=" << itr->second->getInterestString() << endl;

            return true;
        }
    }
    return false;
}

/** print info: who is in which room, who is in a group (entering group)
  */
void Party::printRoomInfo() const
{
    // print who is which room
    int i=0;
    vector<boost::shared_ptr<RoomBase> >::const_iterator itr=roomList.begin();
    for (; itr != roomList.end(); itr++, i++)
    {
        char location=char(i)+'A';
        cout << "Room " << location << endl;
        boost::shared_ptr<RoomBase> room = *itr;
        room->printInterestGroups();
    }

    // print who is in a group. Only RoomB has grouping info
    itr=roomList.begin();
    itr++;
    boost::shared_ptr<RoomBase> roomB = *itr;
    roomB->printPairList();
}
