#include <iostream> // Used to print data to stdout
#include <unordered_map> // Using a hash table data structure as the inventory to store each type of items (armor, weapons etc.) and to enable O(1) operations
#include <vector>
#include <algorithm>

/* Following headers used for user input */
#include <fstream>
#include <sstream>
#include <limits>

#include "./classes/armor.hpp" // Class for Armor type items
#include "./classes/weapon.hpp" // Class for Weapon type items
#include "./classes/thieves_tool.hpp" // Class for Lockpick and Probe items
#include "./classes/clothing.hpp" // Class for Clothing type items
#include "./classes/misc.hpp" // Class for Miscellaneous items (e.g. keys, coins)
#include "./classes/soul_gem.hpp" // Class for Soul Gem items
#include "./classes/apparatus.hpp" // Class for Apparatus items
#include "./classes/light.hpp" // Class for Light items

std::unordered_map<std::string,Item*> inventory; // Hash table data structure to store all inventory items

void parseInventory()
{
    inventory.clear(); // Clear any items stored inside the hash map before parsing

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
            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Armor Slot" */
            std::getline(next_ss, parsedValue, ';');
            std::string armorSlot = parsedValue.substr(parsedValue.find(':') + 2);
            
            /* Parse "Armor Class" */
            std::getline(next_ss, parsedValue, ';');
            std::string armorClass = parsedValue.substr(parsedValue.find(':') + 2);

            /* Parse "Equipped Status" */
            std::getline(next_ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            armor->setArmorSlot(armorSlot);
            armor->setArmorClass(armorClass);
            armor->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(armor->getName() != "UNDEFINED")
                inventory.insert(std::make_pair(armor->getName(),armor));

        }
        else if(type == "Weapon")
        {
            Weapon* weapon = new Weapon();
            weapon->setName(name);
            weapon->setSingleCost(cost);
            weapon->setSingleWeight(weight);
            weapon->setQuantity(quantity);

            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Weapon Slot" */
            std::getline(next_ss, parsedValue, ';');
            std::string weaponType = parsedValue.substr(parsedValue.find(':') + 2);
            
            /* Parse "Weapon Class" */
            std::getline(next_ss, parsedValue, ';');
            std::string weaponClass = parsedValue.substr(parsedValue.find(':') + 2);

            /* Parse "Equipped Status" */
            std::getline(next_ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            weapon->setWeaponType(weaponType);
            weapon->setWeaponClass(weaponClass);
            weapon->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(weapon->getName() != "UNDEFINED")
                inventory.insert(std::make_pair(weapon->getName(),weapon));
        }
        else if(type == "Lockpick" | type == "Probe")
        {
            ThievesTool* tool = new ThievesTool();
            tool->setName(name);
            tool->setSingleCost(cost);
            tool->setSingleWeight(weight);
            tool->setQuantity(quantity);

            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Condition" */
            std::getline(next_ss, parsedValue, ';');
            int condition = std::stoi(parsedValue.substr(parsedValue.find(':') + 2));

            /* Parse "Equipped Status" */
            std::getline(next_ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            tool->setType(type);
            tool->setCondition(condition);
            tool->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(tool->getName() != "UNDEFINED")
                inventory.insert(make_pair(tool->getName(),tool));
        }
        else if(type == "Clothing")
        {
            Clothing* clothing = new Clothing();
            clothing->setName(name);
            clothing->setSingleCost(cost);
            clothing->setSingleWeight(weight);
            clothing->setQuantity(quantity);

            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Clothing Slot" */
            std::getline(next_ss, parsedValue, ';');
            std::string clothingSlot = parsedValue.substr(parsedValue.find(':') + 2);

            /* Parse "Equipped Status" */
            std::getline(next_ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            clothing->setClothingSlot(clothingSlot);
            clothing->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(clothing->getName() != "UNDEFINED")
                inventory.insert(make_pair(clothing->getName(),clothing));
        }
        else if(type == "Apparatus")
        {
            Apparatus* apparatus = new Apparatus();
            apparatus->setName(name);
            apparatus->setSingleCost(cost);
            apparatus->setSingleWeight(weight);
            apparatus->setQuantity(quantity);

            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Apparatus Type" */
            std::getline(next_ss, parsedValue, ';');
            std::string apparatusType = parsedValue.substr(parsedValue.find(':') + 2);

            apparatus->setApparatusType(apparatusType);

            if(apparatus->getName() != "UNDEFINED")
                inventory.insert(make_pair(apparatus->getName(),apparatus));
        }
        else if(type == "Light")
        {
            Light* light = new Light();
            light->setName(name);
            light->setSingleCost(cost);
            light->setSingleWeight(weight);
            light->setQuantity(quantity);

            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Duration" */
            std::getline(next_ss, parsedValue, ';');
            int lightDuration = std::stoi(parsedValue.substr(parsedValue.find(':') + 2));

            /* Parse "Equipped Status" */
            std::getline(next_ss, parsedValue, ';');
            std::string equippedStatus = parsedValue.substr(parsedValue.find(':') + 2);

            light->setDuration(lightDuration);
            light->setEquippedStatus(equippedStatus == "true" ? true : false);

            if(light->getName() != "UNDEFINED")
                inventory.insert(make_pair(light->getName(),light));
        }
        else if(type == "Miscellaneous")
        {
            // get next line to obtain additional information

            std::getline(file, line);

            std::stringstream next_ss(line);

            /* Parse "Type" */
            std::getline(next_ss, parsedValue, ';');
            std::string miscType = parsedValue.substr(parsedValue.find(':') + 2);

            if(miscType == "Soul Gem") // Create the SoulGem subclass if this is a Soul Gem type
            {
                /* Parse "Soul Gem Capacity" */
                std::getline(next_ss, parsedValue, ';');
                int soulGemCapacity = std::stoi(parsedValue.substr(parsedValue.find(':') + 2));

                SoulGem* soul_gem = new SoulGem();
                soul_gem->setName(name);
                soul_gem->setSingleCost(cost);
                soul_gem->setSingleWeight(weight);
                soul_gem->setQuantity(quantity);

                soul_gem->setType(miscType);

                soul_gem->setSoulCapacity(soulGemCapacity);

                if(soul_gem->getName() != "UNDEFINED")
                    inventory.insert(make_pair(soul_gem->getName(),soul_gem));
            }
            else // Create a standard Misc object for other types
            {
                Miscellaneous* misc = new Miscellaneous();
                misc->setName(name);
                misc->setSingleCost(cost);
                misc->setSingleWeight(weight);
                misc->setQuantity(quantity);

                misc->setType(miscType);

                if(misc->getName() != "UNDEFINED")
                    inventory.insert(make_pair(misc->getName(),misc));
            }
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
        if(auto castedItem = dynamic_cast<Armor*>(searchedItem->second)) // Armor
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
        else if(auto castedItem = dynamic_cast<Weapon*>(searchedItem->second)) // Weapon
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Weapon type: "<<castedItem->getWeaponType()<<std::endl;
            std::cout<<"Weapon class: "<<castedItem->getWeaponClass()<<std::endl;
            std::cout<<"Is weapon equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<ThievesTool*>(searchedItem->second)) // Thieves Tool (Lockpicks and Probes)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Tool type: "<<castedItem->getType()<<std::endl;
            std::cout<<"Item condition: "<<castedItem->getCondition()<<std::endl;
            std::cout<<"Is tool equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Clothing*>(searchedItem->second)) // Clothing items
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Clothing slot: "<<castedItem->getClothingSlot()<<std::endl;
            std::cout<<"Is clothing equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Apparatus*>(searchedItem->second)) // Apparatus items (Alembic, Calcinator, Mortar and Pestle, Retort)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Apparatus type: "<<castedItem->getApparatusType()<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Light*>(searchedItem->second)) // Apparatus items (Alembic, Calcinator, Mortar and Pestle, Retort)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Duration: "<<castedItem->getDuration()<<std::endl;
            std::cout<<"Is light equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Miscellaneous*>(searchedItem->second)) // Misc items (Coin, Soul Gem, Key, Other)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Item type: "<<castedItem->getType()<<std::endl;

            if(auto soulGemItem = dynamic_cast<SoulGem*>(castedItem))
                std::cout<<"Soul capacity: "<<soulGemItem->getSoulCapacity()<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        // ... Repeat for other Item subclasses
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

void viewInventory(std::vector<Item*> inventory)
{
    std::cout<<"Total inventory items: "<<inventory.size()<<"\n"<<std::endl;
    
    // Iterate through all inventory items
    for(auto item = inventory.begin(); item != inventory.end(); item++)
    {
        /* COPIED FROM searchInventory FUNCTION - KEEP IT UPDATED */
        if(auto castedItem = dynamic_cast<Armor*>(*item)) // Armor
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
        else if(auto castedItem = dynamic_cast<Weapon*>(*item)) // Weapon
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Weapon type: "<<castedItem->getWeaponType()<<std::endl;
            std::cout<<"Weapon class: "<<castedItem->getWeaponClass()<<std::endl;
            std::cout<<"Is weapon equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<ThievesTool*>(*item)) // Weapon
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Tool type: "<<castedItem->getType()<<std::endl;
            std::cout<<"Item condition: "<<castedItem->getCondition()<<std::endl;
            std::cout<<"Is tool equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Clothing*>(*item)) // Weapon
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Clothing slot: "<<castedItem->getClothingSlot()<<std::endl;
            std::cout<<"Is clothing equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Apparatus*>(*item)) // Apparatus items (Alembic, Calcinator, Mortar and Pestle, Retort)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Apparatus type: "<<castedItem->getApparatusType()<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Light*>(*item)) // Apparatus items (Alembic, Calcinator, Mortar and Pestle, Retort)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Duration: "<<castedItem->getDuration()<<std::endl;
            std::cout<<"Is light equipped: "<<(castedItem->getEquippedStatus() ? "true" : "false")<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        else if(auto castedItem = dynamic_cast<Miscellaneous*>(*item)) // Misc items (Coin, Soul Gem, Key, Other)
        {
            std::cout<<"Name: "<<castedItem->getName()<<std::endl;

            std::cout<<"Item type: "<<castedItem->getType()<<std::endl;

            if(auto soulGemItem = dynamic_cast<SoulGem*>(castedItem))
                std::cout<<"Soul capacity: "<<soulGemItem->getSoulCapacity()<<std::endl;

            // Calculate total cost and total weight
            std::cout<<"Total value: "<<castedItem->calculateTotalValue()<<" septims"<<std::endl;
            std::cout<<"Total weight: "<<castedItem->calculateTotalWeight()<<std::endl;

            std::cout<<"\n";
        }
        // ... Repeat for other Item subclasses
    }

    std::cout<<"Reached end of inventory. Returning back to main menu.\n\n";
}

void viewInventoryMenu()
{
    bool validInput = true;

    std::vector<Item*> viewList;

    while(validInput)
    {
        std::cout<<"What kind of items do you want to view: (Enter an integer between 1-4 then press ENTER key)\n"<<std::endl;
        std::cout<<"(1) View all items\n";
        std::cout<<"(2) View all equippable items\n";
        std::cout<<"(3) View all apparatus items\n";
        std::cout<<"(4) View all misc. items\n";
        std::cout<<"(5) Return back to main menu\n";

        std::string usrOption;

        std::cin >> usrOption;

        std::cout<<"\n";

        if(usrOption == "1") // View all items in inventory
        {
            for(auto item : inventory)
                viewList.push_back(item.second);
        }
        else if(usrOption == "2") // View all equippable items
        {
            for(auto item : inventory)
            {
                if(auto castedItem = dynamic_cast<Equippable*>(item.second))
                    viewList.push_back(item.second);
            }
        }
        else if(usrOption == "3") // View all apparatus items
        {
            for(auto item : inventory)
            {
                if(auto castedItem = dynamic_cast<Apparatus*>(item.second))
                    viewList.push_back(item.second);
            }
        }
        else if(usrOption == "4") // View all misc. items
        {
            for(auto item : inventory)
            {
                if(auto castedItem = dynamic_cast<Miscellaneous*>(item.second))
                    viewList.push_back(item.second);
            }
        }
        else if(usrOption == "5") // Return to main menu
            return ;
        else if(usrOption != "5") // Invalid inputs
        {
            std::cout<<"Invalid input. Please try again.\n\n";
            continue;
        }

        validInput = false;
    }

    validInput = true;

    while(validInput)
    {
        std::cout<<"Select a sorting criteria: (Enter an integer between 1-9 then press ENTER key)\n"<<std::endl;
        std::cout<<"(1) Sort by name (increasing)\n";
        std::cout<<"(2) Sort by name (decreasing)\n";
        std::cout<<"(3) Sort by cost (increasing)\n";
        std::cout<<"(4) Sort by cost (decreasing)\n";
        std::cout<<"(5) Sort by quantity (increasing)\n";
        std::cout<<"(6) Sort by quantity (decreasing)\n";
        std::cout<<"(7) Sort by weight (increasing)\n";
        std::cout<<"(8) Sort by weight (decreasing)\n";
        std::cout<<"(9) Return back to main menu\n";

        std::string usrOption;

        std::cin >> usrOption;

        std::cout<<"\n";

        if(usrOption == "1") // Sort items alphabetically in increasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->getName() < b->getName(); 
            });
        }
        else if(usrOption == "2") // Sort items alphabetically in decreasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->getName() > b->getName();  
            });
        }
        else if(usrOption == "3") // Sort items by total value in increasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->calculateTotalValue() < b->calculateTotalValue(); 
            });
        }
        else if(usrOption == "4") // Sort items by total value in decreasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->calculateTotalValue() > b->calculateTotalValue(); 
            });
        }
        else if(usrOption == "5") // Sort items by quantity in increasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->getQuantity() < b->getQuantity(); 
            });
        }
        else if(usrOption == "6") // Sort items by quantity in decreasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->getQuantity() > b->getQuantity();  
            });
        }
        else if(usrOption == "7") // Sort items by total weight in increasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->calculateTotalWeight() < b->calculateTotalWeight(); 
            });
        }
        else if(usrOption == "8") // Sort items by total weight in decreasing order
        {
            std::sort(viewList.begin(), viewList.end(), [](Item* a, Item* b) {
                return a->calculateTotalWeight() > b->calculateTotalWeight(); 
            });
        }
        else if(usrOption == "9") // Clear viewing list before returning back to menu
            viewList.clear();
        else if(usrOption != "9") // Invalid inputs
        {
            std::cout<<"Invalid input. Please try again.\n\n";
            continue;
        }

        validInput = false;
    }

    if(!viewList.empty())
        viewInventory(viewList);
    else
        std::cout<<"Returning back to main menu.\n\n";

    viewList.clear();
}

void mainMenu()
{
    std::cout<<"Welcome to the Morrowind Inventory Manager\n"<<std::endl;

    bool validInput = true;

    while(validInput)
    {
        std::string usrOption;

        std::cout<<"Select one of the following features: (Enter an integer between 1-4 then press ENTER key)\n"<<std::endl;
        std::cout<<"(1) View inventory\n";
        std::cout<<"(2) Search inside inventory\n";
        std::cout<<"(3) Refresh inventory\n";
        std::cout<<"(4) Exit program\n";

        std::cin >> usrOption;

        std::cout<<"\n";

        if(usrOption == "1")
            viewInventoryMenu();
        else if(usrOption == "2")
            searchInventoryMenu();
        else if(usrOption == "3")
        {
            parseInventory();
            std::cout<<"Inventory refreshed. Returning back to main menu.\n\n";
        }
        else if(usrOption == "4")
        {
            std::cout<<"Exiting program ... \n";
            validInput = false;
        }
        else // Invalid inputs
            std::cout<<"Invalid input. Please try again.\n\n";  
    }
}

int main()
{
    /* Parse through text file and obtain each inventory item before proceeding to main menu for user input */
    parseInventory();

    mainMenu();

    return 0;
}