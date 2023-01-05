
#include "doctest.h"
#include "skipList.h"
#include <string>

TEST_CASE("SkipList Function Tests") {
    SkipList<int> list;
    for (int i = 1; i <= 10; i++) {
        list.insertLast(i);
    }
    SUBCASE("deleteFirst test") {
        int i = 1;
        int deleted;
        for (; i <= 10; i++) {
            deleted = list.deleteFirst();
            CHECK_EQ(deleted,i);
        }
        CHECK(i == 11);
    }
    SUBCASE("deleteLast test") {
        int i = 10;
        int deleted;
        for (; i >= 1; i--) {
            deleted = list.deleteLast();
            CHECK_EQ(deleted,i);
        }
        CHECK(i == 0);
    }
    SUBCASE("deleteAfter test") {
        Iterator<int> it = list.begin();
        int deleted;
        int i = 2;
        // 1 3  5 6 7 8 9 10
        for (it; it.valid() && it.next().valid() ; it++) {
            deleted = list.deleteAfter(it);
            CHECK_EQ(deleted,i);
            i += 2;
        }
        CHECK(!it.valid());
    }
    SUBCASE("insertAfter test") {
        Iterator<int> it = list.begin();
        int deleted;
        // 1 1 2 2 3 3 4 4 5 6 7 8 9 10
        for (int i = 1; i <= 10; i ++) {
            list.insertAfter(it,i);
            it++; it++;
        }
        CHECK(!it.valid());
        it = list.begin();
        int numbers [20];
        for (int i = 0; i < 10; i++ ) {
            numbers[2*i + 0] = i + 1;
            numbers[2*i + 1] = i + 1;
        }
        int i = 0;
        for (it; it.valid(); it++) {
            REQUIRE(it.get() == numbers[i]);
            i++;
        }
    }
    SUBCASE("Skipping test") {
        Iterator<int> from = list.begin();
        Iterator<int> to = list.begin(); to++; to++; // 2 forwards (1 -> 3, 3 -> 5, 5 -> 7, 7 -> 9)
        for (int i = 1; i < 5; i ++) {
            CHECK(list.addSkip(from,to));
            from = to;
            to++; to++;
        }
        from = list.begin();
        to = list.begin(); to++; to++;
        for (from;from.valid();) {
            if (from.get() == 1 || from.get() == 3 || from.get() == 5 || from.get() == 7) {
                CHECK(list.useSkip(from));
                CHECK(from == to);
                to++; to++;
            }
            else {
                CHECK(!list.useSkip(from));
                if (from.get() == 9 || from.get() == 10) {
                    CHECK(true);
                }
                else {
                    CHECK(false);
                }
                from++;
            }
        }
    }
    SUBCASE("Finding elements") {
        Iterator<int> compare = list.begin(); 
        Iterator<int> foundElem;
        for (int i = 1; i <= 10; i++) {
            foundElem = list.findElem(i);
            REQUIRE(foundElem == compare);
            compare++;
        }
    }
}

TEST_CASE ("Shortest route") {
    SkipList<std::string> route;
    route.insertLast("Sofia");
    route.insertLast("Pazardzhik");
    route.insertLast("Plovdiv");
    route.insertLast("Dimitrovgrad");
    route.insertLast("StaraZagora");
    route.insertLast("NovaZagora");
    route.insertLast("Yambol");
    route.insertLast("Karnobat");
    route.insertLast("Burgas");

    Iterator<std::string> from = route.findElem("Sofia");
    Iterator<std::string> to = route.findElem("Plovdiv");
    REQUIRE(from.valid());
    REQUIRE(to.valid());
    route.addSkip(from,to);

    from = route.findElem("Plovdiv");
    to = route.findElem("NovaZagora");
    REQUIRE(from.valid());
    REQUIRE(to.valid());
    route.addSkip(from,to);

    from = route.findElem("Dimitrovgrad");
    to = route.findElem("NovaZagora");
    REQUIRE(from.valid());
    REQUIRE(to.valid());
    route.addSkip(from,to);

    from = route.findElem("StaraZagora");
    to = route.findElem("Yambol");
    REQUIRE(from.valid());
    REQUIRE(to.valid());
    route.addSkip(from,to);

    from = route.findElem("NovaZagora");
    to = route.findElem("Burgas");
    REQUIRE(from.valid());
    REQUIRE(to.valid());
    route.addSkip(from,to);

    Iterator<std::string>& toVisit = from;
    toVisit = route.findElem("Plovdiv");
    toVisit.addVisit();
    toVisit = route.findElem("StaraZagora");
    toVisit.addVisit();
    toVisit = route.findElem("Yambol");
    toVisit.addVisit();

    SkipList<std::string> bestRoute = route.findShortestRoute();
    Iterator<std::string>& currLocation = to;
    currLocation = bestRoute.begin();
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Sofia");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Plovdiv");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Dimitrovgrad");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "StaraZagora");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Yambol");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Karnobat");
    currLocation++;
    REQUIRE(currLocation.valid());
    CHECK(currLocation.get() == "Burgas");
    currLocation++;
    CHECK(!currLocation.valid());
}
