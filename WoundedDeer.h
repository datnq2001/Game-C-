#ifndef ZOORK_WOUNDEDDEER_H
#define ZOORK_WOUNDEDDEER_H

#include "Character.h"

class WoundedDeer : public Character {
public:
    WoundedDeer(const std::string &n, const std::string &d);

    void interact() override;
};

#endif //ZOORK_WOUNDEDDEER_H
