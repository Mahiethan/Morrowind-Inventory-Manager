#include "thieves_tool.hpp"

// getter methods

std::string ThievesTool::getType()
{
    return toolType;
}

int ThievesTool::getCondition()
{
    return condition;
}

// setter methods

void ThievesTool::setType(std::string type)
{
    toolType = type;
}

void ThievesTool::setCondition(int cond)
{
    condition = cond;
}