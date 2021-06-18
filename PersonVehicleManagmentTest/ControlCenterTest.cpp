#include "../PersonVehicleManagment/ControlCenter.h"

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"


bool approxStringCompare(const std::string& str1, const std::string& str2){

    const unsigned int percentage = 100;

    unsigned int sizeMin = std::min(str1.size(), str2.size());
    unsigned int sizeMax = std::min(str1.size(), str2.size());
    unsigned int sizeAverage = (sizeMin + sizeMax) / 2;
    unsigned int match = 0;

    if(sizeMin == 0) return sizeMax == 0;

    for(unsigned int i = 0; i < sizeMin; ++i){
        if(str1[i] == str2[i]){
            match++;
        }
    }

    unsigned int resPercentage = (100 * match) / sizeAverage;

    return resPercentage >= percentage;


}

TEST_CASE("Inside function :: approxStringCompare(const string&, const string&, int"){
    REQUIRE (approxStringCompare("qwer1", "qwer1"));
    REQUIRE (approxStringCompare("QWERTYUZXC\n", "QWERTYUZXC"));
    REQUIRE (approxStringCompare("QWeQWERTY UZXCQWERTYUZXC!@", "QWeQWERTY UZXCQWERTYUZXC!@"));
}


TEST_CASE("ControlCenter :: show vehicles"){

    ControlCenter cc;

    std::string res;

    res = cc.executeCommand("show vehicles");
    REQUIRE (approxStringCompare(res, "(none)"));

    cc.executeCommand("vehicle qw1234qw \"description 1\"");

    res = cc.executeCommand("show vehicles");
    REQUIRE (approxStringCompare(res, "1: qw1234qw"));

}

TEST_CASE("ControlCenter :: show people"){

    ControlCenter cc;

    std::string res;

    res = cc.executeCommand("show people");
    REQUIRE (approxStringCompare(res, "(none)"));

    cc.executeCommand("person \"name 1\" 123");

    res = cc.executeCommand("show people");
    REQUIRE (approxStringCompare(res, "1: name 1 [123]"));

}

TEST_CASE("ControlCenter :: show <what> (person, vehicle, undefined)"){

    ControlCenter cc;

    std::string res;

    cc.executeCommand("vehicle qw1234qw \"description 1\"");
    cc.executeCommand("person \"name 1\" 123");

    try{
        cc.executeCommand("show");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: SHOW [PEOPLE|VEHICLES|<id>]"));
    }

    try{
        cc.executeCommand("show too many");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: SHOW [PEOPLE|VEHICLES|<id>]"));
    }

    try{
        cc.executeCommand("show AA1111AA");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Detailed view of a vehicle was not successful. Reason: Vehicle was not found."));
    }

    try{
        cc.executeCommand("show 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Detailed view of a person was not successful. Reason: Person was not found."));
    }

    try{
        cc.executeCommand("show not-valid");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Detailed view of an object was not successful. Reason: Not valid id format."));
    }

    try{
        cc.executeCommand("show qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle [qw1234qw] with no owner. Description: description 1"));
    }

    try{
        cc.executeCommand("show 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person name 1 [123]. Vehicles(id): (none)"));
    }

    cc.executeCommand("acquire 123 qw1234qw");

    try{
        cc.executeCommand("show 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person name 1 [123]. Vehicles(id): (none)"));
    }

    try{
        cc.executeCommand("show qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle [qw1234qw] with owner name name 1 [123]. Description: description 1"));
    }

    try{
        cc.executeCommand("show 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person name 1 [123]. Vehicles(id): (none)"));
    }

}

TEST_CASE("ControlCenter :: vehicle <registration> <description>"){

    ControlCenter cc;

    std::string res;

    try{
        cc.executeCommand("vehicle");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: VEHICLE <registration> <description>"));
    }

    try{
        cc.executeCommand("vehicle qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: VEHICLE <registration> <description>"));
    }

    try{
        cc.executeCommand("vehicle invalid desc1");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle was not created. Reason: Invalid registration number."));
    }

    res = cc.executeCommand("vehicle qw1234qw desc1");
    REQUIRE (res == "");

    try{
        cc.executeCommand("vehicle qw1234qw desc2");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle was not created. Reason: Vehicle is not unique."));
    }

    res = cc.executeCommand("vehicle \"aa1234aa\" \"desc 1\"");
    REQUIRE (res == "");

}

TEST_CASE("ControlCenter :: person <name> <id>"){

    ControlCenter cc;

    std::string res;

    try{
        cc.executeCommand("person");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: PERSON <name> <id>"));
    }

    try{
        cc.executeCommand("person name");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: PERSON <name> <id>"));
    }

    try{
        cc.executeCommand("person name invalid");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person was not created. Reason: Invalid number format."));
    }

    try{
        cc.executeCommand("person");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: PERSON <name> <id>\n"));
    }

    try{
        cc.executeCommand("person");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: PERSON <name> <id>"));
    }

    cc.executeCommand("person name1 123");

    try{
        cc.executeCommand("person name2 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person was not created. Reason: Person is not unique."));
    }

    res = cc.executeCommand("person \"name 1\" \"3333\"");
    REQUIRE (res == "");

}


TEST_CASE("ControlCenter :: acquire <owner-id> <vehicle-id>"){

    ControlCenter cc;

    std::string res;

    cc.executeCommand("vehicle qw1234qw desc1");
    cc.executeCommand("person name1 123");

    try{
        cc.executeCommand("acquire");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: ACQUIRE <owner-id> <vehicle-id>"));
    }

    try{
        cc.executeCommand("acquire invalid");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: ACQUIRE <owner-id> <vehicle-id>"));
    }

    try{
        cc.executeCommand("acquire invalid qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully set. Reason: Invalid number format."));
    }

    try{
        cc.executeCommand("acquire 333 qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully set. Reason: Person was not found."));
    }

    try{
        cc.executeCommand("acquire 123 aa1111aa");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully set. Reason: Vehicle was not found."));
    }

    res = cc.executeCommand("acquire 123 qw1234qw");
    REQUIRE (res == "");

}

TEST_CASE("ControlCenter :: release <owner-id> <vehicle-id>"){

    ControlCenter cc;

    std::string res;

    cc.executeCommand("vehicle qw1234qw desc1");
    cc.executeCommand("person name1 123");
    cc.executeCommand("acquire 123 qw1234qw");

    try{
        cc.executeCommand("release");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: RELEASE <owner-id> <vehicle-id>"));
    }

    try{
        cc.executeCommand("release invalid");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: RELEASE <owner-id> <vehicle-id>"));
    }

    try{
        cc.executeCommand("release invalid qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully removed. Reason: Invalid number format."));
    }

    try{
        cc.executeCommand("release 333 qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully removed. Reason: Person was not found."));
    }

    try{
        cc.executeCommand("release 123 aa1111aa");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person's ownership of a vehicle was not successfully removed. Reason: Vehicle was not found."));
    }

    res = cc.executeCommand("release 123 qw1234qw");
    REQUIRE (res == "");

}

TEST_CASE("ControlCenter :: remove <what> (person, vehicle, undefined)"){

    ControlCenter cc;

    std::string res;

    cc.executeCommand("vehicle qw1234qw desc1");
    cc.executeCommand("person name1 123");

    try{
        cc.executeCommand("remove");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: REMOVE [<person-id>|<vehicle-id>]"));
    }

    try{
        cc.executeCommand("remove too many");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Incorrect use of command: REMOVE [<person-id>|<vehicle-id>]"));
    }

    try{
        cc.executeCommand("remove invalid");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Object removal was not successful. Reason: Not valid id format."));
    }

    try{
        cc.executeCommand("remove 333");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person removal was not successful. Reason: Person was not found."));
    }

    try{
        cc.executeCommand("remove aa1111aa");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle removal was not successful. Reason: Vehicle was not found."));
    }

    cc.executeCommand("remove 123");
    cc.executeCommand("remove qw1234qw");

    try{
        cc.executeCommand("remove 123");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Person removal was not successful. Reason: Person was not found."));
    }

    try{
        cc.executeCommand("remove qw1234qw");
    }catch(std::invalid_argument& e){
        REQUIRE ( approxStringCompare( e.what(), "Vehicle removal was not successful. Reason: Vehicle was not found."));
    }

}
