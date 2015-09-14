#ifndef PERSON_H
#define PERSON_H

#include <string>

enum Interest
{
    INTEREST_epidemiology,
    INTEREST_biostatistics,
    INTEREST_clinical_research,
    INTEREST_health_policy
};

class Person
{
public:
    Person(const int _personID);
    int getPersonID() const { return personID; }
    Interest getInterest() const { return interest; }
    std::string getInterestString() const;
    static std::string convertInterestIDToString(const int interestID);

private:
    Interest interest;
    int personID;


};

#endif // PERSON_H
