#ifndef ZOORK_MERCHANT_H
#define ZOORK_MERCHANT_H

#include "Character.h"
#include "Weapon.h"
#include "HealthPotion.h"
#include "Player.h"
#include <vector>
#include <algorithm>

class Merchant : public Character {
public:
    Merchant(const std::string &n, const std::string &d);

    void interact() override;
    void showInventory() const;
    void sellItem(const std::string &itemName, Player *player);
    void buyItemFromPlayer(const std::string &itemName, Player *player); // New method to buy items from player

private:
    std::vector<std::shared_ptr<Item>> inventory;
    void addItemToInventory(const std::shared_ptr<Item>& item);\
    bool isWeapon = false;
};

#endif //ZOORK_MERCHANT_H
