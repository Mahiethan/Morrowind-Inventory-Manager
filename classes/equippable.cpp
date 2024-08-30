#include "item.hpp"
#include "equippable.hpp"

// Getter method

bool Equippable::getEquippedStatus()
{
    return isEquipped;
}

// Setter method

void Equippable::setEquippedStatus(bool status)
{
    isEquipped = status;
}