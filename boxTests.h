#include "doctest.h"
#include "box.h"
#include "readBoxes.cpp"
#include <string>

TEST_CASE("Optimizing test with input command") {
    /*
    MainBox -> 
    ( PlovdivBox -> Book Magnet ( Plates -> DecorativePlate ) ( Drawings -> OldPlovdiv ) ) 
    ( Drawings -> OldPlovdiv ) 
    ( Plates -> DecorativePlate ) 
    ( StaraZagoraBox -> Postcard ( Cups -> TraditionalCup ) ( Figurines -> AncientFigurine ) ) 
    ( Figurines -> AncientFigurine ) 
    ( Cups -> TraditionalCup ) 
    */
    std::vector<Box> boxes;
    Box* result = readBoxes("boxesList.txt", boxes);
    std::ostringstream os;
    (*result).optimize(boxes,os);
    std::string answer = os.str();
    // Split into 2 because == only takes 200 elems
    CHECK_EQ(answer.substr(0,199), "( PlovdivBox -> Book Magnet ( Plates -> DecorativePlate ) ( Drawings -> OldPlovdiv ) ) ( Drawings -> OldPlovdiv ) ( Plates -> DecorativePlate ) ( StaraZagoraBox -> Postcard ( Cups -> TraditionalCup )");
    CHECK_EQ(answer.substr(200), "( Figurines -> AncientFigurine ) ) ( Figurines -> AncientFigurine ) ( Cups -> TraditionalCup ) ");
}   


