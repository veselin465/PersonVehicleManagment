#ifndef PERSON_H
#define PERSON_H

#include "Vehicle.h"

class Vehicle;

class Person{

private:
    std::string name;
    unsigned int UIN;               // User Identification Number
    std::size_t vehiclesCount;
    std::size_t vehiclesAlloc;
    Vehicle** vehicles;

public:

    Person() = delete;

    Person(unsigned int UIN, const char* name_);

    Person& operator=(const Person& other);

    Person(const Person&);

    ~Person();

    bool operator==(const Person& other) const;

    bool operator==(unsigned int UIN) const;

    void acquireVehicle(Vehicle* v);

    void releaseVehicle(Vehicle* v);

    const unsigned int getUIN() const;

    const std::string getName() const;

    Vehicle** getVehicles() const;

    const std::size_t getVehicleCount() const;

};

#endif // PERSON_H
