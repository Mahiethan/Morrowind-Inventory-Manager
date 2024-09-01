#include <iostream> // Used to print data to stdout
#include <unordered_map> // Using a hash table data structure as the inventory to store each type of items (armor, weapons etc.) and to enable O(1) operations

/* Following headers used for user input */
#include <fstream>
#include <sstream>
#include <limits>

#include "./classes/armor.hpp" // Class for Armor type items

std::unordered_map<std::string,Item*> inventory; // Hash table data structure to store all inventory items

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
    
    while(std::getline(file, line))
    {
        if(line == "==END==") // End of inventory reached
            break;

        std::stringstream ss(line);
        std::string parsedValue;

        /* Parse "Name" */
        std::getline(ss, parsedValue, ';');
        std::string name = parsedValue.substr(parsedValue.find(':') + 2);
        // std::cout<<name<<std::endl;
        
        /* Parse "Type" */
        std::getline(ss, parsedValue, ';');
        std::string type = parsedValue.substr(parsedValue.find(':') + 2);
        // std::cout<<type<<std::endl;
        
        /* Parse "Cost" */
        std::getline(ss, parsedValue, ';');
        int cost = std::stoi(parsedValue.substr(parsedValue.find(':') + 2));
        // std::cout<<cost<<std::endl;
        
        /* Parse "Weight" */
        std::getline(ss, parsedValue, ';');
        float weight = std::stod(parsedValue.substr(parsedValue.find(':') + 2));
        // std::cout<<weight<<std::endl;
        
        /* Parse "Quantity" */
        std::getline(ss, parsedValue);
        int quantity = std::stoi(parsedValue.substr(parsedValue.find(':') + 2));
        // std::cout<<quantity<<std::endl;

        /* Based on item type, create appropriate object */

        if(type == "Armor")
        {
            Armor* armor = new Armor();
            armor->setName(name);
            armor->setSingleCost(cost);
            armor->setSingleWeight(weight);
            armor->setQuantity(quantity);

            // get next line to obtain additional information
            std::stringstream ss(line);

            std::getline(file, line);

            /* Parse "Armor Slot" */
            std::getline(ss, parsedValue, ';');
            std::string armorSlot = parsedValue.substr(parsedValue.find(':') + 2);
            
            /* Parse "Armor Class" */
            std::getline(ss, parsedValue, ';');
            std::string armorClass = parsedValue.substr(parsedValue.find(':') + 2);

            /* Parse "Equipped Status" */
            std::getline(ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            // manually setting details
            armor->setArmorSlot(armorSlot);
            armor->setArmorClass(armorClass);
            armor->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(armor->getName() != "UNDEFINED")
                inventory.insert(std::make_pair(armor->getName(),armor));

        }
        else if(type == "")
        {

        }
        // ... Repeat for other Item subclasses
    }
}

void searchInventory(std::string itemName)
{
    auto searchedItem = inventory.find(itemName);

    std::cout<<"\n";

    if(searchedItem != inventory.end())
    {
        if(auto castedItem = dynamic_cast<Armor*>(searchedItem->second))
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Armor slot: "<<castedItem->getArmorSlot()<<std::endl;
            std::cout<<"Armor class: "<<castedItem->getArmorClass()<<std::endl;
            std::cout<<"Is armor equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
    }
    else
        std::cout<<"Item \""<<itemName<<"\" was not found.\n"<<std::endl;
}

void searchInventoryMenu()
{
    bool validInput = true;

    while(validInput)
    {
        std::string itemName;

        std::cout<<"Enter the name of a item you want to search for:\n"<<std::endl;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(std::cin, itemName);

        searchInventory(itemName);

        int usrOption;

        std::cout<<"Search for another item?\n"<<std::endl;
        std::cout<<"(1) Yes"<<std::endl;
        std::cout<<"(2) No, return back to main menu\n"<<std::endl;

        std::cin >> usrOption;

        std::cout<<"\n";

        switch(usrOption)
        {
            case 1: break;
            case 2: validInput = false; std::cout<<"Returning back to main menu\n\n"; break;
            default: std::cout<<"Invalid input. Please try again (Select an integer between 1-2).\n\n";
        }
    }
}

void mainMenu()
{
    std::cout<<"Welcome to the Morrowind Inventory Manager\n"<<std::endl;

    bool validInput = true;

    while(validInput)
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
            case 1: std::cout<<"NOT YET IMPLEMENTED \n\n"; break;
            case 2: searchInventoryMenu(); break;
            case 3: parseInventory(); std::cout<<"Inventory refreshed. Return back to main menu.\n\n"; break;
            case 4: std::cout<<"Exiting program ... \n"; validInput = false; break;
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