#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) {
    // Add item to the player's inventory
    auto existingItem = getItem(item->getName());
    if (existingItem) {
        existingItem->setQuantity(existingItem->getQuantity() + item->getQuantity());
    } else {
        inventory.push_back(std::move(item));
    }
}

void Player::removeItem(const std::string& itemName) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                   [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; }),
                   inventory.end());
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) const {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; });
    return it != inventory.end() ? *it : nullptr;
}

std::shared_ptr<Item> Player::retrieveItem(const std::string& itemName) {
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
            std::cout << "- " << item->getName() << " (x" << item->getQuantity() << ")\n";
        }
    }
}

void Player::useItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        item->use();
        item->decreaseQuantity();
        if (item->getQuantity() <= 0) {
            removeItem(itemName);
        }
    } else {
        std::cout << "You don't have " << itemName << ".\n";
    }
}
