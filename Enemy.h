#ifndef ZOORK_ENEMY_H
#define ZOORK_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy(const std::string &n, const std::string &d, int health, int attack);

    void interact() override;
};

#endif //ZOORK_ENEMY_H
