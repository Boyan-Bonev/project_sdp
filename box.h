#ifndef __BOX_HPP
#define __BOX_HPP

#include <string>
#include <vector>

class Box  {
    std::string name;
    std::vector<std::string> souvenirs;
    std::vector<Box> innerBoxes;
public:
    Box(std::string const& _name) : name(_name) {}
    std::string getName() const {return name;}
    void addSouvenir(std::string const& souvenirName) { souvenirs.push_back(souvenirName); }
    void insertBox (Box const& boxName) { innerBoxes.push_back(boxName); }
    bool empty() const { return souvenirs.empty() && innerBoxes.empty(); }
    bool hasOnlyABox () const { return souvenirs.empty() && innerBoxes.size() == 1; }
    bool usefulBox () const { return !souvenirs.empty() || innerBoxes.size() > 1; }
    
    void removeUselessBoxes ();
};

#include "box.cpp"

#endif