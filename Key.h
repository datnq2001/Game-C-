#ifndef ZOORK_KEY_H
#define ZOORK_KEY_H

#include "Item.h"

class Key : public Item {
public:
    Key(const std::string &n, const std::string &d, int quantity = 1) : Item(n, d, quantity) {}
};

#endif //ZOORK_KEY_H
