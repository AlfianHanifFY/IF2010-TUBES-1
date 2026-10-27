#include "GUI/Screen/EndDungeonScreen/EndDungeonScreen.hpp"

EndDungeonScreen::EndDungeonScreen(GameState &GameState) : Screen(GameState), TitleBtn(357, 456, 144, 42, "HOME", RED), popUp()
{
    bg = LoadTexture("./Assets/DungeonScreen/EndDungeonScreen.png");
}

EndDungeonScreen::~EndDungeonScreen() {}

void EndDungeonScreen::Draw()
{

    ClearBackground(LIGHTGRAY);
    DrawTexture(bg, 0, 0, WHITE);

    TitleBtn.draw();
    if (getPrize == false)
    {
        if (getGameState().getDungeon() != nullptr)
        {
            if (getGameState().getDungeon()->getIsWin())
            {
                
                int scale = 1;

                if (getGameState().getDungeon()->getIsDouble())
                {
                    scale = 3;
                }

                info = {
                    "Mastery Point = " + to_string(getGameState().getDungeon()->getMasteryPrize() * scale),
                    "Dungeon Gold Bonus = " + to_string(getGameState().getDungeon()->getGoldPrize() * scale),
                    "Dungeon Exp Bonus = " + to_string(getGameState().getDungeon()->getExpPrize() * scale),
                    "Items from mobs : "};

                vector<Item *> itemPrize = getGameState().getMobLoot();
                for (auto i = itemPrize.begin(); i != itemPrize.end(); i++)
                {

                    try
                    {
                        for (size_t x = 0; x < scale; x++)
                        {
                            itemInfo.push_back(" - " + (*i)->getName());
                            *getGameState().getInventory() += (*i);
                        }
                    }
                    catch (string &e)
                    {
                        popUp.trigger(e, RED, 0.5);
                        popUp.show();
                    }
                }

                getGameState().getCharacter()->addMastery(getGameState().getDungeon()->getMasteryPrize() * scale);
                getGameState().getCharacter()->addGold(getGameState().getDungeon()->getGoldPrize() * scale);
                getGameState().getCharacter()->addExp(getGameState().getDungeon()->getExpPrize() * scale);
            }
            else
            {
                
                info = {
                    "Gold Penalty =  " + to_string(getGameState().getDungeon()->getGoldPenalty()),
                    "Exp Penalty = " + to_string(getGameState().getDungeon()->getExpPenalty()),
                    "Got NO item from MOBS "};

                getGameState().getCharacter()->addGold(getGameState().getDungeon()->getGoldPenalty());
                getGameState().getCharacter()->addExp(getGameState().getDungeon()->getExpPenalty());
            }
        }

        
        getPrize = true;
    }

    DrawText("Dungeon Result", 210, 43, 64, WHITE);
    drawListCol(info, 165, 126, 15, 25, 250, 15, WHITE);
    drawListCol(itemInfo, 165, 220, 9, 25, 250, 15, WHITE);

    if (TitleBtn.isClicked())
    {
        getPrize = true;
        getGameState().getShop()->restock(getGameState().getItems());
        setNext("HomeScreen");

        getGameState().setDungeon(nullptr);
        getGameState().getCharacter()->reset();
    }

    popUp.update();
    popUp.draw();
}
