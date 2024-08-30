#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "equippable.hpp"

class Armor: public Equippable
{
    private:
        std::string armorSlot;
        std::string armorClass;
    public:
        //constructor
        Armor();

        //getters
        std::string getArmorSlot();
        std::string getArmorClass();

        //setters
        void setArmorSlot(std::string type);
        void setArmorClass(std::string c);
};

#endif // ARMOR_HPP