#include "../PersonVehicleManagment/Vehicle.h"
#include "../PersonVehicleManagment/Person.h"
#include "../PersonVehicleManagment/Registration.h"

#include "catch_amalgamated.hpp"

TEST_CASE ("Vehicle :: rule of 3"){

    // constructors and operator=
    Vehicle veh1("AA1234AA", "Desc 1");

    Vehicle copy1(veh1);
    Vehicle copy2 = veh1;

    Registration reg1 = "BB1234BB";
    const char* reg1_c_str = reg1.getNumber();
    const char* regA = "AA1234AA";

    Vehicle veh2 (reg1_c_str, "Desc 2");

    // operator ==
    REQUIRE (veh1 == regA);
    REQUIRE (veh1 == copy1);
    REQUIRE (copy1 == veh1);
    REQUIRE (veh2 == reg1);
    REQUIRE_FALSE (veh2 == "ZZ1234ZZ");
    REQUIRE_FALSE (veh2 == veh1);
    REQUIRE_FALSE (veh2 == copy1);

}

TEST_CASE ("Vehicle :: owner functionality"){

    Vehicle v("AA1234AA", "dess 1");
    REQUIRE (v.getOwner() == nullptr);

    Person p(1234, "name");

    v.setOwner(&p);
    REQUIRE (v.getOwner() != nullptr);

    v.removeOwner();
    REQUIRE (v.getOwner() == nullptr);

}

TEST_CASE ("Vehicle :: Registration number validation"){

    // basically, all the tests from Registration :: invalid argument - still should be tested

    REQUIRE_THROWS_AS (Vehicle("1234AA", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("1234AAAA", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("AA1234", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("AA1234A", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("A1234", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("A1234AAA", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("AAA1234A", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("AAAA1234", "Desc"), std::invalid_argument);

    REQUIRE_THROWS_AS (Vehicle("AA1234A@", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("AA1_34AA", "Desc"), std::invalid_argument);
    REQUIRE_THROWS_AS (Vehicle("A.1234AA", "Desc"), std::invalid_argument);


    //the following should NOT throw exceptions
    Vehicle("AB1839YZ", "Desc");
    Vehicle("AA0000AA", "Desc");
    Vehicle("A1234AA", "Desc");
    Vehicle("ZZ9999ZZ", "Desc");
    Vehicle("Z7890ZZ", "Desc");

}
