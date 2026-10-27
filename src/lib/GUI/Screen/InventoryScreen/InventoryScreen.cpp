#include "GUI/Screen/InventoryScreen/InventoryScreen.hpp"

InventoryScreen::InventoryScreen(GameState &GameState) : Screen(GameState), ExitBtn(828, 462, 951 - 828, 531 - 462, "EXIT", RED),
                                                         SkillBtn(702, 462, 824 - 702, 531 - 462, "SKILL", BROWN),
                                                         ShopBtn(482, 462, 698 - 482, 531 - 462, "SHOP", BROWN),
                                                         InventoryBtn(242, 462, 477 - 242, 531 - 462, "INVENTORY", BROWN),
                                                         DungeonBtn(8, 462, 238 - 8, 531 - 462, "DUNGEON", ORANGE),
                                                         HomeBtn(190, 416, 235 - 190, 451 - 416, "<<", GRAY),
                                                         popUp(),
                                                         unEquipBtn(33, 378, 145, 50, "UNEQUIP", BROWN),
                                                         EquipBtn(33, 378, 145, 50, "EQUIP", BROWN),
                                                         SellBtn(33, 320, 145, 50, "SELL", RED)

{
    
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            string id = to_string(i) + to_string(j);
            ItemSlot.insert({id, Button(316 + 73 * j, 42 + 70 * i, 46, 46)});
        }
    }

    curI = 0;
    curJ = 0;

    vector<string> equipment = {"Weapon",
                                "Head",
                                "Body",
                                "Leg",
                                "Pendant"};

    for (size_t i = 0; i < 5; i++)
    {
        EquippedItem.insert({equipment[i], Button(318 + 110 * i, 380, 46, 46)});
    }

    toggleEquipment = false;
    sellToggle = false;
    current = nullptr;
    currentType = "";
}

InventoryScreen::~InventoryScreen()
{
}

void InventoryScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    Texture2D bg = LoadTexture("./Assets/InventoryScreen/InventoryScreen.png");
    DrawTexture(bg, 0, 0, WHITE);
    
    ExitBtn.draw();
    DungeonBtn.draw();
    ShopBtn.draw();
    SkillBtn.draw();
    InventoryBtn.draw();
    HomeBtn.draw();

    
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            string id = to_string(i) + to_string(j);
            ItemSlot.at(id).draw();

            try
            {
                if (getGameState().getInventory()->getItemAt(i, j) == nullptr)
                {
                    throw string("");
                }
                string slotId = getGameState().getInventory()->getItemAt(i, j)->getID();
                string count = string("[ ") + to_string(getGameState().getInventory()->getQuantityAt(i, j)) + string(" ]");
                DrawText(slotId.c_str(), 328 + 73 * j, 48 + 70 * i, 13, BLACK);
                DrawText(count.c_str(), 328 + 73 * j, 65 + 70 * i, 13, BLACK);
            }
            catch (string &e)
            {
                
            }

            if (ItemSlot.at(id).isClicked())
            {
                toggleEquipment = false;

                try
                {
                    current = getGameState().getInventory()->getItemAt(i, j);
                    if (current == nullptr)
                    {
                        throw string("Slot kosong !");
                    }

                    curI = i;
                    curJ = j;
                    info = {
                        string("Name    : ") + current->getName(),
                        string("Type    : ") + current->getType(),
                        string("Rarity  : ") + string(1, current->getRarity()),
                        string("BaseStat: ") + std::to_string(current->getBaseStat()),
                        string("Price   : ") + std::to_string(current->getPrice()),
                        string("Sell Price : ") + std::to_string(current->getSellPrice()),
                    };

                    vector<Effect *> effects = current->getEffects();
                    if (!effects.empty())
                    {
                        info.push_back(string("Effects:"));
                        for (Effect *effect : effects)
                        {
                            info.push_back(string("- ") + effect->getName());
                        }
                    }

                    if (current->getType() != "Potion")
                    {
                        equipToggle = true;
                    }
                    sellToggle = true;
                }
                catch (const string &e)
                {
                    info = {};
                    popUp.trigger(e, RED, 0.5);
                }
            }
        }
    }

    
    if (getGameState().getInventory()->getWeapon() != nullptr)
    {
        DrawText(getGameState().getInventory()->getWeapon()->getID().c_str(), 328 + 110 * 0, 395, 13, BLACK);
    }
    
    if (getGameState().getInventory()->getHead() != nullptr)
    {
        DrawText(getGameState().getInventory()->getHead()->getID().c_str(), 328 + 110 * 1, 395, 13, BLACK);
    }
    
    if (getGameState().getInventory()->getBody() != nullptr)
    {
        DrawText(getGameState().getInventory()->getBody()->getID().c_str(), 328 + 110 * 2, 395, 13, BLACK);
    }
    
    if (getGameState().getInventory()->getFoot() != nullptr)
    {
        DrawText(getGameState().getInventory()->getFoot()->getID().c_str(), 328 + 110 * 3, 395, 13, BLACK);
    }
    
    if (getGameState().getInventory()->getPendant() != nullptr)
    {
        DrawText(getGameState().getInventory()->getPendant()->getID().c_str(), 328 + 110 * 4, 395, 13, BLACK);
    }

    
    for (auto it = EquippedItem.begin(); it != EquippedItem.end(); it++)
    {
        it->second.draw();
        currentType = it->first;

        if (it->second.isClicked())
        {
            try
            {
                toggleEquipment = true;
                equipToggle = false;
                sellToggle = false;
                
                if (it->first == "Weapon")
                {
                    current = getGameState().getInventory()->getWeapon();
                }
                else if (it->first == "Head")
                {
                    current = getGameState().getInventory()->getHead();
                }
                else if (it->first == "Body")
                {
                    current = getGameState().getInventory()->getBody();
                }
                else if (it->first == "Leg")
                {
                    current = getGameState().getInventory()->getFoot();
                }
                else if (it->first == "Pendant")
                {
                    current = getGameState().getInventory()->getPendant();
                }

                if (current == nullptr)
                {
                    toggleEquipment = false;
                    throw string("Slot empty !");
                }

                info = {
                    string("Name    : ") + current->getName(),
                    string("Type    : ") + current->getType(),
                    string("Rarity  : ") + string(1, current->getRarity()),
                    string("BaseStat: ") + std::to_string(current->getBaseStat()),
                    string("Price   : ") + std::to_string(current->getPrice()),
                    string("Sell Price : ") + std::to_string(current->getSellPrice()),
                };

                vector<Effect *> effects = current->getEffects();
                if (!effects.empty())
                {
                    info.push_back(string("Effects:"));
                    for (Effect *effect : effects)
                    {
                        info.push_back(string("- ") + effect->getName());
                    }
                }
            }
            catch (const std::string &e)
            {
                info = {};
                popUp.trigger(e, RED, 0.5);
                current = nullptr;
                sellToggle = false;
                equipToggle = false;
            }
        }
    }

    
    drawList(info, 20, 112, 15, WHITE);

    
    if (toggleEquipment)
    {
        unEquipBtn.draw();

        if (unEquipBtn.isClicked())
        {
            try
            {
                if (current == nullptr)
                {
                    throw string("current item null");
                }

                Item *itemToAdd = current;

                
                getGameState().getInventory()->unequipItem(current);

                
                *getGameState().getInventory() += itemToAdd;

                
                getGameState().getCharacter()->unequipItem(current);
                current = nullptr;
                info.clear();
                toggleEquipment = false;


            }
            catch (const std::string &e)
            {
                popUp.trigger(e, RED, 0.5);
                popUp.show();
            }
        }
    }

    if (sellToggle)
    {
        SellBtn.draw();
        if (SellBtn.isClicked())
        {
            try
            {
                if (getGameState().getInventory()->getQuantityAt(curI, curJ) < 1)
                {
                    throw string("Invalid quantity");
                }

                getGameState().getShop()->sellItem(current);

                int gold = getGameState().getCharacter()->getGold();
                
                getGameState().getCharacter()->setGold(gold + current->getSellPrice());
                getGameState().getInventory()->removeItem(current->getID());
            }
            catch (const string &e)
            {
                popUp.trigger(e, RED, 0.5);
                popUp.show();
            }
        }
    }

    if (equipToggle)
    {
        EquipBtn.draw();

        if (EquipBtn.isClicked())
        {
            try
            {
                if (current == nullptr)
                {
                    throw string("current item null");
                }

                Item *itemToAdd = current;

                
                getGameState().getInventory()->equipItem(current);

                
                getGameState().getInventory()->removeItem(current->getID());
                getGameState().getCharacter()->equipItem(current);

                
                current = nullptr;
                info.clear();
                equipToggle = false;

                
            }
            catch (const std::string &e)
            {
                popUp.trigger(e, RED, 0.5);
                popUp.show();
            }
        }
    }

    
    if (HomeBtn.isClicked())
    {
        setNext("HomeScreen");
    }
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

    popUp.update();
    popUp.draw();
}