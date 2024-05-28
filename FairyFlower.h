#ifndef ZOORK_FAIRYFLOWER_H
#define ZOORK_FAIRYFLOWER_H

#include "Item.h"

class FairyFlower : public Item {
public:
    FairyFlower(const std::string &n, const std::string &d, int quantity = 1, int price = 199)
        : Item(n, d, quantity, price) {}
};

#endif //ZOORK_FAIRYFLOWER_H
