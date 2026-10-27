#include "GUI/Screen/HomeScreen/HomeScreen.hpp"

HomeScreen::HomeScreen(GameState &GameState) : Screen(GameState),
                                               ExitBtn(828, 462, 951 - 828, 531 - 462, "EXIT", RED),
                                               SkillBtn(702, 462, 824 - 702, 531 - 462, "SKILL", BROWN),
                                               ShopBtn(482, 462, 698 - 482, 531 - 462, "SHOP", BROWN),
                                               InventoryBtn(242, 462, 477 - 242, 531 - 462, "INVENTORY", BROWN),
                                               DungeonBtn(8, 462, 238 - 8, 531 - 462, "DUNGEON", ORANGE)

{
    
    if (getGameState().getCharacter()->getName() == "HMIF")
    {
        getGameState().HMIF();
    }
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::Draw()
{
    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/HomeScreen/HomeScreen.png");
    string profileAsset = "./Assets/profile/" + getGameState().getCharacter()->getCharType() + ".png";
    Texture2D profile = LoadTexture(profileAsset.c_str());
    DrawTexture(bg, 0, 0, WHITE);
    
    ExitBtn.draw();
    DungeonBtn.draw();
    ShopBtn.draw();
    SkillBtn.draw();
    InventoryBtn.draw();

    
    DrawTexture(profile, 25, 31, WHITE);
    
    DrawText(getGameState().getCharacter()->getName().c_str(), 100, 26, 15, WHITE);
    DrawText((string("Rank ") + (getGameState().getCharacter()->getRank())).c_str(), 100, 26 + 18, 15, WHITE);
    DrawText(getGameState().getCharacter()->getCharType().c_str(), 100, 26 + 18 + 18, 13, WHITE);
    DrawText((string("Lvl.") + to_string(getGameState().getCharacter()->getLevel())).c_str(), 100, 26 + 18 + 18 + 18, 13, WHITE);

    
    std::vector<std::string> info = {
        "Exp = " + std::to_string(getGameState().getCharacter()->getExp()) + " / 100",
        "Mastery = " + std::to_string(getGameState().getCharacter()->getMastery()),
        "Gold = " + std::to_string(getGameState().getCharacter()->getGold()),
        "Stat",
        "  Intelligent = " + std::to_string(getGameState().getCharacter()->getStat(1)),
        "  Strength = " + std::to_string(getGameState().getCharacter()->getStat(0)),
        "  Agility = " + std::to_string(getGameState().getCharacter()->getStat(2)),
        "Equipped Item :",
        "   Weapon  : " + (getGameState().getCharacter()->getWeapon() ? getGameState().getCharacter()->getWeapon()->getName() : "None"),
        "   Armor   : " + (getGameState().getCharacter()->getHead() ? getGameState().getCharacter()->getHead()->getName() : "None"),
        "   Body    : " + (getGameState().getCharacter()->getBody() ? getGameState().getCharacter()->getBody()->getName() : "None"),
        "   Foot    : " + (getGameState().getCharacter()->getFoot() ? getGameState().getCharacter()->getFoot()->getName() : "None"),
        "   Pendant : " + (getGameState().getCharacter()->getFoot() ? getGameState().getCharacter()->getPendant()->getName() : "None"),
        "Active Skill : ",
    };

    vector<Skill *> activeSkill = getGameState().getCharacter()->getSkillTree()->getActiveSkill();
    for (auto i = activeSkill.begin(); i != activeSkill.end(); i++)
    {
        info.push_back(" - " + (*i)->getName());
    }

    drawList(info, 20, 122, 14, WHITE);

    DrawText((string("Config : ./") + getGameState().getConfigPath()).c_str(), 20, 429, 14, WHITE);

    
    if (ExitBtn.isClicked())
    {
        setNext("ExitScreen");
    }
    if (DungeonBtn.isClicked())
    {
        setNext("DungeonSelectionScreen");
    }
    if (SkillBtn.isClicked())
    {
        setNext("SkillScreen");
    }
    if (ShopBtn.isClicked())
    {
        setNext("ShopScreen");
    }
    if (InventoryBtn.isClicked())
    {
        setNext("InventoryScreen");
    }
}