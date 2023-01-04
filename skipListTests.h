
#include "doctest.h"
#include "skipList.h"

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
