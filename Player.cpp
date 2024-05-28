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
    for (auto &invItem : inventory) {
        if (invItem->getName() == item->getName()) {
            invItem->setQuantity(invItem->getQuantity() + item->getQuantity());
            return;
        }
    }
    inventory.push_back(std::move(item));
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
            std::cout << "- " << item->getName() << " x" << item->getQuantity() << " (Price: " << item->getPrice() << "G)\n";
        }
    }
}

void Player::useItem(const std::string& itemName) {
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

void Player::addGold(int amount) {
    gold += amount;
}

void Player::removeGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    } else {
        std::cout << "You don't have enough gold.\n";
    }
}

int Player::getGold() const {
    return gold;
}
