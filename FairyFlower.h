#ifndef ZOORK_FAIRYFLOWER_H
#define ZOORK_FAIRYFLOWER_H

#include "Item.h"

// The FairyFlower class represents a special item in the game.
class FairyFlower : public Item {
public:
    // Constructor for the FairyFlower class. Initializes the item with a name, description, quantity, and price.
    FairyFlower(const std::string &n, const std::string &d, int quantity = 1, int price = 199)
        : Item(n, d, quantity, price) {}
};

#endif //ZOORK_FAIRYFLOWER_H
