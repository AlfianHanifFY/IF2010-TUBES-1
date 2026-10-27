#include "GUI/Screen/ShopScreen/ShopScreen.hpp"

ShopScreen::ShopScreen(GameState &GameState) : Screen(GameState), ExitBtn(828, 462, 951 - 828, 531 - 462, "EXIT", RED),
                                               SkillBtn(702, 462, 824 - 702, 531 - 462, "SKILL", BROWN),
                                               ShopBtn(482, 462, 698 - 482, 531 - 462, "SHOP", BROWN),
                                               InventoryBtn(242, 462, 477 - 242, 531 - 462, "INVENTORY", BROWN),
                                               DungeonBtn(8, 462, 238 - 8, 531 - 462, "DUNGEON", ORANGE),
                                               WeaponBtn(243, 9, 171, 51, "WEAPON", GRAY),
                                               ArmorBtn(243 + 173, 9, 171, 51, "ARMOR", GRAY),
                                               PotionBtn(243 + 173 * 2, 9, 171, 51, "POTION", GRAY),
                                               PendantBtn(243 + 173 * 3, 9, 180, 51, "PENDANT", GRAY),
                                               HomeBtn(190, 416, 235 - 190, 451 - 416, "<<", GRAY),
                                               leftBtn(389, 374, 50, 50),
                                               rightBtn(723, 379, 50, 50),
                                               BuyBtn(33, 378, 145, 50, "BUY", BROWN),
                                               current(nullptr),
                                               popUp()
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            string id = to_string(i) + to_string(j);
            itemBtn.insert({id, Button(304 + (456 - 296) * j, 90 + (252 - 90) * i, 100, 100)});
        }
    }
    page = 0;
    itemsPerPage = 8;
    toggle = false;
    idx = -1;
    section = "";
}

ShopScreen::~ShopScreen()
{
}

void ShopScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    Texture2D bg = LoadTexture("./Assets/ShopScreen/ShopScreen.png");
    DrawTexture(bg, 0, 0, WHITE);
    
    ExitBtn.draw();
    DungeonBtn.draw();
    ShopBtn.draw();
    SkillBtn.draw();
    InventoryBtn.draw();

    WeaponBtn.draw();
    ArmorBtn.draw();
    PotionBtn.draw();
    PendantBtn.draw();

    HomeBtn.draw();

    leftBtn.draw();
    rightBtn.draw();

    DrawText((string("$") + to_string(getGameState().getCharacter()->getGold())).c_str(), 108, 28, 32, YELLOW);

    
    int col = 4;
    int gap = 0;
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int index = page * itemsPerPage + (i * col + j);
            if (index < itemShop.size())
            {
                
                string id = to_string(i) + to_string(j);
                itemBtn.at(id).draw();

                
                if (itemBtn.at(id).isClicked())
                {
                    toggle = true;
                    current = &itemShop.at(index); 
                    
                    if (current != nullptr)
                    {
                        info = {
                            string("Name        : ") + current->getItem()->getName(),
                            string("Type        : ") + current->getItem()->getType(),
                            string("Rarity      : ") + string(1, current->getItem()->getRarity()),
                            string("BaseStat    : ") + std::to_string(current->getItem()->getBaseStat()),
                            string("Base Price  : ") + std::to_string(current->getItem()->getPrice()),
                            string("Buy Price   : ") + std::to_string(current->getItem()->getBuyPrice()),
                            string("Quantity    : ") + std::to_string(current->getQuantity()),
                        };
                        idx = index;
                        vector<Effect *> effects = current->getItem()->getEffects();
                        if (!effects.empty())
                        {
                            info.push_back(string("Effects:"));
                            for (Effect *effect : effects)
                            {
                                info.push_back(string("- ") + effect->getName());
                            }
                        }
                    }
                }

                
                if (j > 1)
                {
                    gap = 20;
                }
                else
                {
                    gap = 0;
                }

                
                DrawText(itemShop.at(index).getItem()->getID().c_str(), 324 + (456 - 296) * j + gap, 105 + (252 - 90) * i, 20, BLACK);
            }
        }
        drawList(info, 20, 112, 15, WHITE);

        if (toggle)
        {
            BuyBtn.draw();
            if (BuyBtn.isClicked())
            {
                try
                {
                    if (current->getQuantity() < 1)
                    {
                        throw string("Stock Empty");
                    }

                    if (getGameState().getCharacter()->getGold() >= current->getItem()->getBuyPrice())
                    {
                        getGameState().getShop()->buyItem(current->getItem()->getID());
                        int curGold = getGameState().getCharacter()->getGold();
                        getGameState().getCharacter()->setGold(curGold - current->getItem()->getBuyPrice());
                        
                        *getGameState().getInventory() += current->getItem();
                        
                        toggle = false;
                        
                        popUp.trigger(string("You Buy a ") + current->getItem()->getName(), GREEN, 0.5);
                        popUp.show();

                        
                        itemShop = getGameState().getShop()->getItemsByType(section); 
                    }
                    else
                    {
                        throw string("Not Enough gold, you poor !");
                    }
                }
                catch (string &e)
                {
                    popUp.trigger(e, RED, 0.5);
                    popUp.show();
                }
            }
        }

        if (leftBtn.isClicked())
        {
            if (page > 0)
                page--;
        }

        if (rightBtn.isClicked())
        {
            if ((page + 1) * itemsPerPage < itemShop.size())
                page++;
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

        if (WeaponBtn.isClicked())
        {
            itemShop = getGameState().getShop()->getItemsByType("Weapon");
            section = "Weapon";
            page = 0;
        }
        if (ArmorBtn.isClicked())
        {
            itemShop = getGameState().getShop()->getItemsByType("Armor");
            section = "Armor";
            page = 0;
        }
        if (PotionBtn.isClicked())
        {
            itemShop = getGameState().getShop()->getItemsByType("Potion");
            section = "Potion";
            page = 0;
        }
        if (PendantBtn.isClicked())
        {
            itemShop = getGameState().getShop()->getItemsByType("Pendant");
            section = "Pendant";
            page = 0;
        }
        popUp.update();
        popUp.draw();
    }
}
