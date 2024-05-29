#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string &n, const std::string &d, int health, int attack)
    : Character(n, d) {
    this->health = health;
    this->attack = attack;
}

void Enemy::interact() {
    std::cout << "The enemy attacks you!\n";
}
