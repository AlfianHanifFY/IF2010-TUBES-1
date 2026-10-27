#include "GUI/Screen/DungeonSelectionScreen/DungeonSelectionScreen.hpp"

DungeonSelectionScreen::DungeonSelectionScreen(GameState &GameState) : Screen(GameState),
                                                                       ERankBtn(40, 451, 90, 42, "SELECT", ORANGE),
                                                                       DRankBtn(40 + 160, 451, 90, 42, "SELECT", ORANGE),
                                                                       CRankBtn(40 + 160 * 2, 451, 90, 42, "SELECT", ORANGE),
                                                                       BRankBtn(40 + 160 * 3, 451, 90, 42, "SELECT", ORANGE),
                                                                       ARankBtn(40 + 160 * 4, 451, 90, 42, "SELECT", ORANGE),
                                                                       SRankBtn(40 + 160 * 5, 451, 90, 42, "SELECT", ORANGE),
                                                                       SpecialRankBtn(24, 27, 110, 50, "SPECIAL", PURPLE),
                                                                       ExitBtn(898, 9, 52, 45, "X", RED),
                                                                       popUp()
{
}

DungeonSelectionScreen::~DungeonSelectionScreen() {}

void DungeonSelectionScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    Texture2D bg = LoadTexture("./Assets/DungeonSelectionScreen/DungeonSelection.png");

    DrawTexture(bg, 0, 0, WHITE);

    ERankBtn.draw();
    DRankBtn.draw();
    CRankBtn.draw();
    BRankBtn.draw();
    ARankBtn.draw();
    SRankBtn.draw();
    SpecialRankBtn.draw();
    ExitBtn.draw();

    

    DrawText("Select Dungeon", 322, 20, 42, WHITE);
    DrawText("E", 67, 160, 64, BLACK);
    DrawText("D", 67 + 160 * 1, 160, 64, BLACK);
    DrawText("C", 67 + 160 * 2, 160, 64, BLACK);
    DrawText("B", 62 + 160 * 3, 160, 64, BLACK);
    DrawText("A", 60 + 160 * 4, 160, 64, BLACK);
    DrawText("S", 60 + 160 * 5, 160, 64, BLACK);
    vector<string> RankSDesc = {
        "- Min level: 50+",
        "- Mob level: 50-100",
        "- Fee: 1000 gold",
        "- Chambers: 6"};

    vector<string> RankADesc = {
        "- Min level: 35+",
        "- Mob level: 30-70",
        "- Fee: 500 gold",
        "- Chambers: 5"};

    vector<string> RankBDesc = {
        "- Min level: 25+",
        "- Mob level: 20-50",
        "- Fee: 300 gold",
        "- Chambers: 4"};

    vector<string> RankCDesc = {
        "- Min level: 20+",
        "- Mob level: 10-35",
        "- Fee: 150 gold",
        "- Chambers: 3"};

    vector<string> RankDDesc = {
        "- Min level: 10+",
        "- Mob level: 0-25",
        "- Fee: 0 gold",
        "- Chambers: 2"};

    vector<string> RankEDesc = {
        "- Min level: 0+",
        "- Mob level: 0-10",
        "- Fee: 0 gold",
        "- Chambers: 1"};

    vector<string> SpecialRankDesc = {
        "- No min level",
        "- Mob level: 0-?",
        "- No entry fee",
        "- Chambers: 100 tiered"};

    drawList(RankEDesc, 24, 278, 15, WHITE);
    drawList(RankDDesc, 24 + 162 * 1, 278, 13, WHITE);
    drawList(RankCDesc, 24 + 162 * 2, 278, 13, WHITE);
    drawList(RankBDesc, 24 + 162 * 3, 278, 13, WHITE);
    drawList(RankADesc, 15 + 162 * 4, 278, 13, WHITE);
    drawList(RankSDesc, 15 + 162 * 5, 278, 13, WHITE);

    if (ERankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankE());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank E !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank E !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }

    if (DRankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankD());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank D !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank D !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }

    if (CRankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankC());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank C !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank C !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }

    if (BRankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankB());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank B !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank B !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }

    if (ARankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankA());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank A !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank A !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }
    if (SRankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonRankS());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            if (getGameState().getDungeon()->getIsDouble())
            {
                popUp.trigger("[WARNING] Entering Double Dungeon Rank S !", RED, 0.5);
                popUp.show();
            }
            else
            {
                popUp.trigger("Entering Dungeon Rank S !", GREEN, 0.5);
                popUp.show();
            }
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }
    if (SpecialRankBtn.isClicked())
    {
        getGameState().setDungeon(new DungeonSpecial());
        if (getGameState().getDungeon()->canEnter(getGameState().getCharacter()))
        {
            popUp.trigger("Entering Dungeon Rank Special !", GREEN, 0.5);
            popUp.show();
        }
        else
        {
            getGameState().setDungeon(nullptr);
            popUp.trigger("You are not worthy enough !", RED, 0.5);
            popUp.show();
        }
    }

    if (ExitBtn.isClicked())
    {
        setNext("HomeScreen");
    }

    popUp.update();
    popUp.draw();

    if (getGameState().getDungeon() != nullptr && !popUp.isVisible)
    {
        
        getGameState().getCharacter()->useGold(getGameState().getDungeon()->getGoldCost());
        setNext("DungeonScreen");
    }
}