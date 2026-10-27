#include "GUI/Screen/SkillPathScreen/SkillPathScreen.hpp"
#include <iostream>
#include <vector>
#include <string>

SkillPathScreen::SkillPathScreen(GameState &gameState) : Screen(gameState),
                                                         ExitBtn(828, 462, 951 - 828, 531 - 462, "EXIT", RED),
                                                         SkillBtn(702, 462, 824 - 702, 531 - 462, "SKILL", BROWN),
                                                         ShopBtn(482, 462, 698 - 482, 531 - 462, "SHOP", BROWN),
                                                         InventoryBtn(242, 462, 477 - 242, 531 - 462, "INVENTORY", BROWN),
                                                         DungeonBtn(8, 462, 238 - 8, 531 - 462, "DUNGEON", ORANGE),
                                                         HomeBtn(190, 416, 235 - 190, 451 - 416, "<<", GRAY),
                                                         BaseSkillBtn(289, 180, 380 - 289, 272 - 180),
                                                         A1SkillBtn(475, 58, 380 - 289, 272 - 180),
                                                         A2SkillBtn(700, 58, 380 - 289, 272 - 180),
                                                         B1SkillBtn(472, 316, 380 - 289, 272 - 180),
                                                         B2SkillBtn(696, 315, 380 - 289, 272 - 180),
                                                         MasterBtn(33, 405, 145, 50, "MASTER", RED),
                                                         popUp()
{
    selectedSkill = nullptr;
    skillTree = getGameState().getCharacter()->getSkillTree();
}

SkillPathScreen::~SkillPathScreen()
{
}

void SkillPathScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    Texture2D bg = LoadTexture("./Assets/SkillPathScreen/SkillPathScreen.png");
    DrawTexture(bg, 0, 0, WHITE);

    ExitBtn.draw();
    DungeonBtn.draw();
    ShopBtn.draw();
    SkillBtn.draw();
    InventoryBtn.draw();
    HomeBtn.draw();

    
    BaseSkillBtn.draw();
    A1SkillBtn.draw();
    A2SkillBtn.draw();
    B1SkillBtn.draw();
    B2SkillBtn.draw();

    DrawText(skillTree->getSkills()["Base"]->getName().c_str(), 291, 216, 10, BLACK);
    DrawText(skillTree->getSkills()["A1"]->getName().c_str(), 478, 95, 10, BLACK);
    DrawText(skillTree->getSkills()["A2"]->getName().c_str(), 703, 95, 10, BLACK);
    DrawText(skillTree->getSkills()["B1"]->getName().c_str(), 473, 352, 10, BLACK);
    DrawText(skillTree->getSkills()["B2"]->getName().c_str(), 699, 352, 10, BLACK);

    

    if (BaseSkillBtn.isClicked())
    {
        selectedSkill = skillTree->getSkills()["Base"];
    }

    if (A1SkillBtn.isClicked())
    {
        selectedSkill = skillTree->getSkills()["A1"];
    }

    if (A2SkillBtn.isClicked())
    {
        selectedSkill = skillTree->getSkills()["A2"];
    }

    if (B1SkillBtn.isClicked())
    {
        selectedSkill = skillTree->getSkills()["B1"];
    }

    if (B2SkillBtn.isClicked())
    {
        selectedSkill = skillTree->getSkills()["B2"];
    }

    
    if (selectedSkill != nullptr)
    {
        info = {
            "Name = " + selectedSkill->getName(),
            "Mana Cost = " + to_string(selectedSkill->getManaCost()),
            "Mastery Cost = " + to_string(selectedSkill->getMasteryCost()),
            "Effect : ",
        };
        vector<Effect *> effects = selectedSkill->getEffects();
        for (auto i = effects.begin(); i != effects.end(); i++)
        {
            info.push_back(" - " + (*i)->getName());
            info.push_back("   > " + (*i)->getDescription());
            info.push_back("   > duration " + to_string((*i)->getDuration()));
        }
        MasterBtn.draw();

        if (MasterBtn.isClicked())
        {
            try
            {
                getGameState().getCharacter()->learnSkill(selectedSkill);
                popUp.trigger("Success learn " + selectedSkill->getName(), GREEN, 0.5);
                popUp.show();
            }
            catch (string &e)
            {
                popUp.trigger(e, RED, 0.5);
                popUp.show();
            }
        }
    }

    drawList(info, 20, 112, 15, WHITE);
    

    if (HomeBtn.isClicked())
        setNext("HomeScreen");
    if (ExitBtn.isClicked())
        setNext("ExitScreen");
    if (DungeonBtn.isClicked())
        setNext("DungeonSelectionScreen");
    if (SkillBtn.isClicked())
        setNext("SkillScreen");
    if (ShopBtn.isClicked())
        setNext("ShopScreen");
    if (InventoryBtn.isClicked())
        setNext("InventoryScreen");

    popUp.update();
    popUp.draw();
}