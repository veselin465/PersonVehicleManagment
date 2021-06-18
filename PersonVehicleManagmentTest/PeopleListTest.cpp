#include "../PersonVehicleManagment/PeopleList.h"
#include "../PersonVehicleManagment/Vehicle.h"
#include "../PersonVehicleManagment/Person.h"

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

TEST_CASE("PeopleList :: add person"){

    PeopleList pList;

    Person p1(111, "name1");
    Person p2(222, "name2");
    Person p3(333, "name3");

    pList.addPerson(p1);
    pList.addPerson(p2);

    REQUIRE (pList.getPeople().size() == 2);

    pList.addPerson(p3);

    REQUIRE (pList.getPeople().size() == 3);

    REQUIRE (pList.getPeople()[1] == p2);

}

TEST_CASE("PeopleList :: add person - unique property"){

    PeopleList pList;

    Person p1(111, "name1");
    Person p2(222, "name2");
    Person p3(111, "name3");

    pList.addPerson(p1);
    pList.addPerson(p2);

    REQUIRE_THROWS_AS (pList.addPerson(p1), std::invalid_argument);
    REQUIRE_THROWS_AS (pList.addPerson(p3), std::invalid_argument);

}

TEST_CASE("PeopleList :: remove person"){

    PeopleList pList;

    Person p1(111, "name1");
    Person p2(222, "name2");
    Person p3(333, "name3");

    pList.addPerson(p1);
    pList.addPerson(p2);
    pList.addPerson(p3);

    REQUIRE (pList.getPeople().size() == 3);

    pList.removePersonByUIN(222);
    REQUIRE (pList.getPeople().size() == 2);
    REQUIRE_THROWS_AS (pList.removePersonByUIN(222), std::invalid_argument);
    REQUIRE_THROWS_AS (pList.findPersonByUIN(222), std::invalid_argument);

    pList.removePersonByUIN(111);
    REQUIRE (pList.getPeople().size() == 1);
    REQUIRE_THROWS_AS (pList.findPersonByUIN(111), std::invalid_argument);

    REQUIRE_THROWS_AS (pList.removePersonByUIN(123), std::invalid_argument);

    // no throws with acquire
    Vehicle v1("qw1234qw", "desc 1");
    pList.acquireVehicle(333, &v1);
    pList.removePersonByUIN(333);

}


TEST_CASE("PeopleList :: find person"){

    PeopleList pList;

    Person p1(111, "name1");
    Person p2(222, "name2");
    Person p3(333, "name3");

    REQUIRE_THROWS_AS (pList.findPersonByUIN(111), std::invalid_argument);

    pList.addPerson(p1);
    pList.addPerson(p2);
    pList.addPerson(p3);

    pList.findPersonByUIN(111);   // no throw

    pList.removePersonByUIN(222);
    REQUIRE_THROWS_AS (pList.findPersonByUIN(222), std::invalid_argument);

    REQUIRE (pList.findPersonByUIN(111) == p1);
    REQUIRE (pList.findPersonByUIN(333) == p3);

}

TEST_CASE("PeopleList :: acquire vehicle"){

    PeopleList pList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");

    Person p1(1111, "name1");
    Person p2(2222, "name2");

    pList.addPerson(p1);
    pList.addPerson(p2);

    pList.acquireVehicle(1111, &v1);
    REQUIRE (pList.findPersonByUIN(1111).getVehicles()[0] == &v1);

    pList.acquireVehicle(1111, &v2);
    REQUIRE (pList.findPersonByUIN(1111).getVehicles()[1] == &v2);

    pList.acquireVehicle(2222, &v3);
    REQUIRE (pList.findPersonByUIN(2222).getVehicles()[0] == &v3);

    // not found
    REQUIRE_THROWS_AS (pList.acquireVehicle(1234, &v1), std::invalid_argument);

    // added vehicle doesnt belong to this person
    REQUIRE (pList.findPersonByUIN(1111).getVehicleCount() == 2);
    REQUIRE (pList.findPersonByUIN(2222).getVehicleCount() == 1);

}

TEST_CASE("PeopleList :: release vehicle"){

    PeopleList pList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");

    Person p1(1111, "name1");
    Person p2(2222, "name2");

    pList.addPerson(p1);
    pList.addPerson(p2);

    pList.acquireVehicle(1111, &v1);

    pList.releaseVehicle(1111, &v1);

    REQUIRE (pList.findPersonByUIN(1111).getVehicleCount() == 0);

    // releasing not acquire vehicle
    REQUIRE_THROWS_AS (pList.releaseVehicle(2222, &v1), std::invalid_argument);
    // releasing not existing person
    REQUIRE_THROWS_AS (pList.releaseVehicle(1234, &v1), std::invalid_argument);

}

TEST_CASE("PeopleList :: get people"){

    PeopleList pList;

    Person p1(1111, "name1");
    Person p2(2222, "name2");
    Vehicle v1("qw1234qw", "desc1");

    REQUIRE (pList.getPeople().size() == 0);

    pList.addPerson(p1);
    pList.addPerson(p2);

    pList.acquireVehicle(1111, &v1);

    REQUIRE (pList.getPeople().size() == 2);
    REQUIRE (pList.getPeople()[0] == p1);
    REQUIRE (pList.getPeople()[1] == p2);

}

