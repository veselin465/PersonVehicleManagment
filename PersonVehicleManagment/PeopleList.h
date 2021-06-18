#ifndef PEOPLE_LIST_H
#define PEOPLE_LIST_H

#include <vector>
#include "Person.h"

class PeopleList{

private:
    std::vector<Person> persons;
    bool isUnique(const Person& person);
public:

    void addPerson(const Person& person);

    Person& findPersonByUIN(int UIN);

    void removePersonByUIN(int UIN);

    void acquireVehicle(int UIN, Vehicle* vehicleId);

    void releaseVehicle(int UIN, Vehicle* vehicleId);

    const std::vector<Person>& getPeople();

};

#endif // PEOPLE_LIST_H
