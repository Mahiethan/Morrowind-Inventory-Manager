#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "equippable.hpp"

class Light: public Equippable
{
    private:
        int duration;
    public:
        // getters
        int getDuration();

        // setters
        void setDuration(int time);
};

#endif // LIGHT_HPP