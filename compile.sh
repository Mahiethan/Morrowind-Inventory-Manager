#!/bin/bash

set -e

main=main.cpp

item=./classes/item.cpp

equippable=./classes/equippable.cpp

armor=./classes/armor.cpp

weapon=./classes/weapon.cpp

thieves_tool=./classes/thieves_tool.cpp

clothing=./classes/clothing.cpp

misc=./classes/misc.cpp

soul_gem=./classes/soul_gem.cpp

# add file paths for more classes here

printf "Compiling ..."

g++ -g $item $equippable $armor $weapon $thieves_tool $clothing $misc $soul_gem $main -o inventoryManager -static

echo " DONE"