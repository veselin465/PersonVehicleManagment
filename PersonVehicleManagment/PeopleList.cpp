#include <iostream>
#include "PeopleList.h"

bool PeopleList::isUnique(const Person& person){

    size_t count = persons.size();

    for(size_t  i = 0; i < count; i++){
        if(persons[i] == person) return false;
    }

    return true;
}

void PeopleList::addPerson(const Person& person){
    if(isUnique(person)){
        persons.push_back(person);
    }else{
        throw std::invalid_argument("Person is not unique.");
    }
}

Person& PeopleList::findPersonByUIN(int UIN){

    size_t count = persons.size();

    for(size_t  i = 0; i < count; i++){
        if(persons[i] == UIN) return (persons[i]);

    }

    throw std::invalid_argument("Person was not found.");
}

void PeopleList::removePersonByUIN(int UIN){

    size_t count = persons.size();

    for(size_t  i = 0; i < count; i++){
        if(persons[i] == UIN){
            persons.erase(persons.begin() + i);
            return;
        }

    }

    throw std::invalid_argument("Person was not found.");
}

void PeopleList::acquireVehicle(int UIN, Vehicle* v){

    if(v == nullptr){
        throw std::invalid_argument("PeopleList :: Null pointer");
    }

    size_t count = persons.size();

    for(size_t  i = 0; i < count; i++){
        if(persons[i] == UIN){
            persons[i].acquireVehicle(v);
            return;
        }

    }

    throw std::invalid_argument("Person was not found.");
}

void PeopleList::releaseVehicle(int UIN, Vehicle* v){

    if(v == nullptr){
        throw std::invalid_argument("PeopleList :: Null pointer");
    }

    size_t count = persons.size();

    for(size_t  i = 0; i < count; i++){
        if(persons[i] == UIN){
            persons[i].releaseVehicle(v);
            return;
        }

    }

    throw std::invalid_argument("Person was not found.");
}

const std::vector<Person>& PeopleList::getPeople(){
    return persons;
}
