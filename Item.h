#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &, int quantity = 1, int price = 0);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>, int quantity = 1, int price = 0);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

    int getQuantity() const;
    void setQuantity(int quantity);
    void decreaseQuantity();

    int getPrice() const; // New method to get the price
    void setPrice(int price); // New method to set the price

protected:
    std::shared_ptr<Command> useCommand;
    int quantity;
    int price; // New attribute for the price
};

#endif //ZOORK_ITEM_H
