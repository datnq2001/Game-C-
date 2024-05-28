#include "WoundedDeer.h"
#include <iostream>

WoundedDeer::WoundedDeer(const std::string &n, const std::string &d) : Character(n, d) {}

void WoundedDeer::interact() {
    std::cout << "The wounded deer says: 'Please find the healing mushroom that grows on the ancient tree facing the sunrise.'\n";
}
