#ifndef ROOM_H
#define ROOM_H

#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include "person.h"
#include <utility>
#include <vector>

#include <boost/smart_ptr/shared_ptr.hpp>

class RoomBase
{
public:
    virtual ~RoomBase(){}
    virtual void enter(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons)=0;
    virtual void leave(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons)=0;
    virtual bool meet(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons) const = 0;
    virtual void printInterestGroups() const =0;
    virtual std::tr1::unordered_map<int, boost::shared_ptr<Person> > getPersonList() const =0;
    virtual std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > selectPersonPair() const =0;
    virtual bool IsPossibleGrouping() const=0;
    virtual void printPairList() const =0;

};

class Room : public RoomBase
{
public:
    Room(const int _roomID, const int numberOfPersons=0);

    void enter(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons);
    void leave(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons);
    bool meet(const std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > & twoPersons) const;
    void printInterestGroups() const;
    std::tr1::unordered_map<int, boost::shared_ptr<Person> > getPersonList() const {return personList; }
    std::pair<boost::shared_ptr<Person>, boost::shared_ptr<Person> > selectPersonPair() const;
    bool IsPossibleGrouping() const;

private:

    int roomID;
    std::tr1::unordered_map<int, boost::shared_ptr<Person> > personList;
    std::tr1::unordered_map<int, int> pairList;
    std::vector<std::tr1::unordered_set<int> > interestGroupList;

    void printAllPersonIDs() const ;
    void printPairList() const;

};

class RoomFactory
{
public:
    static boost::shared_ptr<RoomFactory> instance();
    boost::shared_ptr<RoomBase> makeRoom(const int roomType, const int _roomID, const int numberOfPersons=0) const;

private:
    RoomFactory(){}
    static boost::shared_ptr<RoomFactory> _instance;
};

#endif // ROOM_H
