#ifndef INVENTORYSCREEN_HPP
#define INVENTORYSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"
#include "../../Button/Button.hpp"

class InventoryScreen : public Screen
{
private:
    Button ExitBtn;
    Button SkillBtn;
    Button ShopBtn;
    Button InventoryBtn;
    Button DungeonBtn;
    Button HomeBtn;
    Button unEquipBtn;
    Button EquipBtn;
    Button SellBtn;
    map<string, Button> ItemSlot;
    map<string, Button> EquippedItem;
    PopUp popUp;
    Item *current;
    vector<string> info;
    bool toggleEquipment;
    string currentType;
    bool equipToggle;
    bool sellToggle;

    int curI, curJ;

public:
    InventoryScreen(GameState &GameState);
    ~InventoryScreen();

    void Draw();
};

#endif
