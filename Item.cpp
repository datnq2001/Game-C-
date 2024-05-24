#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d, int quantity) : GameObject(n, d),
                                                         useCommand(std::make_shared<NullCommand>()), quantity(quantity) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, int quantity) : GameObject(n, d),
                                                                                     useCommand(std::move(c)), quantity(quantity) {}

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
