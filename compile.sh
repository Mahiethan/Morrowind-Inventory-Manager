set -e

main=main.cpp

item=./classes/item.cpp

equippable=./classes/equippable.cpp

armor=./classes/armor.cpp

printf "Compiling ..."

g++ -g $item $equippable $armor $main -o inventoryManager

echo " DONE"