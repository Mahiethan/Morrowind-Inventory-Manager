#include "armor.hpp"

// getter methods

std::string Armor::getArmorSlot()
{
    return armorSlot;
}

std::string Armor::getArmorClass()
{
    return armorClass;
}

// setter methods

void Armor::setArmorSlot(std::string slot)
{
    armorSlot = slot;
}

void Armor::setArmorClass(std::string c)
{
    armorClass = c;
}

