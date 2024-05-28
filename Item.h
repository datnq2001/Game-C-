#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &, int quantity = 1, int price = 0, int attack = 0);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>, int quantity = 1, int price = 0, int attack = 0);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

    int getQuantity() const;
    void setQuantity(int quantity);
    void decreaseQuantity();

    int getPrice() const;
    void setPrice(int price);

    int getAttack() const;
    void setAttack(int attack);

    bool isBought() const;
    void setBought(bool bought);

protected:
    std::shared_ptr<Command> useCommand;
    int quantity;
    int price;
    int attack; // New attribute for attack
    bool bought; // New attribute for bought status
};

#endif //ZOORK_ITEM_H
