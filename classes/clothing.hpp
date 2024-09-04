#ifndef CLOTHING_HPP
#define CLOTHING_HPP

#include "equippable.hpp"

class Clothing: public Equippable
{
    private:
        std::string clothingSlot;
    public:
        // getters
        std::string getClothingSlot();

        // setters
        void setClothingSlot(std::string slot);
};

#endif // CLOTHING_HPP