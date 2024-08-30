-- File: main.lua
-- Author: Mahiethan Nitharsan

-- Lua script to export all player inventory items to a file, for use in another program that organises the items into different groups.

-- -------------------------------------------------------------------------------------------------------------------------------------
-- Dictionary used to convert an ObjectType to its matching string value
local objectTypeNames = {
    [tes3.objectType.weapon] = "Weapon",
    [tes3.objectType.armor] = "Armor",
    [tes3.objectType.ammunition] = "Ammunition",
    [tes3.objectType.alchemy] = "Alchemy",
    [tes3.objectType.apparatus] = "Apparatus",
    [tes3.objectType.book] = "Book",
    [tes3.objectType.clothing] = "Clothing",
    [tes3.objectType.ingredient] = "Ingredient",
    [tes3.objectType.lockpick] = "Lockpick",
    [tes3.objectType.repairItem] = "Repair Tool",
    [tes3.objectType.probe] = "Probe",
    [tes3.objectType.light] = "Light",
    [tes3.objectType.miscItem] = "Miscellaneous"
    -- Add more ObjectTypes if inventory items are appearing with type "Unknown"
}

-- Dictionary used to convert an weapon type (tes3.weaponType) to its matching string value
local weaponTypeNames = {
    [0] = "Short Blade",
    [1] = "Long Blade",
    [2] = "Long Blade",
    [3] = "Blunt Weapon",
    [4] = "Warhammers",
    [5] = "Staffs",
    [6] = "Spear",
    [7] = "Axe",
    [8] = "Axe",
    [9] = "Bow",
    [10] = "Crossbow",
    [11] = "Thrown",
    [12] = "Arrows",
    [13] = "Bolts"
}

-- Dictionary used to convert an weapon type (tes3.weaponType) to its matching class string value
local weaponClassNames = {
    [0] = "One Handed",
    [1] = "One Handed",
    [2] = "Two Handed",
    [3] = "One Handed",
    [4] = "Two Handed",
    [5] = "Two Handed",
    [6] = "Two Handed",
    [7] = "One Handed",
    [8] = "Two Handed",
    [9] = "Marksman",
    [10] = "Marksman",
    [11] = "Marksman"
}

-- Dictionary used to convert an clothing slot to its matching string value
local clothingSlotNames = {
    [0] = "Pants",
    [1] = "Shoes",
    [2] = "Shirt",
    [3] = "Belt",
    [4] = "Robe",
    [5] = "Right Glove",
    [6] = "Left Glove",
    [7] = "Skirt",
    [8] = "Ring",
    [9] = "Amulet"
}

-- Dictionary used to convert an armor slot to its matching string value
local armorSlotNames = {
    [0] = "Helmet",
    [1] = "Cuirass",
    [2] = "Left Pauldron",
    [3] = "Right Pauldron",
    [4] = "Greaves",
    [5] = "Boots",
    [6] = "Left Gauntlet",
    [7] = "Right Gauntlet",
    [8] = "Shield",
    [9] = "Left Bracer",
    [10] = "Right Bracer"
}

-- Dictionary used to convert an armor weight class to its matching string value
local armorClassNames = {
    [0] = "Light",
    [1] = "Medium",
    [2] = "Heavy"
}


-- Function which returns the string value of the input ObjectType
local function getObjectTypeName(objectType)
	return objectTypeNames[objectType] or "Unknown"
end

-- Function which returns the string value of the input weaponType
local function getWeaponTypeName(weaponType)
	return weaponTypeNames[weaponType] or "Unknown"
end

-- Function which returns the string value of the class of the input weaponType
local function getWeaponClassName(weaponType)
	return weaponClassNames[weaponType] or "Unknown"
end

-- Function which returns the string value of the input clothingType
local function getClothingSlotName(clothingType)
	return clothingSlotNames[clothingType] or "Unknown"
end

-- Function which returns the string value of the input armorSlot
local function getArmorSlotName(armorSlot)
	return armorSlotNames[armorSlot] or "Unknown"
end

-- Function which returns the string value of the input armorClass
local function getArmorClassName(armorClass)
	return armorClassNames[armorClass] or "Unknown"
end


local function exportInventory()
    -- Opening message of script
    tes3.messageBox("Exporting inventory items ...")

    -- Define the output file path
    local file_path = "./Data Files/MWSE/mods/inventoryExporter/inventory_output.txt"
    local file = io.open(file_path, "w")

    if not file then
        tes3.messageBox("Error: Unable to open file for writing.")
        return
    end

    -- Get player character's name
    local player_name = tes3.player.object.name

    -- Write header to the file
    file:write("Inventory Export\n")
    file:write(string.format("Character name: %s\n",player_name))
    file:write("======================================\n\n")

    -- Iterate over the player's inventory
    for _, stack in pairs(tes3.player.object.inventory) do
        local item = stack.object -- Get inventory item (Object)

        local item_type = getObjectTypeName(item.objectType) -- Get type of item (weapon, armor, ingredient etc.)

        local count = stack.count or 1 -- Get quantity of current item stack

        local cost = item.value or 0 -- Get Septim cost of individual item

        local weight = item.weight or 0 -- Get weight of individual item

        local isEquipped = tes3.player.object:hasItemEquipped(item.id)

        -- Write this general information about item to .txt file
        file:write(string.format("Name: %s; Type: %s; Cost: %d; Weight: %f; Quantity: %d\n", item.name, item_type, cost, weight, count))

        if(item_type == "Weapon") then -- Collect info about weapon type and class

            local weapon_type = getWeaponTypeName(item.type) -- Get type of weapon and ammunition

            local weapon_class = getWeaponClassName(item.type) -- Get class of weapon and ammunition

            file:write(string.format("Weapon Type: %s; Weapon Class: %s; Equipped: %s\n", weapon_type, weapon_class, isEquipped))       

        elseif(item_type == "Ammunition") then -- Collect info about ammo type

            local weapon_type = getWeaponTypeName(item.type) -- Get type of weapon and ammunition

            file:write(string.format("Weapon Type: %s; Equipped: %s\n", weapon_type, isEquipped))      

        elseif(item_type == "Clothing") then -- Collect info about clothing type

            local clothing_slot = getClothingSlotName(item.slot) -- Get slot used by the clothing item

            file:write(string.format("Clothing Slot: %s; Equipped: %s\n", clothing_slot, isEquipped))
        elseif(item_type == "Armor") then -- Collect info about armor type

            local armor_slot = getArmorSlotName(item.slot) -- Get slot used by armor item

            local armor_class = getArmorClassName(item.weightClass) -- Get weight class of armor item

            file:write(string.format("Armor Slot: %s; Armor Class: %s; Equipped: %s\n", armor_slot, armor_class, isEquipped))          
        end

    end
 
    file:write("==END==") -- Signifies end of inventory items
    file:close()

    -- Closing message of script
    tes3.messageBox("Inventory exported to 'inventory_output.txt' inside the inventoryExporter mod folder.")
end

-- Event to trigger the data export when a save game is loaded successfully
event.register("loaded", exportInventory)