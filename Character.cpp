#include "Character.h"

// Constructor for the Character class, initializing the character with a name, description, 
// and default values for health, attack, move, and initiative.
Character::Character(const std::string &n, const std::string &d)
    : GameObject(n, d), health(100), attack(10), move(5), initiative(1) {}

// Getter method for the health attribute. Returns the current health of the character.
int Character::getHealth() const {
    return health;
}

// Setter method for the health attribute. Sets the character's health to the provided value.
void Character::setHealth(int health) {
    this->health = health;
}

// Getter method for the attack attribute. Returns the current attack value of the character.
int Character::getAttack() const {
    return attack;
}
