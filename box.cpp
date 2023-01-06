#include "box.h"

void Box::removeUselessBoxes () {
    if (innerBoxes.empty()) {
        return;
    }
    std::vector<Box>::iterator it = innerBoxes.begin();
    /*
    continues the cycle after adding boxes when there is only a box
    */
    while (it != innerBoxes.end()) {
        if ((*it).empty())
            // deletes current and moves to the next
            it =innerBoxes.erase(it);
        else if ((*it).hasOnlyABox()) {
            // push back the only box the current innerBox has
            innerBoxes.push_back ( (*it).innerBoxes.front() );
            // deletes current and moves to the next
            it = innerBoxes.erase(it);
        }
        else {
            // goes deeper into the box because it has more than one box and isn't empty
            (*it).removeUselessBoxes();
            // if after clearing the useless boxes, the box is still useful
            //                                has a souvenir or more than 2 useful boxes
            // then move to the next box
            // else check again if its empty or has a single box
            if ((*it).usefulBox())
                it++;
        }
    }
}
