#include "../PersonVehicleManagment/Registration.h"

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

TEST_CASE("Registration :: rule of 3"){

    // constructors and operator=
    Registration reg1("AA1234AA");
    Registration copy1(reg1);
    Registration copy2 = reg1;
    Registration reg2 = Registration("BB1234BB");

    // operator ==
    REQUIRE (reg1 == "AA1234AA");
    REQUIRE (reg1 == copy1);
    REQUIRE (copy1 == reg1);
    REQUIRE_FALSE (reg2 == "AA1234AA");
    REQUIRE_FALSE (reg2 == reg1);
    REQUIRE_FALSE (reg2 == copy1);

    const char* regnum_c_str = reg1.getNumber();

    REQUIRE (reg1 == regnum_c_str);
    REQUIRE_FALSE (reg2 == regnum_c_str);
    REQUIRE (strlen(regnum_c_str) == 8);
}

TEST_CASE ("Registration :: invalid argument"){

    REQUIRE_THROWS_AS (Registration("1234AA"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("1234AAAA"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("AA1234"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("AA1234A"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("A1234"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("A1234AAA"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("AAA1234A"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("AAAA1234"), std::invalid_argument);

    REQUIRE_THROWS_AS (Registration("AA1234A@"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("AA1_34AA"), std::invalid_argument);
    REQUIRE_THROWS_AS (Registration("A.1234AA"), std::invalid_argument);


    //the following should NOT throw exceptions
    Registration("AB1839YZ");
    Registration("AA0000AA");
    Registration("A1234AA");
    Registration("ZZ9999ZZ");
    Registration("Z7890ZZ");


    Registration reg("AA1234AA");
    REQUIRE ((std::string) "AA1234AA" == reg.getNumber());


}

