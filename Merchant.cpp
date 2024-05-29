#include "Merchant.h"
#include "Weapon.h"
#include "HealthPotion.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

Merchant::Merchant(const std::string &n, const std::string &d) : Character(n, d) {
    addItemToInventory(std::make_shared<Weapon>("Basic-Sword", "A basic sword with 50 physical attack.", 1, 80, 50));
    addItemToInventory(std::make_shared<Weapon>("Silver-Sword", "A powerful sword with 80 physical attack.", 1, 140, 80));
    addItemToInventory(std::make_shared<Weapon>("Magic-Wand", "A wand with 60 magic attack.", 1, 120, 60));
    addItemToInventory(std::make_shared<Weapon>("Bow", "A bow with 55 physical attack.", 1, 85, 55));
    addItemToInventory(std::make_shared<HealthPotion>("Health-Potion", "A potion that restores 20 HP.", 1, 10, 20));
}

void Merchant::interact() {
    std::cout << "The merchant says: 'Care to trade? I have many goods to offer.'\n";
    showInventory();
}

void Merchant::showInventory() const {
    std::cout << "Merchant's Inventory:\n";
    for (const auto &item : inventory) {
        std::cout << "- " << item->getName() << " (Price: " << item->getPrice() << "G, ";
        if (item->getAttack() > 0) {
            std::cout << "Attack: " << item->getAttack() << ")";
        } else if (auto potion = std::dynamic_pointer_cast<HealthPotion>(item)) {
            std::cout << "Heal: " << potion->getHealAmount() << " HP)";
        } else {
            std::cout << ")";
        }
        if (item->isBought()) {
            std::cout << " [Bought]";
        }
        std::cout << "\n";
    }
}

void Merchant::sellItem(const std::string &itemName, Player *player) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                [&itemName](const std::shared_ptr<Item>& item) { 
                    std::string lowerItemName = item->getName();
                    std::string lowerInputName = itemName;
                    std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);
                    std::transform(lowerInputName.begin(), lowerInputName.end(), lowerInputName.begin(), ::tolower);
                    return lowerItemName == lowerInputName; 
                });
    if (it != inventory.end()) {
        auto item = *it;
        if (player->getItem(itemName) || player->getEquipmentItem(itemName)) {
            std::cout << "You already have " << item->getName() << " in your inventory.\n";
            return;
        }
        if (player->getGold() >= item->getPrice()) {
            player->removeGold(item->getPrice());
            player->addItem(item);
            std::cout << "You bought " << item->getName() << " for " << item->getPrice() << "G.\n";
            if (auto weapon = std::dynamic_pointer_cast<Weapon>(item)) {
                item->setBought(true);
            }
        } else {
            std::cout << "You don't have enough gold to buy " << item->getName() << ".\n";
        }
    } else {
        std::cout << "Item not found in merchant's inventory.\n";
    }
}

void Merchant::buyItemFromPlayer(const std::string &itemName, Player *player) {
    auto item = player->retrieveItem(itemName);
    if (item) {
        int sellPrice = item->getPrice(); // Assume merchant buys at half the price
        player->addGold(sellPrice);
        addItemToInventory(item);
        std::cout << "You sold " << item->getName() << " for " << sellPrice << "G.\n";
    } else {
        std::cout << "You don't have " << itemName << " to sell.\n";
    }
}

void Merchant::addItemToInventory(const std::shared_ptr<Item>& item) {
    inventory.push_back(item);
}
