#include "OtherLegendaryCharacters.h"
#include <iostream>

// Constructor for OtherLegendaryCharacters, calls the base class Character constructor
OtherLegendaryCharacters::OtherLegendaryCharacters(const std::string &n, const std::string &d) 
    : Character(n, d) {}

// Definition of the interact method for OtherLegendaryCharacters
void OtherLegendaryCharacters::interact() {
    std::cout << "The legendary character says: 'Greetings, traveler. You have encountered a being of great power.'\n";
}
