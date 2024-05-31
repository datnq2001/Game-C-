#ifndef ZOORK_WEAPON_H
#define ZOORK_WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    Weapon(const std::string &n, const std::string &d, int quantity = 1, int price = 0, int attack = 0)
        : Item(n, d, quantity, price, attack) {}

    void use() override {
        std::cout << "You equipped the " << getName() << ". Your attack increased by " << getAttack() << ".\n";
    }
};

#endif //ZOORK_WEAPON_H
