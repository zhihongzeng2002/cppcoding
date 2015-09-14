#include <stdlib.h>
#include <time.h>
#include "person.h"

/** constructor
  @param _personID ID of person
  */
Person::Person(const int _personID) : personID(_personID)
{
    // randomly assign a interest
    interest=Interest(rand() % 4);
}

/** get string of person's interest
 */
std::string Person::getInterestString() const
{
    return convertInterestIDToString((int)interest);
}

/** convert int of person's interest to string
 @param interest ID int of person ID
*/
std::string Person::convertInterestIDToString(const int interestID)
{
    std::string interestString;

    switch(interestID)
    {
    case 0:
        interestString = "epidemiology";
        break;
    case 1:
        interestString = "biostatistics";
        break;
    case 2:
        interestString = "clinical research";
        break;
    case 3:
        interestString = "health policy";
        break;
    default:
        interestString = "invalid interest";
    }
    return interestString;
}
