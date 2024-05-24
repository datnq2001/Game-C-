#ifndef ZOORK_VILLAGER_H
#define ZOORK_VILLAGER_H

#include "Character.h"

class Villager : public Character {
public:
    Villager(const std::string &n, const std::string &d);

    void interact() override;
};

#endif //ZOORK_VILLAGER_H
