#include "doctest.h"
#include "graph.h"
#include <string>
#include <iostream>

TEST_CASE ("Basic functions test") {
    Graph* test = new Graph("Plovdiv.txt");
    int railstation = test->findVertIdx("Railstation");
    REQUIRE(railstation == 0);
    REQUIRE(test->getSize() == 6);
    REQUIRE(test->timeToExplore == 68);
    CHECK(test->shortestPath(0,0) == 0);
    CHECK(test->shortestPath(0,1) == 26);
    CHECK(test->shortestPath(0,2) == 20);
    CHECK(test->shortestPath(0,3) == 22);
    CHECK(test->shortestPath(0,4) == 40);
    CHECK(test->shortestPath(0,5) == 33);
    std::ostringstream os;
    test->bestTravel("Railstation",os);
    CHECK_EQ(os.str(),"Railstation RomanStadium DzhumayaSquare ArtGallery AntiqueTheatre ArtGallery Railstation\n");
    std::ostringstream os1;
    test->visitMost(false,0,0,30,1,os1);
    CHECK_EQ(os1.str(),"Railstation \n");
    std::ostringstream os2;
    test->bestTravel("HistoricalMuseum",os2);
    CHECK_EQ(os2.str(),"HistoricalMuseum AntiqueTheatre ArtGallery DzhumayaSquare RomanStadium DzhumayaSquare HistoricalMuseum\n");
}
