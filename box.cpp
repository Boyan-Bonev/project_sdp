#include "box.h"
#include <iostream>

void Box::print (std::ostream& os) const {
    if (!name.empty()) {
        os << name << " -> ";
        if (!souvenirs.empty()) {
            std::vector<std::string> copy = souvenirs;
            while (!copy.empty()) {
                os << copy.back() << ' ';
                copy.pop_back();
            }
            
        }
        if (!innerBoxes.empty()) {
            std::vector<Box*> boxesCopy = innerBoxes;
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
    std::vector<Box*>::iterator it = innerBoxes.begin();
    // continues the cycle after adding boxes when there is only a box
    while (it != innerBoxes.end()) {
    // the iterators go to random memory whenever they use erase() or push_back() 
    // so inconveniently it has to go to the beginning of the boxes everytime
    // it either removes an element 
    // or inserts a new one
        if ((*it)->empty()) {
            innerBoxes.erase(it);
            it = innerBoxes.begin();
            /*
            betterCase:
            innerBoxes.erase(it++);
            */
        }
        else if ((*it)->hasOnlyABox()) {
            // push back the only box the current innerBox has
            Box* toInsert = (*it)->innerBoxes.front();
            (*it)->innerBoxes.clear();
            innerBoxes.push_back ( toInsert );
            it = innerBoxes.begin();
            /*
            betterCase:
            innerBoxes.push_back((*it)->innerBoxes.front());
            innerBoxes.erase(it++);
            */

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
