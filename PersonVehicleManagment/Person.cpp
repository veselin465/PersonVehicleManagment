#include <iostream>

#include "Person.h"

Person::Person(unsigned int UIN_, const char* name_){

    if(name_ == nullptr){
        throw std::invalid_argument("Person :: Null pointer");
    }

    UIN = UIN_;
    name = name_;
    vehiclesAlloc = 2;
    vehiclesCount = 0;

    vehicles = new Vehicle*[vehiclesAlloc];
}

Person& Person::operator=(const Person& other){

    this->UIN = other.UIN;
    this->name = other.name;
    this->vehiclesAlloc = other.vehiclesAlloc;
    this->vehiclesCount = other.vehiclesCount;
    delete[] this->vehicles;
    this->vehicles = new Vehicle*[vehiclesAlloc];
    for(std::size_t i = 0; i < vehiclesCount; i++){
        vehicles[i] = other.vehicles[i];
    }
    return *this;
}

Person::Person(const Person& copy){
    vehiclesCount = 0;
    vehiclesAlloc = 2;
    vehicles = new Vehicle*[vehiclesAlloc];
    *this = copy;
}

Person::~Person(){
    delete[] this->vehicles;
}

bool Person::operator==(const Person& other) const{
    return UIN == other.UIN;
}

bool Person::operator==(unsigned int UIN) const{
    return this->UIN == UIN;
}

void Person::acquireVehicle(Vehicle* v){

    if(v == nullptr){
        throw std::invalid_argument("Person :: Null pointer");
    }

    // check unique
    for(size_t i = 0; i < vehiclesCount; i++){
        if(*(vehicles[i]) == *v){
            throw std::invalid_argument("Attempt to register already registered vehicle.");
        }
    }

    // check vehicles capacity
    if(vehiclesCount + 1 >= vehiclesAlloc){
        vehiclesAlloc *= 2;
        Vehicle** tmp = new Vehicle*[vehiclesAlloc];
        for(std::size_t i = 0; i < vehiclesCount; i++){
            tmp[i] = vehicles[i];
        }
        delete[] vehicles;
        vehicles = tmp;
    }

    // add vehicle pointer
    vehicles[vehiclesCount++] = v;
}

void Person::releaseVehicle(Vehicle* v){

    if(v == nullptr){
        throw std::invalid_argument("Person :: Null pointer");
    }

    for(size_t  i = 0; i < vehiclesCount; i++){
        if(v == vehicles[i]){
            Vehicle* temp = vehicles[i];
            vehicles[i] = vehicles[vehiclesCount-1];
            vehicles[vehiclesCount-1] = temp;
            vehiclesCount--;
            return;
        }
    }
    throw std::invalid_argument("Not found vehicle. ");
}

const unsigned int Person::getUIN() const{
    return UIN;
}

const std::string Person::getName() const{
    return name;
}

Vehicle** Person::getVehicles() const{
    return vehicles;
}

const std::size_t Person::getVehicleCount() const{
    return vehiclesCount;
}
