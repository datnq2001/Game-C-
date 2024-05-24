#ifndef ZOORK_MERCHANT_H
#define ZOORK_MERCHANT_H

#include "Character.h"

class Merchant : public Character {
public:
    Merchant(const std::string &n, const std::string &d);

    void interact() override;
};

#endif //ZOORK_MERCHANT_H
