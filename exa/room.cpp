#include "room.h"
#include <utility>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/** constructor to build a room with number of persons
  @param _roomID ID of the room
  @param numberOfPersons number of persons in a room
  */
Room::Room(const int _roomID, const int numberOfPersons)
    : roomID(_roomID), interestGroupList(4)
{
    for (int i=0; i<numberOfPersons; i++)
    {
        // make a person, and insert it to personList with ID=i;
        boost::shared_ptr<Person> person(new Person(i));
        personList.insert(std::make_pair(i, person));

        // update interestGroups
        interestGroupList.at(person->getInterest()).insert(person->getPersonID());
    }
    // display the room info
    printAllPersonIDs();
    printInterestGroups();
    cout << endl;
}

/** persons enter the room
  @param twoPersons pair of two persons entering the room
  */
void Room::enter(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > &twoPersons)
{
    // update personList
    personList.insert(std::make_pair(twoPersons.first->getPersonID(), twoPersons.first));
    personList.insert(std::make_pair(twoPersons.second->getPersonID(), twoPersons.second));

    // update pairList
    pairList.insert(std::make_pair(twoPersons.first->getPersonID(), twoPersons.second->getPersonID()));

    // update interestGroupList
    interestGroupList.at(twoPersons.first->getInterest()).insert(twoPersons.first->getPersonID());
    interestGroupList.at(twoPersons.second->getInterest()).insert(twoPersons.second->getPersonID());
}

/** persons leave the room
  @param twoPersons pair of two persons leaving the room
  */
void Room::leave(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > &twoPersons)
{
    // update personList
    personList.erase(twoPersons.first->getPersonID());
    personList.erase(twoPersons.second->getPersonID());

    // update interestGroup
    interestGroupList.at(twoPersons.first->getInterest()).erase(twoPersons.first->getPersonID());
    interestGroupList.at(twoPersons.second->getInterest()).erase(twoPersons.second->getPersonID());
}

/** two people meet and check whether they have common interest
  @param _pair pair of two persons in a meeting
  @return true if they have a common interest, otherwise false;
  */
bool Room::meet(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > &_pair) const
{
    if (_pair.first->getInterest()==_pair.second->getInterest())
        return true;
    else
        return false;
}

/** print the list of person IDs in the room
 */
void Room::printAllPersonIDs() const
{
    char _roomID=char(roomID)+'A';
    std::cout << "Room " << _roomID << " (person ID): ";
    std::tr1::unordered_map<int, boost::shared_ptr<Person> >::const_iterator itr=personList.begin();
    for (; itr != personList.end(); itr++)
        std::cout << itr->first << " ";

    cout << endl;
}

/** print the pair list of persons who enter the room as groups
 */
void Room::printPairList() const
{
    char roomID=(char)roomID+'A';
    std::cout << "Pair groups in Room " << roomID << ": ";
    std::tr1::unordered_map<int, int>::const_iterator itr;
    for (itr=pairList.begin(); itr != pairList.end(); itr++)
        std::cout << itr->first << "-" << itr->second << " ";
    cout << endl;
}

/** randomly select persons
  @return two selected person IDs
  */
std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > Room::selectPersonPair() const
{
    // build ID array for random selection
    std::vector<int> IDarray(personList.size());

    int current=0;
    std::tr1::unordered_map<int, boost::shared_ptr<Person> >::const_iterator itr=personList.begin();
    for (; itr != personList.end(); itr++, current++)
    {
        IDarray.at(current)=itr->first;
    }

    int randNum;

    // get the random number between 0 and array size
    randNum=rand() % IDarray.size();
    // select the first person
    boost::shared_ptr<Person> firstPerson = personList.find(IDarray.at(randNum))->second;

    // delete the first person in the IDarray
    IDarray.erase(IDarray.begin()+randNum);

    // select the second person
    randNum=rand() % IDarray.size();
    boost::shared_ptr<Person> secondPerson = personList.find(IDarray.at(randNum))->second;

    return pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> >(firstPerson, secondPerson);
}

/** check whether there are two persons who have common interest in the room
 */
bool Room::IsPossibleGrouping() const
{
    std::vector<std::tr1::unordered_set<int> >::const_iterator itr=interestGroupList.begin();
    for (; itr != interestGroupList.end(); itr++)
    {
        std::tr1::unordered_set<int> interestGroup=*itr;
        if (interestGroup.size()>1) return true;
    }
    return false;
}

/** print the interest group information, including the number of persons and IDS in each group
 */
void Room::printInterestGroups() const
{
    int groupNo=0;
    vector<std::tr1::unordered_set<int> >::const_iterator itr=interestGroupList.begin();
    for (; itr != interestGroupList.end(); itr++, groupNo++)
    {
        std::tr1::unordered_set<int> oneGroup=*itr;
        cout << "Group of " << Person::convertInterestIDToString(groupNo) << " (" << oneGroup.size() << "): ";

        std::tr1::unordered_set<int>::const_iterator t=oneGroup.begin();
        for (; t != oneGroup.end(); t++)
            cout << *t << " ";

        cout << endl;
    }

}

/** initialize _instance=NULL
 */
boost::shared_ptr<RoomFactory> RoomFactory::_instance=boost::shared_ptr<RoomFactory>();

/** singleton to get the sole instance
 */
boost::shared_ptr<RoomFactory> RoomFactory::instance()
{
    if (!_instance)
    {
        _instance=boost::shared_ptr<RoomFactory>(new RoomFactory);
    }
    return _instance;
}

/** make a room with initial parameters
 * @param roomType type of room. Currently there is only one type of room with roomType=0
 * @param _roomID ID of room
 * @param numberOfPersons number of persons
 * @return shared pointer of RoomBase
 */
boost::shared_ptr<RoomBase> RoomFactory::makeRoom(const int roomType, const int _roomID, const int numberOfPersons) const
{
    switch(roomType)
    {
    case 0:
        return boost::shared_ptr<RoomBase>(new Room(_roomID, numberOfPersons));
    default:
        return boost::shared_ptr<RoomBase>();
    }

}
