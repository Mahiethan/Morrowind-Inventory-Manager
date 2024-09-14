#ifndef APPARATUS_HPP
#define APPARATUS_HPP

#include "item.hpp"

class Apparatus: public Item
{
    private:
        std::string apparatusType; 
    public:
        // getter
        std::string getApparatusType();

        // setter
        void setApparatusType(std::string type);
};

#endif // APPARATUS_HPP