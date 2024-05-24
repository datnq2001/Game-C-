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

    // Delete copy constructor and assignment operator
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;

    // Private constructor for singleton pattern
    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}

    std::vector<std::shared_ptr<Item>> inventory;  // Player's inventory
};

#endif //ZOORK_PLAYER_H
