#include "../PersonVehicleManagment/Vehicle.h"
#include "../PersonVehicleManagment/Person.h"

#include "catch_amalgamated.hpp"

TEST_CASE ("Person :: rule of 3"){

    Person p1(1234, "qwer");
    Person p2(p1);
    Person p3 = p1;
    Person p4(1000, "qwer");

    REQUIRE (p1.getUIN() == p2.getUIN());
    REQUIRE (p1.getUIN() == p3.getUIN());
    REQUIRE (p2.getUIN() == p3.getUIN());
    REQUIRE (p1 == p3);

    REQUIRE_FALSE (p1 == p4);
    REQUIRE_FALSE (p2.getUIN() == p4.getUIN());
    REQUIRE_FALSE (p3 == 1000);

}

TEST_CASE ("Person :: get vehicle count"){

    Vehicle v1("qw1111qw", "desc 1");
    Vehicle v2("qw2222qw", "desc 2");
    Vehicle v3("qw3333qw", "desc 3");

    Person p1(1111, "qwer1");
    Person p2(2222, "qwer2");
    Person p3(3333, "qwer3");
    REQUIRE (p1.getVehicleCount() == 0);

    p1.acquireVehicle(&v1);
    p1.acquireVehicle(&v2);
    p1.acquireVehicle(&v3);
    REQUIRE (p1.getVehicleCount() == 3);

    p2.acquireVehicle(&v1);
    p2.acquireVehicle(&v3);
    REQUIRE (p2.getVehicleCount() == 2);

    p3.acquireVehicle(&v2);
    REQUIRE (p3.getVehicleCount() == 1);

}

TEST_CASE ("Person :: get UIN"){
    Person p1(1111, "qwer1");
    Person p2(2222, "qwer2");
    REQUIRE (p1.getUIN() == 1111);
    REQUIRE (p2.getUIN() == 2222);
}

TEST_CASE ("Person :: get name"){
    Person p1(1111, "qwer1");
    Person p2(2222, "qwer2wqeeqweqweqewqwe");
    REQUIRE (p1.getName() == (std::string)"qwer1");
    REQUIRE (p2.getName() == (std::string)"qwer2wqeeqweqweqewqwe");
}

TEST_CASE ("Person :: get vehicles"){

    Vehicle v1("qw1111qw", "desc 1");
    Vehicle v2("qw2222qw", "desc 2");
    Vehicle v3("qw3333qw", "desc 3");

    Person p1(1111, "qwer1");

    p1.acquireVehicle(&v1);
    p1.acquireVehicle(&v2);
    p1.acquireVehicle(&v3);

    REQUIRE ((*p1.getVehicles()[1]) == v2);
    REQUIRE_FALSE ((*p1.getVehicles()[1]) == v1);

}

TEST_CASE ("Person :: acquire vehicle - unique property"){

    Vehicle v1("qw1111qw", "desc 1");
    Vehicle v2("qw2222qw", "desc 2");
    Vehicle v3("qw1111qw", "desc 3");

    Person p1(1111, "qwer1");

    p1.acquireVehicle(&v1);
    p1.acquireVehicle(&v2);
    REQUIRE_THROWS_AS (p1.acquireVehicle(&v3), std::invalid_argument);
    REQUIRE_THROWS_AS (p1.acquireVehicle(&v2), std::invalid_argument);

    REQUIRE (p1.getVehicleCount() == 2);

}

TEST_CASE ("Person :: release vehicle - find and delete property"){

    Vehicle v1("qw1111qw", "desc 1");
    Vehicle v2("qw2222qw", "desc 2");
    Vehicle v3("qw1111qw", "desc 3");

    Person p1(1111, "qwer1");

    p1.acquireVehicle(&v1);
    p1.acquireVehicle(&v2);

    p1.releaseVehicle(&v1);

    REQUIRE (p1.getVehicleCount() == 1);

    REQUIRE_THROWS_AS (p1.releaseVehicle(&v1), std::invalid_argument);
    REQUIRE_THROWS_AS (p1.releaseVehicle(&v3), std::invalid_argument);

    REQUIRE (p1.getVehicleCount() == 1);

    p1.releaseVehicle(&v2);

    REQUIRE (p1.getVehicleCount() == 0);

}
