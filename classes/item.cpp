#include "item.hpp"

// Destructor

Item::~Item()
{
    // Do nothing. Only exists to enable downcasting.
}

// Setter methods

void Item::setName(std::string n)
{
    name = n;
}

void Item::setSingleWeight(float w)
{
    weight = w;
}

void Item::setSingleCost(int c)
{
    cost = c;
}

void Item::setQuantity(int q)
{
    quantity = q;
}

// Getter methods

std::string Item::getName()
{
    return name;
}

float Item::getSingleWeight()
{
    return weight;
}

int Item::getSingleCost()
{
    return cost;
}

int Item::getQuantity()
{
    return quantity;
}

// Additional functions

float Item::calculateTotalWeight()
{
    return getQuantity() * getSingleWeight();
}

int Item::calculateTotalValue()
{
    return getQuantity() * getSingleCost();
}

