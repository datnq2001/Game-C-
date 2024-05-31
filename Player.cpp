#include "Player.h"
#include "Weapon.h"
#include "HealthPotion.h"
#include "Enemy.h"
#include "Item.h"
#include <iostream>
#include <algorithm>

Player *Player::playerInstance = nullptr;

// Set the current room for the player
void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

// Get the current room of the player
Room* Player::getCurrentRoom() const {
    return currentRoom;
}

// Add an item to the player's inventory
void Player::addItem(std::shared_ptr<Item> item) {

    // If item already exists in inventory, increase its quantity
    for (auto &invItem : inventory) {
        if (invItem->getName() == item->getName()) {
            invItem->setQuantity(invItem->getQuantity() + item->getQuantity());
            return;
        }
    }
    // Otherwise, add the new item to the inventory
    inventory.push_back(std::move(item));

}

// Remove an item from the player's inventory by name
void Player::removeItem(const std::string& itemName) {

    // Remove item from inventory by name
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                   [&itemName](const std::shared_ptr<Item>& item) { 
                       std::string lowerItemName = item->getName();
                       std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                       return lowerItemName == itemName; 
                   }),
                   inventory.end());

}

// Get an item from the player's inventory by name
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

// Get an item from the player's equipment by name
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

// Retrieve an item from the player's inventory and remove it
std::shared_ptr<Item> Player::retrieveItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}

// List all items in the player's inventory
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

// List all items in the player's equipment
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

// Use an item from the player's inventory
void Player::useItem(const std::string& itemName) {
    auto item = getItem(itemName);
    // If item is found in inventory, use it
    if (item) {
        if (auto weapon = std::dynamic_pointer_cast<Weapon>(item)) {
            attack += weapon->getAttack();
            std::cout << "Your attack increased to " << attack << ".\n";
            equipment.push_back(item);  // Add to equipment
            removeItem(itemName);  // Remove from inventory
            weapon->use();  // Call use method from Weapon
        } else if (auto potion = std::dynamic_pointer_cast<HealthPotion>(item)) {
            health += potion->getHealAmount();
            std::cout << "You regained health. Current health: " << health << ".\n";
            item->decreaseQuantity();
            if (item->getQuantity() <= 0) {
                removeItem(itemName);
            }
            potion->use();  // Call use method from HealthPotion
        } else {
            item->use();  // Call use method from other types of items
        }
    } else {
        std::cout << "You don't have " << itemName << ".\n";
    }
}

// Unattach an item from the player's equipment
void Player::unattachItem(const std::string& itemName) {
    // Find the item in equipment
    auto it = std::find_if(equipment.begin(), equipment.end(),
                [&itemName](const std::shared_ptr<Item>& item) { 
                    std::string lowerItemName = item->getName();
                    std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                    return lowerItemName == itemName; 
                });

    // If item is found in equipment, remove it and add back to inventory
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

// Interact with a character in the current room
void Player::interactWithCharacter(const std::string& characterName) {
    auto character = currentRoom->getCharacter(characterName);
    if (character) {
        character->interact();
    } else {
        std::cout << "There is no " << characterName << " here.\n";
    }
}

// Self-interaction (not allowed)
void Player::interact() {
    std::cout << "You can't interact with yourself.\n";
}

// Attack an enemy character
void Player::attackEnemy(std::shared_ptr<Character> target) {
    if (target) {
        target->setHealth(target->getHealth() - attack);
        std::cout << "You attack " << target->getName() << " for " << attack << " damage.\n";
        if (target->getHealth() <= 0) {
            std::cout << target->getName() << " has been defeated!\nYou gain 5 Gold and 20EXP\n";
            currentRoom->removeCharacter(target->getName());
            currentRoom->addCharacter(std::make_shared<Enemy>("goblin", "A menacing goblin.", 100, 20)); // Respawn the enemy for future battles 100HP, 20 attack
            addExperience(20); // Gain 20 EXP for defeating an enemy
            addGold(10); // Gain 20 gold for defeating an enemy
            updateQuestProgress(target->getName());
        } else {
            std::cout << target->getName() << " has " << target->getHealth() << " health remaining.\n";
            reduceHealth(target->getAttack());
            std::cout << "You take " << target->getAttack() << " damage. Your current health: " << health << "HP.\n\n";
        }
    }
}

// Add gold to the player's total
void Player::addGold(int amount) {
    gold += amount;
    std::cout << "You gained " << amount << "G.\n\n";
}

// Remove gold from the player's total
void Player::removeGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    } else {
        std::cout << "You don't have enough gold.\n";
    }
}

// Get the player's current gold amount
int Player::getGold() const {
    return gold;
}

// Add health to the player's total
void Player::addHealth(int amount) {
    health += amount;
}

// Reduce health from the player's total
void Player::reduceHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        std::cout << "You have died. Game over.\n";
        exit(0);
    }
}

// Get the player's current health amount
int Player::getHealth() const {
    return health;
}

// Get the player's current attack value
int Player::getAttack() const {
    return attack;
}

// Add experience points to the player's total
void Player::addExperience(int amount) {
    exp += amount;
    std::cout << "You gained " << amount << "EXP.\n\n";
    while (exp >= getNextLevelExperience()) {
        exp -= getNextLevelExperience();
        levelUp();
    }
}

// Level up the player
void Player::levelUp() {
    level++;
    std::cout << "<-----  Congratulations! You reached level " << level << "  ----->\n\n";
    // Increase stats or provide other benefits here
}

// Get the player's current level
int Player::getLevel() const {
    return level;
}

// Get the player's current experience points
int Player::getExperience() const {
    return exp;
}

// Get the experience points required for the next level
int Player::getNextLevelExperience() const {
    return 50 * level; // Example formula for next level EXP
}

// Start a quest with a target count and rewards
void Player::startQuest(const std::string& questName, int targetCount, const std::string& targetType, int expReward, int goldReward) {
    this->questName = questName;        // Set the quest details
    this->targetCount = targetCount;    // Set the target count
    this->defeatedCount = 0;            // Initialize the defeated count
    this->targetType = targetType;      // Set the target type
    this->expReward = expReward;        // Set the experience reward
    this->goldReward = goldReward;      // Set the gold reward
    this->questActive = true;           // Set the quest as active
    std::cout << "Quest started: " << questName << ". Defeat " << targetCount << " " << targetType << "(s).\n\n";
}

// Update the quest progress based on the target type
void Player::updateQuestProgress(const std::string& targetType) {
    if (questActive && this->targetType == targetType) {
        defeatedCount++;
        std::cout << "Quest progress: " << defeatedCount << "/" << targetCount << " " << targetType << "(s) defeated.\n\n";
        
        // Check if the quest is completed
        if (defeatedCount >= targetCount) {
            questActive = false;
            auto seeds = std::make_shared<Item>("sacred-rice-seeds", "These are the sacred rice seeds stolen by the goblins.", 1);
            addItem(seeds);
            std::cout << "Quest completed! You found the sacred rice seeds in your repository. Please return it to villager to get rewards!\n\n";
            /*
            For quests that reward Gold and Exp directly, add the following code:

                addExperience(expReward);
                addGold(goldReward);
            */
        }
    }
}

// Check the status of the current quest
void Player::checkQuestStatus() const {
    if (questActive) {
        std::cout << "Current quest: " << questName << ". Progress: " << defeatedCount << "/" << targetCount << " " << targetType << "(s) defeated.\n\n";
    } else {
        std::cout << "No active quest.\n";
    }
}

// Check if the quest is completed
bool Player::isQuestCompleted() const {
    return !questActive && defeatedCount >= targetCount;
}

// Complete the current quest
void Player::completeQuest() {
    questName = "";
    targetCount = 0;
    defeatedCount = 0;
    targetType = "";
    expReward = 0;
    goldReward = 0;
    questActive = false;
}