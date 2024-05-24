#include "Merchant.h"
#include <iostream>

Merchant::Merchant(const std::string &n, const std::string &d) : Character(n, d) {}

void Merchant::interact() {
    std::cout << "The merchant says: 'Care to trade? I have many goods to offer.'\n";
}
