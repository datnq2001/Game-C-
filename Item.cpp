#include "Item.h"
#include <utility>

Item::Item(const std::string &n, const std::string &d, int quantity, int price, int attack)
    : GameObject(n, d), useCommand(std::make_shared<NullCommand>()), quantity(quantity), price(price), attack(attack), bought(false) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, int quantity, int price, int attack)
    : GameObject(n, d), useCommand(std::move(c)), quantity(quantity), price(price), attack(attack), bought(false) {}

void Item::use() {
    useCommand->execute();
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Item::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
    }
}

int Item::getPrice() const {
    return price;
}

void Item::setPrice(int price) {
    this->price = price;
}

int Item::getAttack() const {
    return attack;
}

void Item::setAttack(int attack) {
    this->attack = attack;
}

bool Item::isBought() const {
    return bought;
}

void Item::setBought(bool bought) {
    this->bought = bought;
}
