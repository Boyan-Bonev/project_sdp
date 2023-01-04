#include "skipList.h"
#include <string>
#include <iostream>

using std::cout;
using std::cin;

int main () {
    int n = 0;
    cout << "Number of towns that the train passes: ";
    cin >> n;

    cout << "Town names: ";
    char input = ' ';
    std::string townName;
    SkipList<std::string> route;

    while (input != '\n') {
        cin.get(input);
        if (input == ' ') {
            route.insertLast(townName);
            townName.clear();
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
    SkipList<std::string> townsToBeVisited;
    while (input != '\n') {
        cin.get(input);
        if (input == ' ') {
            townsToBeVisited.insertLast(townName);
            townName.clear();
        }
        else {
            townName.push_back(input);
        }
    }
    route.insertLast(townName);
    townName.clear();

    //SkipList<std::string> shortestRoute = route.findShortestRoute(townsToBeVisited);
    return 0;
}
