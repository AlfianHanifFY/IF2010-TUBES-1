#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"
#include "../../Button/Button.hpp"

class HomeScreen : public Screen
{
private:
    Button ExitBtn;
    Button SkillBtn;
    Button ShopBtn;
    Button InventoryBtn;
    Button DungeonBtn;

public:
    HomeScreen(GameState &GameState);
    ~HomeScreen();

    void Draw();
};

#endif
