#include "armor.hpp"

// constructor

Armor::Armor()
{
    setName("UNDEFINED");
    setSingleWeight(0.0);
    setSingleCost(0);
    setQuantity(0);

    setEquippedStatus(false);

    setArmorSlot("UNDEFINED");
    setArmorClass("UNDEFINED");
}

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

