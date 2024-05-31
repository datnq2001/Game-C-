#include "Item.h"
#include <utility>

// Constructor for the Item class. Initializes the item with a name, description, quantity, price, and attack value.
Item::Item(const std::string &n, const std::string &d, int quantity, int price, int attack)
    : GameObject(n, d), useCommand(std::make_shared<NullCommand>()), quantity(quantity), price(price), attack(attack), bought(false) {}

// Constructor for the Item class with a command. Initializes the item with a name, description, command, quantity, price, and attack value.
Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, int quantity, int price, int attack)
    : GameObject(n, d), useCommand(std::move(c)), quantity(quantity), price(price), attack(attack), bought(false) {}

// Method to use the item by executing its command.
void Item::use() {
    useCommand->execute();
}

// Method to set the use command for the item.
void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}

// Method to get the quantity of the item.
int Item::getQuantity() const {
    return quantity;
}

// Method to set the quantity of the item.
void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}

// Method to decrease the quantity of the item by 1.
void Item::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
    }
}

// Method to get the price of the item.
int Item::getPrice() const {
    return price;
}

// Method to set the price of the item.
void Item::setPrice(int price) {
    this->price = price;
}

// Method to get the attack value of the item.
int Item::getAttack() const {
    return attack;
}

// Method to set the attack value of the item.
void Item::setAttack(int attack) {
    this->attack = attack;
}

// Method to check if the item has been bought.
bool Item::isBought() const {
    return bought;
}

// Method to set the bought status of the item.
void Item::setBought(bool bought) {
    this->bought = bought;
}
