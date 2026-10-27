#ifndef SKILLPATHSCREEN_HPP
#define SKILLPATHSCREEN_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../Screen.hpp"

class SkillPathScreen : public Screen
{
private:
    Button ExitBtn;
    Button SkillBtn;
    Button ShopBtn;
    Button InventoryBtn;
    Button DungeonBtn;
    Button HomeBtn;
    Button MasterBtn;

    Button BaseSkillBtn;
    Button A1SkillBtn;
    Button A2SkillBtn;
    Button B1SkillBtn;
    Button B2SkillBtn;

    vector<Button> skillBtn;

    Skill *selectedSkill;
    SkillTree *skillTree;
    map<string, Rectangle> skillRects;

    vector<string> info;

    PopUp popUp;

public:
    SkillPathScreen(GameState &gameState);
    virtual ~SkillPathScreen();

    void Draw();
};

#endif