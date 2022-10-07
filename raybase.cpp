#include "raybase.h"

void BaseRay::print() const {
    std::cout << "\tposition: \n";
    position.print();
    std::cout << "\tdirection: \n";
    direction.print();
}