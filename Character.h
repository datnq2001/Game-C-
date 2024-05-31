#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>
#include <memory>

// The Character class represents a character in the game, inheriting from GameObject.
class Character : public GameObject {
public:
    // Constructor that initializes a character with a name and description.
    Character(const std::string &, const std::string &);

    // Public method to get the character's health.
    int getHealth() const;

    // Public method to set the character's health.
    void setHealth(int health);

    // Public method to get the character's attack value.
    int getAttack() const;

    // Pure virtual method for interaction, making Character an abstract class.
    virtual void interact() = 0;

protected:
    // Vector to store the character's inventory items.
    std::vector<std::shared_ptr<Item>> inventory;
    
    std::vector<std::string> tags;

    // Character's health points.
    int health;

    // Character's attack value.
    int attack;

    // Character's movement points.
    int move;
    
    // Character's initiative value.
    int initiative;
};

#endif //ZOORK_CHARACTER_H
