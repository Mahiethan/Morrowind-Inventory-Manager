#ifndef EQUIPPABLE_HPP
#define EQUIPPABLE_HPP

#include "item.hpp"

class Equippable: public Item
{
    private:
        bool isEquipped; // boolean flag which determines if the item is currently equipped
    public:
        // getter
        bool getEquippedStatus();

        // setter
        void setEquippedStatus(bool status);
};

#endif // EQUIPPABLE_HPP
