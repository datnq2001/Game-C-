#ifndef ZOORK_KEY_H
#define ZOORK_KEY_H

#include "Item.h"

// Key class inherits from Item
class Key : public Item {
public:
    // Constructor for the Key class
    Key(const std::string &n, const std::string &d, int quantity = 1, int price = 0) : Item(n, d, quantity, price) {}
};

#endif //ZOORK_KEY_H
