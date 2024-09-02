#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "equippable.hpp"

class Weapon : public Equippable
{
    private:
        std::string weaponType;
        std::string weaponClass;
    public:
        // getters
        std::string getWeaponType();
        std::string getWeaponClass();

        // setters
        void setWeaponType(std::string type);
        void setWeaponClass(std::string c);

};

#endif // WEAPON_HPP