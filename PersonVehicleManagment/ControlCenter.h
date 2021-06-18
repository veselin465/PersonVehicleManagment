#ifndef CONTROL_CENTER_H
#define CONTROL_CENTER_H

#include <iostream>
#include <vector>
#include "VehicleList.h"
#include "PeopleList.h"

class ControlCenter{

private:

    VehicleList vehicleList;
    PeopleList peopleList;
    std::vector <std::string> commandLines;

    std::vector <std::string> splitWithQuotes(const std::string& commandLine);

    void tolower(std::string& str);

    bool confirmAction(char yes, char no);

    int getIdType(const std::string& str);

    void stringToUpper(std::string& str);

    unsigned int parseStringToUInt(const std::string& str);

    bool fileExist(const std::string& filename);

    void addVehicle(const char* regnum, const char* desc);

    void addPerson(unsigned int UIN, const char* name);

    Vehicle& getVehicle(const char* regnum);

    Person& getPerson(unsigned int UIN);

    void acquireVehicleToPerson(const char* regnum, unsigned int UIN);

    void releaseVehicleFromPerson(const char* regnum, unsigned int UIN);

    const std::vector<Vehicle>& getAllVehicles();

    const std::vector<Person>& getAllPersons();

    void removeVehicle(const char* regnum);

    void removePerson(unsigned int UIN);

public:

    void loadFromFile(const std::string& filename);

    void saveToFile(const std::string& filename);

    const std::string executeCommand(const std::string& commandLine);

};


#endif // CONTROL_CENTER_H

