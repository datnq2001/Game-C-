#include "Character.h"

Character::Character(const std::string &n, const std::string &d)
    : GameObject(n, d), health(100), attack(10), move(5), initiative(1) {}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int health) {
    this->health = health;
}

int Character::getAttack() const {
    return attack;
}
