#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <vector>
#include <memory>
#include <string>

// The Player class represents the player character in the game.
class Player : public Character {
public:
    // Static method to get the player instance.
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
    void listEquipment() const;
    void useItem(const std::string& itemName);
    void unattachItem(const std::string& itemName);

    void interactWithCharacter(const std::string& characterName);
    void interact() override;

    void addGold(int amount);
    void removeGold(int amount);
    int getGold() const;

    void addHealth(int amount);
    void reduceHealth(int amount);
    int getHealth() const;
    int getAttack() const;

    void addExperience(int amount);
    void levelUp();
    int getLevel() const;
    int getExperience() const;
    int getNextLevelExperience() const;

    void attackEnemy(std::shared_ptr<Character> target);

    void startQuest(const std::string& questName, int targetCount, const std::string& targetType, int expReward, int goldReward);
    void updateQuestProgress(const std::string& targetType);
    void checkQuestStatus() const;
    bool isQuestCompleted() const;
    void completeQuest();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    // Private constructor to prevent instantiation.
    static Player *playerInstance;
    Room* currentRoom;
    int gold;
    int health;
    int attack;
    int level;
    int exp;

    std::string questName;
    int targetCount;
    int defeatedCount;
    std::string targetType;
    int expReward;
    int goldReward;
    bool questActive;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()), gold(0), health(200), attack(5), level(1), exp(0),
               questName(""), targetCount(0), defeatedCount(0), targetType(""), expReward(0), goldReward(0), questActive(false) {}

    std::vector<std::shared_ptr<Item>> inventory;
    std::vector<std::shared_ptr<Item>> equipment;
};

#endif //ZOORK_PLAYER_H