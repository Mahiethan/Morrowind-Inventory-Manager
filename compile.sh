set -e

main=main.cpp

item=./classes/item.cpp

printf "Compiling ..."

g++ -g $item $main -o inventoryManager

echo " DONE"