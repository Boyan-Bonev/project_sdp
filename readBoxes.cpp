#include <iostream>
#include <fstream>
#include <vector>
#include "box.h"
/*
първия ред положително естествено число b - всички кутии, 
а на всеки от следващите b реда всяка от кутиите
уникален надпис на кутия, броя на сувенирите в нея, имената на тези сувенири, броя кутии и техните надписи 
всички разделени с по един интервал.
*/

Box* findBox(std::vector<Box>& boxes, std::string& name) {
    Box curr = Box(name);
    unsigned size = boxes.size() - 1;
    for (; size != -1; size--) {
        if (boxes[size] == curr) {
            return &boxes[size];
        }
    }
    return nullptr;
}

Box* readBoxes(std::string const& fileName, std::vector<Box>& boxes) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error ("Couldn't open file");
    }
    std::string line;
    std::getline(file,line,'\n');
    int rows = std::stoi(line);
    if (rows == 0) {
        return nullptr;
    }
    boxes.reserve(rows);
    
    Box* pMainBox = new Box("MainBox"), *toInsert;
    std::string currElem, currBoxName;
    bool enteredBoxName = false, enteredSouvenirsAmount = false, enteredBoxesAmount = false;
    int pos, souvenirsAmount = 0;
    while (rows != 0) {
        line.clear();
        std::getline(file,line);
        Box* pCurrBox = nullptr;
        souvenirsAmount = 0;
        enteredBoxName = false;
        enteredSouvenirsAmount = false;
        enteredBoxesAmount = false;
        while (!line.empty()) {
            while ( ( ( pos = line.find( ' ' ) ) != std::string::npos  ) || (!line.empty())) {
                if (pos == -1) {
                    currElem = line;
                    line.erase();
                }
                else {
                    currElem = line.substr(0,pos);
                    line.erase(0,pos+1);
                }

                if (!enteredBoxName) {
                    currBoxName = currElem;
                    pCurrBox = findBox(boxes,currElem);
                    if (!pCurrBox) {
                        boxes.push_back(Box(currElem));
                        pCurrBox = &boxes.back();
                    }
                    enteredBoxName = true;
                }

                else if (!enteredSouvenirsAmount) {
                    souvenirsAmount = std::stoi(currElem);
                    enteredSouvenirsAmount = true;
                }

                else if (souvenirsAmount != 0) {
                    souvenirsAmount--;
                    pCurrBox->addSouvenir(currElem);
                }

                else if (!enteredBoxesAmount) 
                    enteredBoxesAmount = true;
                    
                else {
                    toInsert = findBox(boxes,currElem);
                    if (!toInsert) {
                        boxes.push_back(Box(currElem));
                        pCurrBox = findBox(boxes,currBoxName);
                        pCurrBox->insertBox(boxes.back());
                    }
                    else {
                        pCurrBox->insertBox(*toInsert);
                    }
                }
		    }
        }
        rows--;
    }

    file.close();
    int i = boxes.size() - 1;
    while (i >= 0) {
        pMainBox->insertBox(boxes[i]);
        i--;
    }
    return pMainBox;
}