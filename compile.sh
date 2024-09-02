set -e

main=main.cpp

item=./classes/item.cpp

equippable=./classes/equippable.cpp

armor=./classes/armor.cpp

weapon=./classes/weapon.cpp

# add file paths for more classes here

printf "Compiling ..."

g++ -g $item $equippable $armor $weapon $main -o inventoryManager -static

echo " DONE"