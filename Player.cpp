#include "Player.h"
#include "Weapon.h"
#include "HealthPotion.h"
#include "Enemy.h"
#include <iostream>
#include <algorithm>

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
                   [&itemName](const std::shared_ptr<Item>& item) { 
                       std::string lowerItemName = item->getName();
                       std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                       return lowerItemName == itemName; 
                   }),
                   inventory.end());
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) const {
    std::string lowerInputName = itemName;
    std::transform(lowerInputName.begin(), lowerInputName.end(), lowerInputName.begin(), ::tolower);
    auto it = std::find_if(inventory.begin(), inventory.end(),
                [&lowerInputName](const std::shared_ptr<Item>& item) { 
                    std::string lowerItemName = item->getName();
                    std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                    return lowerItemName == lowerInputName; 
                });
    return it != inventory.end() ? *it : nullptr;
}

std::shared_ptr<Item> Player::getEquipmentItem(const std::string& itemName) const {
    std::string lowerInputName = itemName;
    std::transform(lowerInputName.begin(), lowerInputName.end(), lowerInputName.begin(), ::tolower);
    auto it = std::find_if(equipment.begin(), equipment.end(),
                [&lowerInputName](const std::shared_ptr<Item>& item) { 
                    std::string lowerItemName = item->getName();
                    std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                    return lowerItemName == lowerInputName; 
                });
    return it != equipment.end() ? *it : nullptr;
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

void Player::listEquipment() const {
    if (equipment.empty()) {
        std::cout << "You have no equipment.\n";
    } else {
        std::cout << "Your equipment:\n";
        for (const auto& item : equipment) {
            std::cout << "- " << item->getName() << " (Attack: " << item->getAttack() << ")\n";
        }
    }
}

void Player::useItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        if (auto weapon = std::dynamic_pointer_cast<Weapon>(item)) {
            attack += weapon->getAttack();
            std::cout << "Your attack increased to " << attack << ".\n";
            equipment.push_back(item);  // Add to equipment
            removeItem(itemName);  // Remove from inventory
            weapon->use();  // Thay đổi: Gọi phương thức use từ Weapon
        } else if (auto potion = std::dynamic_pointer_cast<HealthPotion>(item)) {
            health += potion->getHealAmount();
            std::cout << "You regained health. Current health: " << health << ".\n";
            item->decreaseQuantity();
            if (item->getQuantity() <= 0) {
                removeItem(itemName);
            }
            potion->use();  // Thay đổi: Gọi phương thức use từ HealthPotion
        } else {
            item->use();  // Gọi phương thức use từ các loại item khác
        }
    } else {
        std::cout << "You don't have " << itemName << ".\n";
    }
}


void Player::unattachItem(const std::string& itemName) {
    auto it = std::find_if(equipment.begin(), equipment.end(),
                [&itemName](const std::shared_ptr<Item>& item) { 
                    std::string lowerItemName = item->getName();
                    std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                    return lowerItemName == itemName; 
                });
    if (it != equipment.end()) {
        auto item = *it;
        if (auto weapon = std::dynamic_pointer_cast<Weapon>(item)) {
            attack -= weapon->getAttack();
            std::cout << "Your attack decreased to " << attack << ".\n";
            addItem(item);  // Add back to inventory
            equipment.erase(it);  // Remove from equipment
        }
    } else {
        std::cout << "You don't have " << itemName << " equipped.\n";
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

void Player::attackEnemy(std::shared_ptr<Character> target) {
    if (target) {
        target->setHealth(target->getHealth() - attack);
        std::cout << "You attack " << target->getName() << " for " << attack << " damage.\n";
        if (target->getHealth() <= 0) {
            std::cout << target->getName() << " has been defeated!\nYou gain 5 Gold and 20EXP\n";
            currentRoom->removeCharacter(target->getName());
            currentRoom->addCharacter(std::make_shared<Enemy>("goblin", "A menacing goblin.", 100, 20));
            addExperience(20); // Example: Gain 20 EXP for defeating an enemy
            addGold(20); // Example: Gain 20 gold for defeating an enemy
        } else {
            std::cout << target->getName() << " has " << target->getHealth() << " health remaining.\n";
            reduceHealth(target->getAttack());
            std::cout << "You take " << target->getAttack() << " damage. Your current health: " << health << "HP.\n\n";
        }
    }
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

void Player::addHealth(int amount) {
    health += amount;
}

void Player::reduceHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        std::cout << "You have died. Game over.\n";
        exit(0);
    }
}

int Player::getHealth() const {
    return health;
}

int Player::getAttack() const {
    return attack;
}

void Player::addExperience(int amount) {
    exp += amount;
    std::cout << "You gained " << amount << " experience points.\n\n";
    while (exp >= getNextLevelExperience()) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    exp = 0;
    std::cout << "<-----  Congratulations! You reached level " << level << "  ----->\n\n";
    // Increase stats or provide other benefits here
}

int Player::getLevel() const {
    return level;
}

int Player::getExperience() const {
    return exp;
}

int Player::getNextLevelExperience() const {
    return 50 * level; // Example formula for next level EXP
}
