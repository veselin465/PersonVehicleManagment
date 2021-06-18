#include "../PersonVehicleManagment/VehicleList.h"
#include "../PersonVehicleManagment/Vehicle.h"
#include "../PersonVehicleManagment/Person.h"

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

TEST_CASE("VehicleList :: add vehicle"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");
    Vehicle v4("qw3333qw", "desc 4");

    REQUIRE (vList.getVehicles().size() == 0);

    vList.addVehicle(v1);
    vList.addVehicle(v2);

    REQUIRE (vList.getVehicles()[1] == v2);

    vList.addVehicle(v3);
    vList.addVehicle(v4);

    REQUIRE (vList.getVehicles().size() == 4);
    REQUIRE (vList.getVehicles()[0] == v1);
    REQUIRE (vList.getVehicles()[3] == v4);

}

TEST_CASE("VehicleList :: find vehicle"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");
    Vehicle v4("qw3333qw", "desc 4");

    vList.addVehicle(v1);
    vList.addVehicle(v2);
    vList.addVehicle(v3);
    vList.addVehicle(v4);

    REQUIRE (vList.findVehicleByRegnum("qw1234qw") == v1);
    REQUIRE (vList.findVehicleByRegnum("qw2222qw") == v3);
    REQUIRE (vList.findVehicleByRegnum("qw3333qw") == v4);

    REQUIRE (vList.findVehicleByRegnum("qw1111qw") ==
             vList.getVehicles()[1]);

    REQUIRE_THROWS_AS (vList.findVehicleByRegnum("qw5555qw"), std::invalid_argument);

}

TEST_CASE("VehicleList :: remove vehicle"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");
    Vehicle v4("qw3333qw", "desc 4");

    vList.addVehicle(v1);
    vList.addVehicle(v2);
    vList.addVehicle(v3);
    vList.addVehicle(v4);

    REQUIRE (vList.getVehicles().size() == 4);

    vList.removeVehicleByRegnum("qw2222qw");
    REQUIRE (vList.getVehicles().size() == 3);

    vList.removeVehicleByRegnum("qw1234qw");
    REQUIRE (vList.getVehicles().size() == 2);

    REQUIRE_THROWS_AS (vList.removeVehicleByRegnum("qw5555qw"), std::invalid_argument);
    REQUIRE_THROWS_AS (vList.removeVehicleByRegnum("qw2222qw"), std::invalid_argument);

    REQUIRE (vList.getVehicles().size() == 2);

    vList.removeVehicleByRegnum("qw1111qw");

    REQUIRE (vList.getVehicles().size() == 1);
    REQUIRE (vList.getVehicles()[0] == v4);

}


TEST_CASE("VehicleList :: add vehicle - unique property"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");
    Vehicle v4("qw1234qw", "desc 4");

    vList.addVehicle(v1);
    vList.addVehicle(v2);

    REQUIRE_THROWS_AS (vList.addVehicle(v1), std::invalid_argument);

    vList.addVehicle(v3);

    REQUIRE_THROWS_AS (vList.addVehicle(v4), std::invalid_argument);

    vList.removeVehicleByRegnum("qw1234qw");

    vList.addVehicle(v4);

}

TEST_CASE("VehicleList :: set owner to a vehicle"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");

    Person p1(1111, "name1");
    Person p2(2222, "name2");

    vList.addVehicle(v1);
    vList.addVehicle(v2);

    vList.setOwner("qw1234qw", &p1);

    REQUIRE (vList.findVehicleByRegnum("qw1234qw").getOwner() == &p1);

    REQUIRE_THROWS_AS (vList.setOwner("qw2222qw", &p1), std::invalid_argument);

}

TEST_CASE("VehicleList :: remove owner from a vehicle"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");

    Person p1(1111, "name1");
    Person p2(2222, "name2");

    vList.addVehicle(v1);
    vList.addVehicle(v2);

    vList.removeOwner("qw1234qw");

    vList.setOwner("qw1234qw", &p1);

    REQUIRE (vList.findVehicleByRegnum("qw1234qw").getOwner() == &p1);

    vList.removeOwner("qw1234qw");

    REQUIRE (vList.findVehicleByRegnum("qw1234qw").getOwner() == nullptr);

    REQUIRE_THROWS_AS (vList.removeOwner("qw2222qw"), std::invalid_argument);

}

TEST_CASE("VehicleList :: get vehicles"){

    VehicleList vList;

    Vehicle v1("qw1234qw", "desc 1");
    Vehicle v2("qw1111qw", "desc 2");
    Vehicle v3("qw2222qw", "desc 3");

    Person p1(1111, "name1");

    vList.addVehicle(v1);
    vList.addVehicle(v2);
    vList.addVehicle(v3);

    vList.setOwner("qw1234qw", &p1);

    REQUIRE (vList.getVehicles()[0] == v1);
    REQUIRE (vList.getVehicles()[2] == v3);

    vList.removeVehicleByRegnum("qw1234qw");

    REQUIRE_FALSE (vList.getVehicles()[0] == v1);
    REQUIRE_FALSE (vList.getVehicles()[1] == v1);

}


