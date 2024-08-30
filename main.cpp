#include <iostream> // used to print data to stdout
#include <unordered_map> // using a hash table data structure as the inventory to store all items and enable O(1) operations

#include <fstream>
#include <sstream>
#include <string>

#include "./classes/item.hpp"

std::unordered_map<std::string,Item> inventory; // Hash table data structure to store the whole inventory items

void parseInventory()
{
    /* Open text file and check if it exists */
    std::ifstream file("inventory_output.txt"); 
    
    if (!file.is_open())
    {
        std::cerr<<"File 'inventory_output.txt' not found."<<std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line; // String variable to process each line in the text file

    /* Skip the next four lines */
    for (int i = 0; i < 4; ++i)
        std::getline(file, line); 
    
    while (std::getline(file, line))
    {
        if(line == "==END==") // End of inventory reached
            break;

        std::stringstream ss(line);
        std::string token;

        /* Parse "Name" */
        std::getline(ss, token, ';');
        std::string name = token.substr(token.find(':') + 2);
        // std::cout<<name<<std::endl;
        
        /* Parse "Type" */
        std::getline(ss, token, ';');
        std::string type = token.substr(token.find(':') + 2);
        // std::cout<<type<<std::endl;
        
        /* Parse "Cost" */
        std::getline(ss, token, ';');
        int cost = std::stoi(token.substr(token.find(':') + 2));
        // std::cout<<cost<<std::endl;
        
        /* Parse "Weight" */
        std::getline(ss, token, ';');
        float weight = std::stod(token.substr(token.find(':') + 2));
        // std::cout<<weight<<std::endl;
        
        /* Parse "Quantity" */
        std::getline(ss, token);
        int quantity = std::stoi(token.substr(token.find(':') + 2));
        // std::cout<<quantity<<std::endl;

        /* Based on item type, create appropriate object */

        Item item;

        item.setName(name);
        item.setSingleCost(cost);
        item.setSingleWeight(weight);
        item.setQuantity(quantity);

        inventory.insert(std::make_pair(item.getName(),item));
    }
}

int main()
{
    // Parse through text file and obtain each inventory item
    parseInventory();

    auto searchedItem = inventory.find("Adamantium Left Pauldron");

    if(searchedItem != inventory.end())
    {
        // If found, calculate total cost and total weight
        std::cout<<"Total value: "<<searchedItem->second.calculateTotalValue()<<" septims"<<std::endl;
        std::cout<<"Total weight: "<<searchedItem->second.calculateTotalWeight()<<std::endl;
    }

    return 0;
}