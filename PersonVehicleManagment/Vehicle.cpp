#include "Registration.h"
#include "Vehicle.h"
#include <string.h>

Vehicle::Vehicle(const char* regnum_, const char* description_)
    :regnum(regnum_){

    if(description_ == nullptr){
        throw std::invalid_argument("Vehicle :: Null pointer");
    }

    this->description = description_;
    this->owner = nullptr;
}

Vehicle& Vehicle::operator=(const Vehicle& other){
    this->regnum = other.regnum;
    this->description = other.description;
    this->owner = other.owner;
    return *this;
}

Vehicle::Vehicle(const Vehicle& copy)
    :regnum(copy.regnum){
    *this = copy;
}

bool Vehicle::operator==(const Vehicle& other) const{
    return regnum == other.regnum;
}

bool Vehicle::operator==(const Registration& reg) const{
    return regnum == reg;
}

bool Vehicle::operator==(const char* reg) const{

    if(reg == nullptr){
        throw std::invalid_argument("Vehicle :: Null pointer");
    }

    try{
        Registration reg1(reg);
        return (reg1 == regnum);
    }catch(std::invalid_argument& e){
        return false;
    }
}

void Vehicle::setOwner(Person* v){
    this->owner = v;            // setting nullptr to owner is acceptable
}

void Vehicle::removeOwner(){
    this->owner = nullptr;
}

const Person* Vehicle::getOwner() const{
    return owner;
}

const Registration& Vehicle::getRegistration() const{
    return regnum;
}

const char* Vehicle::getDescription() const{
    return description.c_str();
}
