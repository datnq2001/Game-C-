#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <vector>
#include <memory>

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    std::shared_ptr<Item> getItem(const std::string& itemName) const;
    std::shared_ptr<Item> getEquipmentItem(const std::string& itemName) const;
    std::shared_ptr<Item> retrieveItem(const std::string& itemName);
    
    void listInventory() const;
    void listEquipment() const; // New method to list equipment
    void useItem(const std::string& itemName);
    void unattachItem(const std::string& itemName); // New method to unattach item

    void interactWithCharacter(const std::string& characterName);
    void interact() override;

    void addGold(int amount);
    void removeGold(int amount);
    int getGold() const;

    void addHealth(int amount);
    void reduceHealth(int amount);
    int getHealth() const;
    int getAttack() const;

    void addExperience(int amount); // New method to add experience points
    void levelUp(); // New method to handle level up
    int getLevel() const; // Get current level
    int getExperience() const; // Get current experience
    int getNextLevelExperience() const; // Get experience required for next level


    void attackEnemy(std::shared_ptr<Character> target);
    
    // Delete copy constructor and assignment operator
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    int gold;
    int health;
    int attack;
    int level; // New attribute for player level
    int exp; // New attribute for player experience

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()), gold(1000), health(200), attack(5), level(1), exp(0) {}

    std::vector<std::shared_ptr<Item>> inventory;
    std::vector<std::shared_ptr<Item>> equipment; // New vector for equipment
};

#endif //ZOORK_PLAYER_H
