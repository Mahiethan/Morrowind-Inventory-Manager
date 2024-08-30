#include <iostream> // used to print data to stdout
#include <unordered_map> // using a hash table data structure as the inventory to store all items and enable O(1) operations

#include "./classes/item.hpp"

int main()
{
    std::unordered_map<std::string,Item> inventory; // Hash table data structure to store the whole inventory items

    // Parse through text file and obtain each inventory item
    // Create the correct Item instance for each item, set the attributes and add it the the hash table data structure
    // Repeat the following code inside the 'for' loop for all inventory items

    int totalItems = 1;

    for(int i = 0; i < totalItems; i++)
    {
        // Example item
        Item item;

        item.setName("Wickwheat");
        item.setQuantity(54);
        item.setSingleCost(1);
        item.setSingleWeight(0.1);

        // Add each item to the inventory map
        inventory.insert(std::make_pair(item.getName(),item));
    }

    // Hash table contains all of the items in the inventory

    // Testing out search

    auto searchedItem = inventory.find("Wickwheat");

    if(searchedItem != inventory.end())
    {
        // If found, calculate total cost and total weight
        std::cout<<"Total value: "<<searchedItem->second.calculateTotalValue()<<" septims"<<std::endl;
        std::cout<<"Total weight: "<<searchedItem->second.calculateTotalWeight()<<std::endl;
    }

    return 0;
}