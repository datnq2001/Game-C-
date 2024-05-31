#include "WoundedDeer.h"
#include <iostream>

// Constructor for WoundedDeer
WoundedDeer::WoundedDeer(const std::string &n, const std::string &d) : Character(n, d) {}

// Definition of the interact method for WoundedDeer
void WoundedDeer::interact() {
    std::cout << "The wounded deer says: 'Please find the healing mushroom that grows on the ancient tree facing the sunrise.'\n";
}
