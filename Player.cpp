#include "Player.h"
#include <iostream>

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) {
    // Check if the item already exists in the inventory
    auto existingItem = getItem(item->getName());
    if (existingItem) {
        // Increase the quantity of the existing item
        existingItem->setQuantity(existingItem->getQuantity() + item->getQuantity());
    } else {
        // Add new item to the inventory
        inventory.push_back(std::move(item));
    }
}

void Player::removeItem(const std::string& itemName) {
    // Remove item from the inventory by name
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                   [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; }),
                   inventory.end());
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) const {
    // Get item from the inventory by name
    auto it = std::find_if(inventory.begin(), inventory.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; });
    return it != inventory.end() ? *it : nullptr;
}

std::shared_ptr<Item> Player::retrieveItem(const std::string& itemName) {
    // Retrieve item from the inventory and remove it
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}

void Player::listInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (const auto& item : inventory) {
            std::cout << "- " << item->getName() << " (x" << item->getQuantity() << ") price: " << item->getPrice() << "G\n";
        }
    }
}

void Player::useItem(const std::string& itemName) {
    // Use an item from the inventory
    auto item = getItem(itemName);
    if (item) {
        item->use();
    } else {
        std::cout << "You don't have " << itemName << ".\n";
    }
}

void Player::interactWithCharacter(const std::string& characterName) {
    auto character = currentRoom->getCharacter(characterName);
    if (character) {
        character->interact();
    } else {
        std::cout << "There is no " << characterName << " here.\n";
    }
}

void Player::interact() {
    std::cout << "You can't interact with yourself.\n";
}
