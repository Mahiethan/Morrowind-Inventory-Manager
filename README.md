# TES III : Morrowind Inventory Management Tool

# ***Work in Progress***

# Prerequisites

- A game copy of *"The Elder Scrolls III : Morrowind"*

- *MWSE (Morrowind Script Extender)*
    - Installation: https://www.nexusmods.com/morrowind/mods/45468 (Nexus Mods) 

    - Follow the mod requirements listed on this mod webpage to ensure compatability.

# Where to place the Lua script inside the `inventoryExplorer` folder?

Copy the entire folder `inventoryExplorer` into the following directory:

```
PATH/TO/GAME/Morrowind/Data Files/MWSE/mods
```

Once placed here, the contained Lua script is triggered to work when successfully loading a save inside the game. The following message will appear, every time a save file is loaded, to indicate that the Lua script is correctly working:

```
"Exporting inventory items ..."
```

The inventory items of the playable character in the save file will be stored in a text file called `inventory_output.txt`, which will be produced in the same directory as the Lua script `./inventoryExplorer` inside the `./mods` folder.

The path for this text file can be changed by editing the following value in the `main.lua` script:

```lua
local filePath = "./Data Files/MWSE/mods/inventoryExporter/inventory_output.txt"
```