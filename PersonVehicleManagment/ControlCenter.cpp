#include <iostream>
#include <fstream>
#include "ControlCenter.h"


bool ControlCenter::confirmAction(char yes, char no){
    char input;
    std::cin >> input;
    std::cin.ignore();

    while(input != yes && input != no){
        std::cin >> input;
        std::cin.ignore();
    }

    return (yes == input);

}

bool ControlCenter::fileExist(const std::string& filename){

    bool doesExist = false;
    std::ifstream readFile(filename);

    if(readFile.is_open()){
        doesExist = true;
    }

    readFile.close();

    return doesExist;
}

void ControlCenter::loadFromFile(const std::string& filename){

    std::ifstream readFile(filename);
    std::string commandLine;

    if(readFile.fail()){
        std::cout << "Cannot open file!";
        return;
    }
    while (getline (readFile, commandLine)) {

        if(commandLine == "") continue;
        commandLines.push_back(commandLine);
    }

    readFile.close();

    size_t commandsCount = commandLines.size();
    size_t successfulExecutedCount = 0;
    for(size_t i = 0; i < commandsCount; i++){

        std::string currentCommand;

        currentCommand = commandLines[i];

        if(currentCommand.empty()) continue;
        try{
            executeCommand(currentCommand);
            successfulExecutedCount++;
        }
        catch (std::invalid_argument& e){
            std::cout << "\n";
            std::cout << "FAIL: \"" << currentCommand << "\"\n  -> ";
            std::cout << e.what();
        }


    }

    std::cout << "\nFile transfer finished. [" << successfulExecutedCount
        << "/" << commandsCount << "] completed commands. \n\n";

}

void ControlCenter::saveToFile(const std::string& filename){

    std::ifstream readFile(filename);

    if(readFile.is_open()){
        std::cout << "File exists. If you continue, file's entire contest will be rewritten. Y/N: ";
        bool res = confirmAction('Y', 'N');
        if(!res){
            return;
        }
    }

    readFile.close();

    std::ofstream writeFile(filename, std::ios::trunc);
    std::string commandLine;

    if(writeFile.fail()){
        std::cout << "Error opening file";
        return;
    }

    size_t count = commandLines.size();

    for(size_t i = 0; i < count; i++){
        writeFile << commandLines[i];
        writeFile << std::endl;
    }

    writeFile.close();

}

void ControlCenter::addVehicle(const char* regnum, const char* desc){
    Vehicle v(regnum, desc);
    vehicleList.addVehicle(v);
}

void ControlCenter::addPerson(unsigned int UIN, const char* name){
    Person p(UIN, name);
    peopleList.addPerson(p);
}

Vehicle& ControlCenter::getVehicle(const char* regnum){
    return vehicleList.findVehicleByRegnum(regnum);
}

Person& ControlCenter::getPerson(unsigned int UIN){
    return peopleList.findPersonByUIN(UIN);
}

void ControlCenter::acquireVehicleToPerson(const char* regnum, unsigned int UIN){
    Person* p = &peopleList.findPersonByUIN(UIN);
    Vehicle* v = &vehicleList.findVehicleByRegnum(regnum);
    peopleList.acquireVehicle(UIN, v);
    vehicleList.setOwner(regnum, p);
}

void ControlCenter::releaseVehicleFromPerson(const char* regnum, unsigned int UIN){
    Vehicle* v = &vehicleList.findVehicleByRegnum(regnum);
    peopleList.releaseVehicle(UIN, v);
    vehicleList.removeOwner(regnum);
}

const std::vector<Vehicle>& ControlCenter::getAllVehicles(){
    return vehicleList.getVehicles();
}

const std::vector<Person>& ControlCenter::getAllPersons(){
    return peopleList.getPeople();
}

void ControlCenter::removeVehicle(const char* regnum){

    Vehicle v = vehicleList.findVehicleByRegnum(regnum);

    if(v.getOwner() != nullptr){
        std::cout << "Vehicle is acquired by someone. Are you sure you want to remove entity (Y/N): ";
        bool conf = confirmAction('Y', 'N');
        if(!conf) return;
        releaseVehicleFromPerson(regnum, (*v.getOwner()).getUIN());
    }

    vehicleList.removeVehicleByRegnum(regnum);
}

void ControlCenter::removePerson(unsigned int UIN){

    Person p = peopleList.findPersonByUIN(UIN);
    size_t count = p.getVehicleCount();
    if(count != 0){
        std::cout << "Person acquires 1 or more vehicles. Are you sure you want to remove entity (Y/N): ";
        bool conf = confirmAction('Y', 'N');
        if(!conf) return;

        for(size_t i = 0; i < count; i++){
            Vehicle v = *p.getVehicles()[i];
            releaseVehicleFromPerson(v.getRegistration().getNumber(), UIN);
        }
    }

    peopleList.removePersonByUIN(UIN);

}



void ControlCenter::stringToUpper(std::string& str){
    for(size_t  i = 0; str[i]; i++){
        if('a' <= str[i] && str[i] <= 'z'){
            str[i] = str[i] + 'A' - 'a';
        }
    }
}

unsigned int ControlCenter::parseStringToUInt(const std::string& str){
    if(str.size() == 0) throw std::invalid_argument("Empty string is not a valid number. ");
    unsigned int res = 0;
    for(size_t i = 0; i < str.size(); i++){
        res *= 10;
        if(!('0' <= str[i] && str[i] <= '9')){
            throw std::invalid_argument("Invalid number format. ");
        }
        res += (str[i] - '0');
    }
    return res;
}

// 'reads' what type of id is provided
// 0 -> invalid
// 1 -> person (uint)
// 2 -> vehicle (Registration)
int ControlCenter::getIdType(const std::string& str){

    bool isDigit = true;
    for(size_t i = 0; i < str.size(); i++){
        if(!('0' <= str[i] && str[i] <= '9')){
            isDigit = false;
            break;
        }
    }

    if(isDigit){
        return 1;
    }else{
        try{
            Registration reg(str.c_str());
            return 2;
        }catch(std::invalid_argument& e){
            return 0;
        }
    }

}


const std::string ControlCenter::executeCommand(const std::string& commandLine){

    std::vector<std::string> argumentList;
    std::string currentStr;
    bool isInsideBracket = false;
    bool isEmpty = true;

    for(size_t i = 0 ; commandLine[i]; i++){

        if(commandLine[i] != ' '){
            isEmpty = false;
        }

        if(commandLine[i] == '\"'){
            isInsideBracket = !isInsideBracket;
            continue;
        }

        if(commandLine[i] == '\\'){

            currentStr += "\\";

            continue;
        }

        if(commandLine[i] == ' '){
            if(isInsideBracket){
                currentStr += ' ';
            }else{
                if(currentStr != ""){
                    argumentList.push_back(currentStr);
                    std::cout << "\n" << currentStr << "\n";
                }
                currentStr = "";
            }
            continue;
        }

        currentStr += commandLine[i];
    }

    if(isEmpty){
        throw std::invalid_argument
            ("Empty or not meaningful string. ");
    }

    if(currentStr != ""){
        argumentList.push_back(currentStr);
        std::cout << "\n" << currentStr << "\n";
    }

    if(isInsideBracket){
        throw std::invalid_argument
            ("Not every opening quote has closing one. ");
    }

    stringToUpper(argumentList[0]);


    std::string output = "";

    if(argumentList[0] == "VEHICLE"){
        if(argumentList.size() != 3){
            throw std::invalid_argument
            ("Incorrect use of command: VEHICLE <registration> <description>");
        }

        try{
            addVehicle(argumentList[1].c_str(), argumentList[2].c_str());
        }catch(std::invalid_argument& e){
            throw std::invalid_argument( (std::string) "Vehicle was not created. Reason: " + e.what());
        }

    }else if(argumentList[0] == "PERSON"){

        if(argumentList.size() != 3){
            throw std::invalid_argument
            ("Incorrect use of command: PERSON <name> <id>");
        }

        try{
            unsigned int UIN = parseStringToUInt(argumentList[2].c_str());
            addPerson(UIN, argumentList[1].c_str());
        }catch(std::invalid_argument& e){
            throw std::invalid_argument( (std::string) "Person was not created. Reason: " + e.what());
        }

    }else if(argumentList[0] == "ACQUIRE"){
        if(argumentList.size() != 3){
            throw std::invalid_argument
            ("Incorrect use of command: ACQUIRE <owner-id> <vehicle-id>");
        }

        try{
            unsigned int UIN = parseStringToUInt(argumentList[1].c_str());
            acquireVehicleToPerson(argumentList[2].c_str(), UIN);
        }catch(std::invalid_argument& e){
            throw std::invalid_argument(
                (std::string) "Person's ownership of a vehicle was not successfully set. Reason: "
                + e.what());
        }

    }else if(argumentList[0] == "RELEASE"){
        if(argumentList.size() != 3){
            throw std::invalid_argument
            ("Incorrect use of command: RELEASE <owner-id> <vehicle-id>");
        }

        try{
            unsigned int UIN = parseStringToUInt(argumentList[1].c_str());

            releaseVehicleFromPerson(argumentList[2].c_str(), UIN);
        }catch(std::invalid_argument& e){
            throw std::invalid_argument(
                (std::string) "Person's ownership of a vehicle was not successfully removed. Reason: "
                + e.what());
        }

    }else if(argumentList[0] == "REMOVE"){

        if(argumentList.size() != 2){
            throw std::invalid_argument
            ("Incorrect use of command: REMOVE [<person-id>|<vehicle-id>]");
        }

        int idType = getIdType(argumentList[1]);

        if(idType == 0){
            throw std::invalid_argument("Object removal was not successful. Reason: Not valid id format.");
        }

        if(idType == 1){
            try{
                unsigned int UIN = parseStringToUInt(argumentList[1]);
                removePerson(UIN);
            }catch(std::invalid_argument& e){
                throw std::invalid_argument(
                    (std::string) "Person removal was not successful. Reason: "
                    + e.what());
            }
        }

        if(idType == 2){
            try{
                removeVehicle(argumentList[1].c_str());
            }catch(std::invalid_argument& e){
                throw std::invalid_argument(
                    (std::string) "Vehicle removal was not successful. Reason: "
                    + e.what());
            }
        }


    }else if(argumentList[0] == "SHOW"){
        if(argumentList.size() != 2){
            throw std::invalid_argument
            ("Incorrect use of command: SHOW [PEOPLE|VEHICLES|<id>]");
        }

        int idType = getIdType(argumentList[1]);

        if(idType == 0){

            stringToUpper(argumentList[1]);

            if(argumentList[1] == (std::string)"PEOPLE"){

                const std::vector<Person> peopleVector = peopleList.getPeople();

                size_t count = peopleVector.size();

                for(size_t i = 0; i < count; i++){
                    output += std::to_string(i+1) + ": " + peopleVector[i].getName()
                        + " [" + std::to_string(peopleVector[i].getUIN()) + "]";
                }

                if(count == 0){
                    output += "(none)";
                }

            }else if(argumentList[1] == (std::string)"VEHICLES"){

                const std::vector<Vehicle> vehicleVector = vehicleList.getVehicles();
                size_t count = vehicleVector.size();

                for(size_t i = 0; i < count; i++){
                    output += std::to_string(i+1) + ": "
                        + vehicleVector[i].getRegistration().getNumber() + "\n";
                }

                if(count == 0){
                    output += "(none)";
                }

            }else{
                throw std::invalid_argument("Detailed view of an object was not successful. Reason: Not valid id format.");
            }
        }

        if(idType == 1){
            try{
                unsigned int UIN = parseStringToUInt(argumentList[1]);
                Person p = getPerson(UIN);
                output += ((std::string)"Person " + p.getName() + " [" + std::to_string(p.getUIN()) + "]. ");
                output += "Vehicles(id): ";
                size_t vehicleCount = p.getVehicleCount();

                for(size_t  i = 0; i < vehicleCount; i++){
                    Vehicle v = *(p.getVehicles()[i]);
                    output += v.getRegistration().getNumber();
                    if(i + 1 < vehicleCount){
                        output += ", ";
                    }
                }

                if(vehicleCount == 0){
                    output += "(none)";
                }


            }catch(std::invalid_argument& e){
                throw std::invalid_argument
                    ((std::string) "Detailed view of a person was not successful. Reason: " + e.what());
            }
        }

        if(idType == 2){
            try{
                Vehicle v = vehicleList.findVehicleByRegnum(argumentList[1].c_str());

                output += (std::string)"Vehicle [" + v.getRegistration().getNumber() + "]";
                if(v.getOwner() != nullptr){
                    const Person p = (*v.getOwner());
                    output += (std::string) " with owner name " + p.getName() + " [" + std::to_string(p.getUIN()) + "]. ";
                }else{
                    output += " with no owner. ";;
                }
                output += (std::string)"Description: " + v.getDescription();

            }catch(std::invalid_argument& e){
                throw std::invalid_argument
                    ((std::string) "Detailed view of a vehicle was not successful. Reason: " + e.what());
            }
        }

    }else if(argumentList[0] == "SAVE"){

        if(argumentList.size() != 2){
            throw std::invalid_argument
            ("Incorrect use of command: SAVE <path>");
        }

        saveToFile(argumentList[1]);

    }else if(argumentList[0] == "EXIT"){
        return "";
    }
    else{
        throw std::invalid_argument
            ("Unknown command: " + argumentList[0]);
    }
    if(argumentList[0] == "VEHICLE" || argumentList[0] == "PERSON"
       || argumentList[0] == "ACQUIRE"){
        commandLines.push_back(commandLine);
    }

    return output;

}

