#include <iostream> // Used to print data to stdout
#include <unordered_map> // Using a hash table data structure as the inventory to store each type of items (armor, weapons etc.) and to enable O(1) operations

#include <fstream>
#include <sstream>
#include <string>

#include "./classes/armor.hpp"

std::unordered_map<std::string,Armor> armorInventory; // Hash table data structure to store all Armor-type items
// ... Repeat for other item types

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

        if(type == "Armor")
        {
            Armor armor;
            armor.setName(name);
            armor.setSingleCost(cost);
            armor.setSingleWeight(weight);
            armor.setQuantity(quantity);

            // get next line to obtain additional information

            // manually setting details
            armor.setArmorSlot("Left Pauldron");
            armor.setArmorClass("Medium");
            armor.setEquippedStatus(true);

            if(armor.getName() != "UNDEFINED")
                armorInventory.insert(std::make_pair(armor.getName(),armor));

        }
        // ... Repeat for other Item subclasses
    }
}

int main()
{
    // Parse through text file and obtain each inventory item
    parseInventory();

    auto searchedItem = armorInventory.find("Adamantium Left Pauldron");

    if(searchedItem != armorInventory.end())
    {
        std::cout<<"Name: "<<searchedItem->second.getName()<<std::endl;

        std::cout<<"Armor slot: "<<searchedItem->second.getArmorSlot()<<std::endl;
        std::cout<<"Armor class: "<<searchedItem->second.getArmorClass()<<std::endl;
        std::cout<<"Is armor equipped: "<<(searchedItem->second.getEquippedStatus() ? "true" : "false")<<std::endl;

        // Calculate total cost and total weight
        std::cout<<"Total value: "<<searchedItem->second.calculateTotalValue()<<" septims"<<std::endl;
        std::cout<<"Total weight: "<<searchedItem->second.calculateTotalWeight()<<std::endl;
    }

    return 0;
}