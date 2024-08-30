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

void searchInventory(std::unordered_map<std::string,Armor>* selection)
{
    if(selection == &armorInventory)
    {
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
    }
}

void searchInventoryMenu()
{
    bool validInput = false;
    while(!validInput)
    {
        int usrOption;

        std::cout<<"Select which inventory to search:\n"<<std::endl;
        std::cout<<"(1) Armor inventory\n";
        std::cout<<"(2) Return to main menu\n";

        std::cin >> usrOption;

        std::cout<<"\n";

        switch(usrOption)
        {
            case 1: searchInventory(&armorInventory); break;
            case 2: validInput = true; break;
            default: std::cout<<"Invalid input. Please try again (Select an integer between 1-2).\n\n";
        }
    }
}

void mainMenu()
{
    std::cout<<"Welcome to the Morrowind Inventory Manager\n\n"<<std::endl;

    bool validInput = false;

    while(!validInput)
    {
        int usrOption;

        std::cout<<"Select one of the following features: (Enter an integer)\n"<<std::endl;
        std::cout<<"(1) View inventory\n";
        std::cout<<"(2) Search inside inventory\n";
        std::cout<<"(3) Refresh inventory\n";
        std::cout<<"(4) Exit program\n";

        std::cin >> usrOption;

        std::cout<<"\n";

        switch(usrOption)
        {
            case 1: std::cout<<"NOT YET IMPLEMENTED \n"; break;
            case 2: searchInventoryMenu(); break;
            case 3: parseInventory(); std::cout<<"Inventory refreshed. Return back to main menu.\n\n"; break;
            case 4: std::cout<<"Exiting program ... \n"; validInput = true; break;
            default: std::cout<<"Invalid input. Please try again (Select an integer between 1-3).\n\n";
        }
    }
}

int main()
{
    /* Parse through text file and obtain each inventory item before proceeding to main menu for user input */
    parseInventory();

    mainMenu();

    return 0;
}