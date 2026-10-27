#include "GUI/Screen/DungeonScreen/DungeonScreen.hpp"

DungeonScreen::DungeonScreen(GameState &GameState) : Screen(GameState),
                                                     EscapeBtn(828, 462, 951 - 828, 531 - 462, "EXIT", RED),
                                                     LogBtn(702, 462, 824 - 702, 531 - 462, "LOG", BROWN),
                                                     ItemBtn(482, 462, 698 - 482, 531 - 462, "ITEM", BROWN),
                                                     SkillBtn(242, 462, 477 - 242, 531 - 462, "SKILL", BROWN),
                                                     AttackBtn(8, 462, 238 - 8, 531 - 462, "ATTACK", ORANGE),
                                                     CancelBtn(898, 9, 52, 45, "X", RED),
                                                     CharAnim(getGameState().getCharacter()->getAssets()),
                                                     CharBtn(420, 240, 80, 80),
                                                     popUp(),
                                                     UseBtn(33, 320, 145, 50, "USE", RED),
                                                     Skill1Btn(374 + 70, 144 + 70, 120, 120, "Skill 1", BLUE),
                                                     Skill2Btn(374 + 260, 144 + 70, 120, 120, "Skill 2", BLUE),
                                                     SummonAnim("./Assets/Unit/Character/Necromancer/Keroco")

{
    getGameState().getCharacter()->reset();
    getGameState().getCharacter()->applyItemEffect();
    toggle.insert({"Attack", false});
    toggle.insert({"Skill", false});
    toggle.insert({"Item", false});
    toggle.insert({"Log", false});
    selectedUnit = nullptr;
    BackPack = LoadTexture("./Assets/DungeonScreen/BackPack.png");
    SkillPack = LoadTexture("./Assets/DungeonScreen/SkillPack.png");

    getGameState().getDungeon()->populate();

    playerTurn = true;
    enemyTurn = false;
    CharAnim.Play("idle");
    SummonAnim.Play("idle");

    profilePath = "";
    selectedEnemyPos = -1;

    vector<Mob *> chamberMob = getGameState().getDungeon()->getChamberMob();

    for (auto it = chamberMob.begin(); it != chamberMob.end(); it++)
    {
        mobAnimations.push_back(new Animation((*it)->getAssets(), 0.1));
        if (!isAction)
        {
            mobAnimations.back()->Play("idle");
        }
    }

    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            string id = to_string(i) + to_string(j);
            ItemSlot.insert({id, Button(380 + 96 * j, 144 + 75 * i, 65, 65)});
        }
    }

    actionDuration = 1.35f;
    currentItem = nullptr;
    currenSkill = nullptr;
    getPrize = false;

    atkSound = LoadSound("./Assets/sfx/battle/slash.wav");
    bg = LoadTexture("./Assets/DungeonScreen/DungeonScreenA.png");

    
    
    
}

DungeonScreen::~DungeonScreen() {}

void DungeonScreen::setToggle(string name)
{
    for (auto it = toggle.begin(); it != toggle.end(); it++)
    {
        if (it->first == name)
        {
            it->second = true;
        }
        else
        {
            it->second = false;
        }
    }
    profilePath = "";
}

bool DungeonScreen::isToggle()
{
    for (auto it = toggle.begin(); it != toggle.end(); it++)
    {
        if (it->second == true)
        {
            return true;
        }
    }
    return false;
}

void DungeonScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    vector<Mob *> chamberMob = getGameState().getDungeon()->getChamberMob();

    DrawTexture(bg, 0, 0, WHITE);

    if (profilePath != "")
    {
        Texture2D profile = LoadTexture(profilePath.c_str());
        DrawTexture(profile, 25, 31, WHITE);
    }

    EscapeBtn.draw();
    LogBtn.draw();
    AttackBtn.draw();
    SkillBtn.draw();
    ItemBtn.draw();
    CharAnim.Update();
    CharAnim.Draw({444, 270}, 2.85);
    CharBtn.draw();
    int i = 0;

    if (getGameState().getCharacter()->getCharType() == "Necromancer")
    {
        int summonCount = getCountSummonFrom<Necromancer>(getGameState().getCharacter());

        const int baseX = 386;
        const int baseY = 205;
        const int offsetX = -72;
        const int offsetY = 64;
        const int maxPerColumn = 4;

        for (int i = 0; i < summonCount; ++i)
        {
            int column = i / maxPerColumn;
            int row = i % maxPerColumn;

            int drawX = baseX + column * offsetX;
            int drawY = baseY + row * offsetY;
            Vector2 summonPos = {static_cast<float>(drawX), static_cast<float>(drawY)};
            SummonAnim.Update();
            SummonAnim.Draw(summonPos, 2);
        }
    }

    if (log.size() > 19)
    {
        log.clear();
    }
    std::string chamberText = "Chamber : " +
                              std::to_string(getGameState().getDungeon()->getCurrentChamber()) + " / " +
                              std::to_string(getGameState().getDungeon()->getTotalChamber());

    DrawText(chamberText.c_str(), 20, 429, 14, WHITE);

    int numMobs = mobAnimations.size();
    float verticalSpacing = 80.0f; 
    float startY = 270.0f;         
    
    for (auto it = mobAnimations.begin(); it != mobAnimations.end(); it++)
    {
        
        float offsetY = (numMobs - 1) * verticalSpacing / 2.0f; 

        
        float mobY = startY + offsetY - i * verticalSpacing;

        Vector2 mobPosition = {700.0f, mobY}; 

        if (getGameState().getDungeon()->getChamberMob()[i]->getCurrentHealth() > 0)
        {
            (*it)->Update();
            if (getGameState().getDungeon()->getChamberMob()[i]->getType() == "Boss")
            {
                (*it)->Draw(mobPosition, 4);
            }
            else
            {
                (*it)->Draw(mobPosition, 2.85);
            }
        }

        
        if (CheckCollisionPointRec(GetMousePosition(), {mobPosition.x - 30, mobPosition.y - 30, 100, 50}) &&
            !toggle["Item"] && !(toggle["Skill"] && currenSkill == nullptr))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && getGameState().getDungeon()->getChamberMob()[i]->getCurrentHealth() > 0)
            {
                std::cout << "Mob " << i << " clicked!" << std::endl;
                
                selectedUnit = getGameState().getDungeon()->getChamberMob()[i];

                profilePath = "./Assets/profile/" + selectedUnit->getName() + ".png";
                selectedEnemyPos = i;
            }
        }

        i++;
    }

    if (CharBtn.isClicked() && !toggle["Item"] && !(toggle["Skill"] && currenSkill == nullptr))
    {
        selectedUnit = getGameState().getCharacter();
        profilePath = "./Assets/profile/" + getGameState().getCharacter()->getCharType() + ".png";
    }

    
    if (selectedUnit != nullptr && !isToggle())
    {
        DrawText(selectedUnit->getName().c_str(), 100, 26, 30, WHITE);
        DrawText(string("Rank " + selectedUnit->getRank()).c_str(), 100, 60, 15, WHITE);
        DrawText((string("Lvl.") + to_string(selectedUnit->getLevel())).c_str(), 100, 90, 15, WHITE);
        info = {
            "HEALTH = " + std::to_string(selectedUnit->getCurrentHealth()) + " / " + std::to_string(selectedUnit->getMaxHealth()),
            "MANA = " + std::to_string(selectedUnit->getCurrentMana()) + " / " + std::to_string(selectedUnit->getMaxMana()),
            "Base Attack = " + to_string(selectedUnit->getAttackDamage()),
            "Base Defense = " + to_string(selectedUnit->getDefense()),
            "Health Regen = " + to_string(selectedUnit->getHealthRegen()),
            "Mana Regen = " + to_string(selectedUnit->getManaRegen()),
            "Stat :",
            "  Inteligent = " + std::to_string(selectedUnit->getStat(1)),
            "  Strength = " + std::to_string(selectedUnit->getStat(0)),
            "  Agility = " + std::to_string(selectedUnit->getStat(2)),
            "Active Effect :"};
        vector<Effect *> effects = selectedUnit->getActiveEffects();
        for (auto i = effects.begin(); i != effects.end(); i++)
        {
            if ((*i)->getRemainingDuration() != -1)
            {
                info.push_back((*i)->getName() + " | (" + to_string((*i)->getRemainingDuration()) + ")");
            }
            else
            {
                info.push_back((*i)->getName() + " | (P)");
            }
        }

        drawList(info, 20, 122, 14, WHITE);
    }

    if (playerTurn)
    {
        if (getGameState().getCharacter()->getStunned())
        {
            popUp.trigger("Stunned ...", YELLOW, 0.2);
            popUp.show();
            if (!isAction)
            {
                actionTimer = 0.0f;
            }

            isAction = true;

            setToggle("");
            selectedUnit = nullptr;
        }

        if (toggle["Attack"])
        {

            blinkText("SELECT UNIT", 490, 14, 32);
            CancelBtn.draw();

            if (selectedUnit != nullptr && selectedUnit != getGameState().getCharacter())
            {
                int dmg = getGameState().getCharacter()->attack(selectedUnit);
                PlaySound(atkSound);
                if (!isAction)
                {
                    CharAnim.Play("attack");
                    SummonAnim.Play("attack");

                    if (getGameState().getDungeon()->getChamberMob()[selectedEnemyPos]->getCurrentHealth() > 0)
                    {
                        mobAnimations[selectedEnemyPos]->Play("hurt");
                    }
                    else
                    {
                        mobAnimations[selectedEnemyPos]->Play("death");
                    }
                }

                isAction = true;
                actionTimer = 0.0f;

                setToggle("");
                selectedUnit = nullptr;
            }
        }

        if (toggle["Skill"])
        {
            blinkText("SELECT SKILL & UNIT", 400, 14, 32);

            vector<Skill *> skills = getGameState().getCharacter()->getAllSkill();

            
            if (currenSkill == nullptr)
            {
                DrawTexture(SkillPack, 374, 144, WHITE);
                Skill1Btn.draw();
                Skill2Btn.draw();
                if (skills.size() > 0)
                {
                    if (Skill1Btn.isClicked())
                    {
                        DrawText("skill 1", 100, 100, 64, WHITE);
                        if (skills[0])
                        {
                            currenSkill = skills[0];
                        }
                    }
                    if (Skill2Btn.isClicked() && (skills.size() > 1))
                    {
                        DrawText("skill 2", 100, 100, 64, WHITE);
                        if (skills[1])
                        {
                            currenSkill = skills[1];
                        }
                    }
                }
                else
                {
                    popUp.trigger("No active skill", RED, 0.5);
                    popUp.show();
                    setToggle("");
                }
                selectedUnit = nullptr;
            }
            else
            {
                info = {
                    "Name = " + currenSkill->getName(),
                    "Mana Cost = " + to_string(currenSkill->getManaCost()),
                    "Mastery Cost = " + to_string(currenSkill->getMasteryCost()),
                    "Effect : ",
                };
                vector<Effect *> effects = currenSkill->getEffects();
                for (auto i = effects.begin(); i != effects.end(); i++)
                {
                    info.push_back(" - " + (*i)->getName());
                    info.push_back("   > " + (*i)->getDescription());
                    info.push_back("   > duration " + to_string((*i)->getDuration()));
                }
                drawList(info, 20, 122, 14, WHITE);

                
                if (selectedUnit != nullptr && selectedUnit != getGameState().getCharacter())
                {
                    getGameState().getCharacter()->useSkill(currenSkill, selectedUnit);
                    PlaySound(atkSound);
                    if (!isAction)
                    {
                        CharAnim.Play("attack");

                        if (getGameState().getDungeon()->getChamberMob()[selectedEnemyPos]->getCurrentHealth() > 0)
                        {
                            mobAnimations[selectedEnemyPos]->Play("hurt");
                        }
                        else
                        {
                            mobAnimations[selectedEnemyPos]->Play("death");
                        }
                    }

                    isAction = true;
                    actionTimer = 0.0f;

                    setToggle("");
                    selectedUnit = nullptr;
                    currenSkill = nullptr;
                }
            }

            CancelBtn.draw();
        }

        if (toggle["Item"])
        {
            blinkText("SELECT ITEM", 490, 14, 32);
            DrawTexture(BackPack, 374, 144, WHITE);

            
            vector<Item *> backpackItem = getGameState().getInventory()->getPotion();

            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 5; j++)
                {
                    string id = to_string(i) + to_string(j);
                    ItemSlot.at(id).draw();

                    
                    try
                    {
                        int idx = i * 5 + j;
                        if (idx >= backpackItem.size())
                        {
                            throw string("");
                        }

                        string slotId = backpackItem.at(idx)->getID();
                        string count = string("[ ") + to_string(getGameState().getInventory()->getItemQuantity(slotId)) + string(" ]");
                        DrawText(slotId.c_str(), 374 + 29 + 96 * j, 144 + 26 + 75 * i, 13, BLACK);
                        DrawText(count.c_str(), 374 + 32 + 96 * j, 144 + 45 + 75 * i, 13, BLACK);
                    }
                    catch (string &e)
                    {
                        
                    }

                    if (ItemSlot.at(id).isClicked())
                    {
                        try
                        {
                            if ((id[0] - '0') * 5 + (id[1] - '0') >= backpackItem.size())
                            {
                                currentItem = nullptr;
                                info = {};
                                throw string("Slot kosong");
                            }
                            currentItem = backpackItem.at((id[0] - '0') * 5 + (id[1] - '0'));

                            info = {
                                string("Name    : ") + currentItem->getName(),
                                string("Type    : ") + currentItem->getType(),
                                string("Rarity  : ") + string(1, currentItem->getRarity()),
                                string("BaseStat: ") + std::to_string(currentItem->getBaseStat()),
                                string("Price   : ") + std::to_string(currentItem->getPrice()),
                                string("Sell Price : ") + std::to_string(currentItem->getSellPrice()),
                            };

                            vector<Effect *> effects = currentItem->getEffects();
                            if (!effects.empty())
                            {
                                info.push_back(string("Effects:"));
                                for (Effect *effect : effects)
                                {
                                    info.push_back(string("- ") + effect->getName());
                                }
                            }
                        }
                        catch (const string &e)
                        {
                            popUp.trigger(e, RED, 0.5);
                        }
                    }
                }
            }
            if (currentItem != nullptr)
            {
                
                UseBtn.draw();
                if (UseBtn.isClicked())
                {
                    currentItem->use(getGameState().getCharacter());
                    getGameState().getInventory()->removeItem(currentItem->getID());
                    isAction = true;
                    actionTimer = 0.0f;

                    setToggle("");
                    selectedUnit = nullptr;
                }
            }
            drawList(info, 20, 122, 14, WHITE);
            CancelBtn.draw();
        }

        if (toggle["Log"])
        {
            blinkText("LOG", 470, 14, 32);
            DrawRectangle(270, 104, 922 - 270, 448 - 104, BLACK);
            drawList(log, 280, 120, 15, WHITE);
            CancelBtn.draw();
        }

        if (LogBtn.isClicked())
        {
            setToggle("Log");
        }
        if (AttackBtn.isClicked())
        {
            selectedUnit = nullptr;
            setToggle("Attack");
        }
        if (SkillBtn.isClicked())
        {
            setToggle("Skill");
        }
        if (ItemBtn.isClicked())
        {
            setToggle("Item");
        }
        if (CancelBtn.isClicked())
        {
            setToggle("");
        }
    }

    if (enemyTurn && !isAction)
    {
        bool isAtk = false;
        int n = 0;
        for (auto i = chamberMob.begin(); i != chamberMob.end(); i++)
        {
            if ((*i)->getCurrentHealth() > 0)
            {
                if (!(*i)->getStunned())
                {
                    (*i)->act(getGameState().getCharacter());
                    mobAnimations[n]->Play("attack");
                    CharAnim.Play("hurt");
                    SummonAnim.Play("hurt");
                    isAtk = true;
                }
            }
            n++;
        }

        if (isAtk)
        {
            PlaySound(atkSound);
        }

        isAction = true;
        actionTimer = 0.0f;

        setToggle("");
        selectedUnit = nullptr;
    }

    if (isAction)
    {
        actionTimer += GetFrameTime();
        if (actionTimer >= actionDuration)
        {
            isAction = false;
            actionTimer = 0.0f;

            
            CharAnim.Play("idle");
            SummonAnim.Play("idle");
            int n = 0;
            for (auto i = chamberMob.begin(); i != chamberMob.end(); i++)
            {
                mobAnimations[n]->Play("idle");

                n++;
            }

            

            if (playerTurn)
            {
                playerTurn = false;
                enemyTurn = true;
                
                
                
                
                getGameState().getCharacter()->tick();
            }
            else if (enemyTurn)
            {
                enemyTurn = false;
                playerTurn = true;

                for (auto i = chamberMob.begin(); i != chamberMob.end(); i++)
                {
                    (*i)->tick();
                    vector<string> logInfo = (*i)->getLog();
                    for (auto i = logInfo.begin(); i != logInfo.end(); i++)
                    {
                        log.push_back(*i);
                    }
                    (*i)->resetLog();
                }
            }

            vector<string> logInfo = getGameState().getCharacter()->getLog();
            for (auto i = logInfo.begin(); i != logInfo.end(); i++)
            {
                log.push_back(*i);
            }
            getGameState().getCharacter()->resetLog();
            for (auto i = chamberMob.begin(); i != chamberMob.end(); i++)
            {
                vector<string> logInfo = (*i)->getLog();
                for (auto i = logInfo.begin(); i != logInfo.end(); i++)
                {
                    log.push_back(*i);
                }
                (*i)->resetLog();
            }
        }
    }
    else
    {
        
        if (getGameState().getDungeon()->isChamberFinished())
        {
            if (!getPrize)
            {
                for (auto i = chamberMob.begin(); i != chamberMob.end(); i++)
                {
                    if ((*i)->getCurrentHealth() < 0)
                    {
                        getGameState().getCharacter()->addGold((*i)->getGoldReward());
                        getGameState().getCharacter()->addExp((*i)->getExpReward());
                        log.push_back("Getting " + to_string((*i)->getGoldReward()) + " gold from defeating " + (*i)->getName());
                        log.push_back("Getting " + to_string((*i)->getExpReward()) + " exp from defeating " + (*i)->getName());
                    }
                }
                getPrize = true;
            }

            
            if (getGameState().getDungeon()->isDungeonFinished())
            {
                getGameState().getDungeon()->setIsWin();
                popUp.trigger("You conquer this dungeon !", GREEN, 0.5);
                popUp.show();
                end = true;
            }
            else
            {
                getGameState().getDungeon()->nextChamber();
                popUp.trigger("Going to Next Chamber !", GREEN, 0.5);
                popUp.show();
                chamberMob = getGameState().getDungeon()->getChamberMob();
                mobAnimations = {};
                for (auto it = chamberMob.begin(); it != chamberMob.end(); it++)
                {
                    mobAnimations.push_back(new Animation((*it)->getAssets(), 0.1));
                    if (!isAction)
                    {
                        mobAnimations.back()->Play("idle");
                    }
                }
                
                
                CharAnim.Play("idle");
                SummonAnim.Play("idle");

                profilePath = "";
                selectedEnemyPos = -1;
                getPrize = false;
            }
        }

        
        if (getGameState().getCharacter()->getCurrentHealth() <= 0)
        {

            popUp.trigger("You Die !", RED, 0.5);
            popUp.show();
            end = true;
            if (getGameState().getDungeon()->getSpecial())
            {
                getGameState().getDungeon()->setIsWin();
            }
        }
    }

    if (EscapeBtn.isClicked())
    {
        getGameState().getCharacter()->reset();
        end = true;
        if (getGameState().getDungeon()->getSpecial())
        {
            getGameState().getDungeon()->setIsWin();
        }
        else
        {
            popUp.trigger("Run From this dungeon !", RED, 0.5);
            popUp.show();
        }
    }

    if (end)
    {
        endTimer += GetFrameTime();

        if (endTimer >= endDuration)
        {
            selectedUnit = nullptr;
            currenSkill = nullptr;
            setNext("EndDungeonScreen");
        }
    }

    popUp.update();
    popUp.draw();
}
