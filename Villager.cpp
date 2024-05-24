#include "Villager.h"
#include <iostream>

Villager::Villager(const std::string &n, const std::string &d) : Character(n, d) {}

void Villager::interact() {
    std::cout << "The villager says: 'Hello, traveler! Welcome to our village.'\n";
}
