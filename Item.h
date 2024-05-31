#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    // Constructor without command
    Item(const std::string &, const std::string &, int quantity = 1, int price = 0, int attack = 0);

    // Constructor with command
    Item(const std::string &, const std::string &, std::shared_ptr<Command>, int quantity = 1, int price = 0, int attack = 0);

    // Method to use the item
    virtual void use();

    // Method to set the use command
    void setUseCommand(std::shared_ptr<Command>);

    // Method to get the quantity of the item
    int getQuantity() const;
    // Method to set the quantity of the item
    void setQuantity(int quantity);
    // Method to decrease the quantity of the item by 1
    void decreaseQuantity();

    // Method to get the price of the item
    int getPrice() const;
    // Method to set the price of the item
    void setPrice(int price);

    // Method to get the attack value of the item
    int getAttack() const;
    // Method to set the attack value of the item
    void setAttack(int attack);

    // Method to check if the item has been bought
    bool isBought() const;
    // Method to set the bought status of the item
    void setBought(bool bought);

protected:
    std::shared_ptr<Command> useCommand; // Command to execute when the item is used
    int quantity; // Quantity of the item
    int price; // Price of the item
    int attack; // Attack value of the item
    bool bought; // Whether the item has been bought or not
};

#endif //ZOORK_ITEM_H
