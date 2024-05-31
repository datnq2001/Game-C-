#ifndef ZOORK_HEALTHPOTION_H
#define ZOORK_HEALTHPOTION_H

#include "Item.h"

// The HealthPotion class represents a healing item in the game.
class HealthPotion : public Item {
public:
    // Constructor for the HealthPotion class. Initializes the potion with a name, description, quantity, price, and heal amount.
    HealthPotion(const std::string &n, const std::string &d, int quantity = 1, int price = 10, int healAmount = 20)
        : Item(n, d, quantity, price), healAmount(healAmount) {}

    // Method to get the heal amount of the potion.
    int getHealAmount() const { return healAmount; }

    // Override the use method to display a message when the potion is used.
    void use() override {
        std::cout << "You used a " << getName() << ". You regained " << getHealAmount() << " health.\n\n";
    }

private:
    int healAmount; // The amount of health the potion restores.
};

#endif //ZOORK_HEALTHPOTION_H
