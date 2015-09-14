#ifndef OOP_H
#define OOP_H

#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>

using namespace std;

class OOP
{
public:
    OOP();
};

enum CardType
{
    REDDIAMON, REDHEART, BLACKDIAMON, BLACKHEART
};

struct Card{
    CardType type;
    int value;
    bool available;
    Card(CardType _type, int _value): type(_type), value(_value){}
    bool operator==(const Card & card) const
    {
         return type==card.type && value== card.value;
    }
};

class Player
{
    int id;
    int score;
    vector<Card> cards;
public:
    Player(int _id): id(_id), score(0) {}
    void addCard(Card &card)
    {
        cards.push_back(card);
    }
    void put(Card &card)
    {
        vector<Card>::iterator itr=find(cards.begin(), cards.end(), card);
        cards.erase(itr);
    }
};

class CardDeck
{
    vector<Card> deck;
    vector<Card> availableCards;
    vector<Player> team;
public:
    CardDeck(){
        shuffle();
    }
    void shuffle(){}
    void distribute(){}

    bool oneRound(){ return false; }

};

enum EmployeeLevel
{
    ASSOCIATE, MANAGER, DIRECTOR
};

struct Call
{
    EmployeeLevel requiredlevel;
    string desc;
    Call(EmployeeLevel _level, string & _desc)
        :requiredlevel(_level), desc(_desc)
    {}
};

struct Employee
{
    string name;
    int id;
    EmployeeLevel level;
    bool available;
    Employee(string _name, int _id, EmployeeLevel _level)
        :name(_name), id(_id), level(_level), available(true)
    {}
    virtual ~Employee(){}

    Employee(): id(-1) {}

    virtual void processCall(Call call){}

    bool isAbleAnswer(Call call)
    {
        return level>=call.requiredlevel;
    }

};

class CallCenter
{
    vector<Employee> team;
    deque<Call> waitList;

public:
    CallCenter(vector<Employee> & _team)
        : team(_team)
    { }

    void receiveCall(Call _call)
    {
        waitList.push_back(_call);
    }

    void answerCall()
    {
        if (waitList.empty()) return;

        Call call=waitList.front();

        bool ok=findEmployeeToAnswer(call);

        if (ok)
            waitList.pop_front();
    }


private:
    Employee getAvailableEmploy(Call call)
    {
        size_t i;
        for (i=0; i<team.size(); i++)
        {
            Employee p=team[i];
            if (p.available && p.isAbleAnswer(call))
                break;
        }
        if (i != team.size())
            return team[i];
        else
            return Employee();

    }

    bool findEmployeeToAnswer(Call call)
    {
        Employee p=getAvailableEmploy(call);
        if (p.id==-1) return false;
        else
        {
            p.processCall(call);
            return true;
        }
    }
};

enum ITEM
{
    CAN, CHIPS,COOKIE
};

class ItemManager
{
    vector<ITEM> items;

public:
    ItemManager(vector<ITEM> & _items)
    {
        items=_items;
    }
    void add(ITEM x)
    {
        items.push_back(x);
    }
    void remove(ITEM x)
    {
        vector<ITEM>::iterator itr=find(items.begin(), items.end(), x);
        items.erase(itr);
    }
    int checkItems()
    {
        return items.size();
    }


};

class PaymentManager
{
    int deposit;
    // cardmanager;
public:
    PaymentManager(int _deposit) : deposit(_deposit){}
    void swipCard() {}
    void insertBill(int bill)
    {
        deposit += bill;
    }

};

enum ACTION
{
    CHOOSEITEM, INSERTBILL, SWIPCARD, PRESSKEY
};

class UI
{
    map<ACTION, int> actionBoard;
    deque<int> data;
    // SCREEN MANAGER
public:
    void run(ACTION x)
    {
        int t=actionBoard.find(x)->second;
    }

};

class VendingMachine
{
    ItemManager itemManager;
    PaymentManager payManager;
    UI ui;
public:
    VendingMachine();
    void addItems(){}
    void removeItems(){}
    int checkItems(){ return itemManager.checkItems();}

    void UIInteraction(ACTION x){ ui.run(x); }

};

// animal kingdom
// tree structure: animal->bird, mammal, insect, fish
struct Attribute
{
    int weight, height, color;
    Attribute(int _weight, int _height, int _color) : weight(_weight), height(_height), color(_color) {}
};

class Animal
{
public:
    Animal(){}
    virtual ~Animal(){}
    virtual void feed()=0;
    virtual void respire()=0;
    virtual void reproduce()=0;
    vector<Attribute> getAttrs() {return attrs; }
protected:
    vector<Attribute> attrs;

};

class Bird : public Animal
{
public:
    Bird(vector<Attribute> & _attrs)  { attrs = _attrs; }
    void feed(){}
    void respire(){}
    void reproduce(){}

};


#endif // OOP_H
