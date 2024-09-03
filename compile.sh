#!/bin/bash

set -e

main=main.cpp

item=./classes/item.cpp

equippable=./classes/equippable.cpp

armor=./classes/armor.cpp

weapon=./classes/weapon.cpp

thieves_tool=./classes/thieves_tool.cpp

# add file paths for more classes here

printf "Compiling ..."

g++ -g $item $equippable $armor $weapon $thieves_tool $main -o inventoryManager -static

echo " DONE"