#ifndef ZOORK_OTHERLEGENDARYCHARACTERS_H
#define ZOORK_OTHERLEGENDARYCHARACTERS_H

#include "Character.h"

// Class definition for OtherLegendaryCharacters which inherits from Character
class OtherLegendaryCharacters : public Character {
public:
    // Constructor for OtherLegendaryCharacters
    OtherLegendaryCharacters(const std::string &n, const std::string &d);

    // Override interact method for specific interaction behavior
    void interact() override;
};

#endif //ZOORK_OTHERLEGENDARYCHARACTERS_H
