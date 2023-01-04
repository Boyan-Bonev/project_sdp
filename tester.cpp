#include <iostream>
#include "linkedList.h"
template <typename T>
class Boo {
    int data;
    public:
    operator int() {return 21;}
    Boo(int x) : data(x) {}
};

class Hey {
    int data;
    public:
    operator Boo<int>() {return Boo<int>(2);}
};

int main () {
    Hey hhh;
    LinkedList<int> t;
    std::cout << (Boo<int>)hhh;
}