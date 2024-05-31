#ifndef ZOORK_WEAPON_H
#define ZOORK_WEAPON_H

#include "Item.h"

// The Weapon class represents a special item in the game.
class Weapon : public Item {
public:

    // Constructor for the Weapon class. Initializes the item with a name, description, quantity, price, and attack.
    Weapon(const std::string &n, const std::string &d, int quantity = 1, int price = 0, int attack = 0)
        : Item(n, d, quantity, price, attack) {}

    // Override the use method to display a message when the weapon is used.
    void use() override {
        std::cout << "You equipped the " << getName() << ". Your attack increased by " << getAttack() << ".\n\n";
    
    }
};

#endif //ZOORK_WEAPON_H
