#include "weapon.hpp"

// getter methods

std::string Weapon::getWeaponType()
{
    return weaponType;
}

std::string Weapon::getWeaponClass()
{
    return weaponClass;
}

// setter methods

void Weapon::setWeaponType(std::string type)
{
    weaponType = type;
}

void Weapon::setWeaponClass(std::string c)
{
    weaponClass = c;
}