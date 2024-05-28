#ifndef ZOORK_MUSHROOM_H
#define ZOORK_MUSHROOM_H

#include "Item.h"

class Mushroom : public Item {
public:
    Mushroom(const std::string &n, const std::string &d, int quantity = 1) : Item(n, d, quantity) {}
};

#endif //ZOORK_MUSHROOM_H
