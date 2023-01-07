#include "box.h"
#include <iostream>


Box::Box(std::string const& _name) {
    const char* __name = _name.data();
    int i = 0;
    for (i; __name[i] != '\0' || i == MAX - 1; i++) {
        name[i] = __name[i];
    }
    name[i] = '\0';
}

bool Box::operator== (Box const& other) const {
    int i = 0;
    while (name[i] != '\0') {
        if (name[i] != other.name[i]) {
            return false;
        }
        i++;
    }
    return other.name[i] == '\0';
}

void Box::print (std::ostream& os) const {
    if (name != "No name") {
        os << name << " -> ";
        if (!souvenirs.empty()) {
            std::vector<std::string> copy = souvenirs;
            while (!copy.empty()) {
                os << copy.back() << ' ';
                copy.pop_back();
            }
            
        }
        if (!innerBoxes.empty()) {
            std::list<Box*> boxesCopy = innerBoxes;
            while (!boxesCopy.empty()) {
                os << "( ";
                boxesCopy.back()->print(os);
                os << ") ";
                boxesCopy.pop_back();
            }
        }
    }
}

void Box::removeUselessBoxes () {
    if (innerBoxes.empty()) {
        return;
    }
    std::list<Box*>::iterator it = innerBoxes.begin();
    std::list<Box*>::iterator save;
    // continues the cycle after adding boxes when there is only a box
    while (it != innerBoxes.end()) {
        if ((*it)->empty()) {
            it = innerBoxes.erase(it);
        }
        else if ((*it)->hasOnlyABox()) {
            Box* toInsert = (*it)->innerBoxes.front();
            (*it)->innerBoxes.clear();
            // save the location of the iterator 
            save = it;
            // push back the only box the current innerBox has
            innerBoxes.push_back ( toInsert );
            // go back to the location
            it = save;
            it = innerBoxes.erase(it);
        }
        else {
            // goes deeper into the box because it has more than one box and isn't empty
            (*it)->removeUselessBoxes();
            // if after clearing the useless boxes, the box is still useful
            //                                (has a souvenir or more than 2 useful boxes)
            // then move to the next box
            // else check again if its empty or has a single box
            if ((*it)->usefulBox())
                it++;
        }
    }
}
