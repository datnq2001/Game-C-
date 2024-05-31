#include "Enemy.h"
#include <iostream>

// Constructor for the Enemy class. Initializes the enemy with a name, description, health, and attack values.
Enemy::Enemy(const std::string &n, const std::string &d, int health, int attack)
    : Character(n, d) {
    this->health = health;
    this->attack = attack;
}

// Method to handle interaction with the enemy.
void Enemy::interact() {
    std::cout << "The enemy attacks you!\n";
}
