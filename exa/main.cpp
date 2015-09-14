#include <iostream>
#include <tr1/unordered_set>
#include <string>
#include "party.h"
#include <algorithm>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    // check the input arguments
    if (argc < 3)
    {
        cout << "SYNOPSIS\n";
        cout << "   " << argv[0] << " numberOfPersons numberOfInteraction\n\n";
        return 0;
    }

    // get the number of persons from the input argument
    const int numberOfPersons = atoi(argv[1]);
    const int numberOfInteraction = atoi(argv[2]);

    cout << "Input arguments: " << endl;
    cout << "Number of people: " << numberOfPersons << endl;
    cout << "Number of Interaction: " << numberOfInteraction << endl;
    cout << endl;

    srand(time(NULL));

    // make a party with 2 rooms and numberOfPersons
    cout << "----------Building a party" << endl;
    Party::instance()->makeParty(2, numberOfPersons);

    cout << "----------Interaction" << endl;

    // starting time
    clock_t initT, t;
    initT=clock();

    for (int i=0; i<numberOfInteraction; i++)
    {
        t=clock()-initT;
        cout << "Time step " << i << ": Second " << float(t)/CLOCKS_PER_SEC << endl;

        bool possibleGrouping = Party::instance()->interaction();

        cout << endl;

        if (!possibleGrouping) break;
    }

    cout << "-----------Summary at the end of the party:" << endl;
    Party::instance()->printRoomInfo();
    cout << endl;

    // given ID #, print a person interest and room ID
    cout << "-----------Inquiry" << endl;

    while(true)
    {
        string input0;
        cout << "Inquire the info of a person? (y/n) " ;
        getline(cin, input0);

        if (input0=="y"|| input0== "Y")
        {
            cout << "Please enter the person ID: ";
            getline(cin, input0);
            int personID=atoi(input0.c_str());
            if (!Party::instance()->printPersonInfo(personID))
            {
                cout << "person ID is invalid" << endl;
            }
        }
        else if (input0=="n" || input0=="N")
            return 0;
        else
            cout << "Only y or n is valid input" << endl;

        cout << endl;

    }

     return 0;
}

