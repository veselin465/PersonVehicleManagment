#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include "Registration.h"

class Person;

class Vehicle{

private:
    Registration regnum;
    std::string description;
    Person* owner;

public:

    Vehicle() = delete;

    Vehicle(const char* regnum_, const char* description_);

    Vehicle& operator=(const Vehicle& other);

    Vehicle(const Vehicle& copy);

    bool operator==(const Vehicle& other) const;

    bool operator==(const Registration& reg) const;

    bool operator==(const char* reg) const;

    void setOwner(Person* v);

    void removeOwner();

    const Person* getOwner() const;

    const Registration& getRegistration() const;

    const char* getDescription() const;

};

#endif // VEHICLE_H

