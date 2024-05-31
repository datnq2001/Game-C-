#ifndef ZOORK_WOUNDEDDEER_H
#define ZOORK_WOUNDEDDEER_H

#include "Character.h"

// The WoundedDeer class represents a character in the game.
class WoundedDeer : public Character {
public:

    // Constructor for the WoundedDeer class. Initializes the deer with a name and description.
    WoundedDeer(const std::string &n, const std::string &d);

    // Method to interact with the deer.
    void interact() override;

};

#endif //ZOORK_WOUNDEDDEER_H
