#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string &n, const std::string &d) : Character(n, d) {}

void Enemy::interact() {
    std::cout << "The enemy attacks you!\n";
}
