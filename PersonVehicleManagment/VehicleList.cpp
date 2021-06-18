#include <iostream>
#include "VehicleList.h"

bool VehicleList::isUnique(const Vehicle& vehicle){

    size_t count = vehicles.size();

    for(size_t  i = 0; i < count; i++){
        if(vehicles[i] == vehicle){
            return false;
        }

    }

    return true;
}

void VehicleList::addVehicle(const Vehicle& vehicle){
    if(isUnique(vehicle)){
        vehicles.push_back(vehicle);
    }else{
        throw std::invalid_argument("Vehicle is not unique.");
    }
}

Vehicle& VehicleList::findVehicleByRegnum(const char* regnum){

    if(regnum == nullptr){
        throw std::invalid_argument("VehicleList :: Null pointer");
    }

    size_t count = vehicles.size();

    for(size_t  i = 0 ; i < count; i++){
        if(vehicles[i] == regnum) return vehicles[i];
    }

    throw std::invalid_argument("Vehicle was not found.");
}

void VehicleList::removeVehicleByRegnum(const char* regnum){

    if(regnum == nullptr){
        throw std::invalid_argument("VehicleList :: Null pointer");
    }

    size_t count = vehicles.size();

    for(size_t  i = 0 ; i < count; i++){
        if(vehicles[i] == regnum){
            vehicles.erase(vehicles.begin() + i);
            return;
        }
    }

    throw std::invalid_argument("Vehicle was not found.");
}

void VehicleList::setOwner(const char* regnum, Person* p){

    if(regnum == nullptr){
        throw std::invalid_argument("VehicleList :: Null pointer");
    }
    /// std::vector<Vehicle>::iterator

    size_t count = vehicles.size();

    for(size_t i = 0; i < count; i++){
        if(vehicles[i] == regnum){
            vehicles[i].setOwner(p);
            return;
        }
    }

    throw std::invalid_argument("Vehicle was not found.");
}

void VehicleList::removeOwner(const char* regnum){

    if(regnum == nullptr){
        throw std::invalid_argument("VehicleList :: Null pointer");
    }

    size_t count = vehicles.size();

    for(size_t i = 0; i < count; i++){
        if(vehicles[i] == regnum){
            vehicles[i].removeOwner();
            return;
        }
    }
    throw std::invalid_argument("Vehicle was not found.");
}

const std::vector<Vehicle>& VehicleList::getVehicles(){
    return vehicles;
}
