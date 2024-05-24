#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &, int quantity = 1);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>, int quantity = 1);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

    int getQuantity() const;
    void setQuantity(int quantity);
    void decreaseQuantity();

protected:
    std::shared_ptr<Command> useCommand;
    int quantity;
};

#endif //ZOORK_ITEM_H
