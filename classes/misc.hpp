#ifndef MISCELLANEOUS_HPP
#define MISCELLANEOUS_HPP

#include "item.hpp"

class Miscellaneous: public Item
{
    private:
        std::string type;
    public:
        // getter
        std::string getType();

        // setter
        void setType(std::string type);
};

#endif // MISCELLANEOUS_HPP