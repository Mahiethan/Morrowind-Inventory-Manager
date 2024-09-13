#ifndef SOUL_GEM_HPP
#define SOUL_GEM_HPP

#include "misc.hpp"

class SoulGem: public Miscellaneous
{
    private:
        int soulCapacity; 
    public:
        // getter
        int getSoulCapacity();

        // setter
        void setSoulCapacity(int capacity);
};

#endif // SOUL_GEM_HPP