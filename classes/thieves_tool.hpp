#ifndef THIEVES_TOOL_HPP
#define THIEVES_TOOL_HPP

#include "equippable.hpp"

/* Class representing Lockpick and Probe items */
class ThievesTool: public Equippable
{
    private:
        std::string toolType;
        int condition;
        // find a way to obtain current condition of item, instead of max
    public:
        // getters
        std::string getType();
        int getCondition();

        // setters
        void setType(std::string type);
        void setCondition(int condition);
};

#endif // THIEVES_TOOL_HPP