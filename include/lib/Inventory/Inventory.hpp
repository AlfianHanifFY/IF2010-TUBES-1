#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "Slot.hpp"
#include <stdexcept>

#include "Item/Armor/Armor.hpp"

using namespace std;

class Inventory
{
private:
    static const int ROWS = 4;
    static const int COLS = 8;
    static const int MAX_STACK = 64;

    Slot backpack[ROWS][COLS];

    Item *weapon = nullptr;
    
    
    
    Item *armors[3];
    Item *pendant = nullptr;

public:
    Inventory();

    Inventory &operator+=(Item *item);

    bool addItemAt(Item *item, int i, int j);

    Item *removeItem(const std::string &itemID);

    void printBackpack() const;

    void printEquipped() const;

    bool equipItem(Item *item);

    bool unequipItem(Item *slot);

    Item *getItemAt(int row, int col);

    int getQuantityAt(int row, int col);

    Item *getHead();
    Item *getBody();
    Item *getFoot();
    Item *getWeapon();
    Item *getPendant();
    vector<Item *> getPotion();
    int getItemQuantity(string &id);
};

#endif