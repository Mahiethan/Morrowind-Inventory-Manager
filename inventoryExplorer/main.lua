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
    [tes3.objectType.miscItem] = "Misc. Item"
}

local function getObjectTypeName(objectType)
	return objectTypeNames[objectType] or "Unknown"
end

local function exportInventory()
    -- Define the output file path
    local filePath = "./Data Files/MWSE/mods/inventoryExporter/inventory_output.txt"
    local file = io.open(filePath, "w")

    if not file then
        tes3.messageBox("Error: Unable to open file for writing.")
        return
    end

    tes3.messageBox("Exporting inventory items ...")

    -- Get player character's name
    local playerName = tes3.player.object.name

    -- Write header to the file
    file:write("Inventory Export"\n")
    file:write(string.format("Character name: %s"\n",playerName))
    file:write("======================================\n\n")

    -- Iterate over the player's inventory
    for _, stack in pairs(tes3.player.object.inventory) do
        local item = stack.object
        local count = stack.count

        file:write(string.format("Name: %s, Type: %s, Count: %d\n", item.name, getObjectTypeName(item.objectType), count))
    end
 
    file:write("==END==")
    file:close()
    tes3.messageBox("Inventory exported to 'inventory_output.txt' inside the inventoryExporter mod folder.")
end

-- Event to trigger the data export when a save game is loaded successfully
event.register("loaded", exportInventory)