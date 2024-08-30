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

        local isEquipped = myObject:hasItemEquipped(item.name)

        -- Write this general information about item to .txt file
        file:write(string.format("Name: %s; Type: %s; Cost: %d; Weight: %f; Quantity: %d\n", item.name, item_type, cost, weight, count))

        if(item_type == "Weapon") then -- Collect info about weapon type and class

            local weapon_type = getWeaponTypeName(item.type) -- Get type of weapon and ammunition

            local weapon_class = getWeaponClassName(item.type) -- Get class of weapon and ammunition

            file:write(string.format("Weapon Type: %s; Weapon Class: %s; Equipped?: %s\n", weapon_type, weapon_class, isEquipped ? "true" : "false"))       

        elseif(item_type == "Ammunition") then -- Collect info about ammo type

            local weapon_type = getWeaponTypeName(item.type) -- Get type of weapon and ammunition

            file:write(string.format("Weapon Type: %s; Equipped?: %s\n", weapon_type, isEquipped ? "true" : "false"))      

        end

    end
 
    file:write("==END==") -- Signifies end of inventory items
    file:close()

    -- Closing message of script
    tes3.messageBox("Inventory exported to 'inventory_output.txt' inside the inventoryExporter mod folder.")
end

-- Event to trigger the data export when a save game is loaded successfully
event.register("loaded", exportInventory)