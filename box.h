#ifndef __BOX_HPP
#define __BOX_HPP

#include <string>
#include <vector>
#include <list>

static const size_t MAX = 50;
class Box  {
    char name [MAX];
    std::vector<std::string> souvenirs;
    std::list<Box*> innerBoxes;
public:
    Box(std::string const& _name);
    Box() : name("No name") {}
    bool operator== (Box const& other) const;
    bool operator!= (Box const& other) const { return !(*this == other); }
    const char* getName() const {return name;}
    void print (std::ostream& os = std::cout) const;
    void addSouvenir(std::string const& souvenirName) { souvenirs.push_back(souvenirName); }
    Box* findBox (std::vector<Box>& boxes);
    void insertBox (Box& boxName) { 
        Box* toInsert = &boxName;
        innerBoxes.push_back(toInsert);
    }
    bool empty() const { return souvenirs.empty() && innerBoxes.empty(); }
    bool hasOnlyABox () const { return souvenirs.empty() && innerBoxes.size() == 1; }
    bool usefulBox () const { return !souvenirs.empty() || innerBoxes.size() > 1; }
    
    void removeUselessBoxes (std::vector<Box>& boxes);
    void optimize (std::vector<Box>& boxes, std::ostream& os = std::cout) { 
        removeUselessBoxes(boxes);
        print(os);
    }
};

#include "box.cpp"

#endif