#ifndef SHOPSCREEN_HPP
#define SHOPSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class ShopScreen : public Screen
{
private:
    Button ExitBtn;
    Button SkillBtn;
    Button ShopBtn;
    Button InventoryBtn;
    Button DungeonBtn;

    Button WeaponBtn;
    Button ArmorBtn;
    Button PotionBtn;
    Button PendantBtn;
    Button BuyBtn;

    map<string, Button> itemBtn;

    vector<ShopItem> itemShop;

    Button leftBtn;
    Button rightBtn;

    ShopItem *current;
    vector<string> info;

    bool toggle;
    Button HomeBtn;
    int page;
    int itemsPerPage;
    PopUp popUp;

    int idx;
    string section;

public:
    ShopScreen(GameState &GameState);
    ~ShopScreen();

    void Draw();
};

#endif
