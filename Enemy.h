#ifndef ZOORK_ENEMY_H
#define ZOORK_ENEMY_H

#include "Character.h"

// The Enemy class represents an enemy character in the game.
class Enemy : public Character {
public:
    // Constructor for the Enemy class. Initializes the enemy with a name, description, health, and attack values.
    Enemy(const std::string &n, const std::string &d, int health, int attack);

    // Override the interact method to define enemy-specific interaction behavior.
    void interact() override;
};

#endif //ZOORK_ENEMY_H
