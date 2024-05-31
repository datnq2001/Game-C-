#ifndef ZOORK_HEALTHPOTION_H
#define ZOORK_HEALTHPOTION_H

#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion(const std::string &n, const std::string &d, int quantity = 1, int price = 10, int healAmount = 20)
        : Item(n, d, quantity, price), healAmount(healAmount) {}

    int getHealAmount() const { return healAmount; }

    void use() override {
        std::cout << "You used a " << getName() << ". You regained " << getHealAmount() << " health.\n";
    }

private:
    int healAmount;
};

#endif //ZOORK_HEALTHPOTION_H
