#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <vector>

class Player : public Character {
public:
    static Player *instance() {
        // Lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    // Methods to manage the player's inventory
    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    std::shared_ptr<Item> getItem(const std::string& itemName) const;
    std::shared_ptr<Item> retrieveItem(const std::string& itemName);
    
    // Method to list all items in the inventory
    void listInventory() const;

    // Method to use an item from the inventory
    void useItem(const std::string& itemName);

    // Method to interact with a character
    void interactWithCharacter(const std::string& characterName);

    // Override the interact method from Character class
    void interact() override;

    void addGold(int amount);
    void removeGold(int amount);
    int getGold() const;

    // Delete copy constructor and assignment operator
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    int gold;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()), gold(1000) {}

    std::vector<std::shared_ptr<Item>> inventory;
};

#endif //ZOORK_PLAYER_H
