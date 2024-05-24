// Key.h
#ifndef ZOORK_KEY_H
#define ZOORK_KEY_H

#include "Item.h"

class Key : public Item {
public:
    Key(const std::string &n, const std::string &d) : Item(n, d) {}
};

#endif //ZOORK_KEY_H