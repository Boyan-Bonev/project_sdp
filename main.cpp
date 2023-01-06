#include "skipList.h"
#include <string>
#include <iostream>
//#include "box.h"
#include <fstream>

using std::cout;
using std::cin;

// Suppossed input
// 12                                                   amount of towns
// Town1 Town2 Town3 ... Town 12                         towns
// Town1 Town3                                          skip
// Town4 Town8                                          skip
// Town5 Town 12.                                       skip
// Town3 Town 5 Town 6                                  toVisit

SkipList<std::string> shortestRoute (SkipList<std::string>& route) {
    int n = 0;
    cout << "Number of towns that the train passes: ";
    cin >> n;

    cout << "Town names: ";
    char input = ' ';
    std::string townName;

    while (input != '\n' || n == 0) {
        cin.get(input);
        if (input == ' ') {
            route.insertLast(townName);
            townName.clear();
            n--;
        }
        else {
            townName.push_back(input);
        }
    }
    route.insertLast(townName);
    townName.clear();

    cout << "/Insert . to stop entering/ Direct Connections: ";
    input = ' ';
    std::string from, to;
    Iterator<std::string> iterFrom, iterTo;
    while (input != '.') {
        cin.get(input);
        switch (input) {
            case '\n' : {
                iterTo = route.findElem(to);
                to.clear();
                route.addSkip(iterFrom,iterTo);
                iterFrom.nulify();
                iterTo.nulify();
            }
            case ' ' : {
                iterFrom = route.findElem(from);
                from.clear();
            }
            default : {
                if (iterFrom.valid()) {
                    to.push_back(input);
                }
                else {
                    from.push_back(input);
                }
            }
        }
    }
    if (iterFrom.valid()) {
        iterTo = route.findElem(to);
        to.clear();
        route.addSkip(iterFrom,iterTo);
        iterFrom.nulify();
        iterTo.nulify();
    }

    cout << "To be visited: ";
    input = ' ';
    Iterator<std::string> visit;
    while (input != '\n') {
        cin.get(input);
        if (input == ' ') {
            visit = route.findElem(townName);
            visit.addVisit();
            townName.clear();
        }
        else {
            townName.push_back(input);
        }
    }
    route.insertLast(townName);
    townName.clear();
    return route.findShortestRoute();
}

int main () {
    SkipList<std::string> route;
    SkipList<std::string> result = shortestRoute(route);
    result.print();
}
