#ifndef VEHICLE_LIST_H
#define VEHICLE_LIST_H

#include <vector>
#include "Vehicle.h"

class Vehicle;

class VehicleList{

private:
    std::vector<Vehicle> vehicles;
    bool isUnique(const Vehicle& vehicle);
public:

    void addVehicle(const Vehicle& vehicle);

    Vehicle& findVehicleByRegnum(const char* regnum);

    void removeVehicleByRegnum(const char* regnum);

    void setOwner(const char* regnum, Person* p);

    void removeOwner(const char* regnum);

    const std::vector<Vehicle>& getVehicles();

};



#endif // VEHICLE_LIST_H

