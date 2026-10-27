#include "GUI/Screen/CharacterSelectionScreen/CharacterSelectionScreen.hpp"

CharAnimation FighterChar;
CharAnimation MageChar;
CharAnimation AssasinChar;
CharAnimation NecromancerChar;
CharAnimation BersekerChar;

CharacterSelectionScreen::CharacterSelectionScreen(GameState &gs) : Screen(gs),
                                                                    FighterBtn(30, 451, 120, 42, "SELECT", ORANGE),
                                                                    MageBtn(30 + 180, 451, 120, 42, "SELECT", ORANGE),
                                                                    AssasinBtn(30 + 180 * 2, 451, 120, 42, "SELECT", ORANGE),
                                                                    NecromancerBtn(30 + 180 * 3, 451, 120, 42, "SELECT", ORANGE),
                                                                    BersekerBtn(30 + 180 * 4, 451, 120, 42, "SELECT", ORANGE),
                                                                    ExitBtn(898, 9, 52, 45, "X", RED),
                                                                    nameInput({254, 40}, 630 - 250, 20),
                                                                    popUp("Who are you ? please fill your name", 1.5, RED)

{

    FighterChar.Init("./Assets/Unit/Character/Fighter/idle.png", 6, 6, 2.5f, 2.5f, {-20.0f, 78.0f});
    MageChar.Init("./Assets/Unit/Character/Mage/idle.png", 6, 6, 2.5f, 2.5f, {155.0f, 78.0f});
    AssasinChar.Init("./Assets/Unit/Character/Assasin/idle.png", 6, 6, 2.5f, 2.5f, {340.0f, 78.0f});
    NecromancerChar.Init("./Assets/Unit/Character/Necromancer/idle.png", 6, 6, 2.5f, 2.5f, {515.0f, 78.0f});
    BersekerChar.Init("./Assets/Unit/Character/Berseker/idle.png", 6, 6, 2.5f, 2.5f, {695.0f, 82.0f});
}

CharacterSelectionScreen::~CharacterSelectionScreen() {}

void CharacterSelectionScreen::Draw()
{
    ClearBackground(LIGHTGRAY);

    Texture2D bg = LoadTexture("./Assets/CharacterSelectionScreen/CharacterSelection.png");

    nameInput.Update();
    DrawTexture(bg, 0, 0, WHITE);

    
    FighterChar.UpdateChar();
    MageChar.UpdateChar();
    AssasinChar.UpdateChar();
    NecromancerChar.UpdateChar();
    BersekerChar.UpdateChar();

    FighterChar.DrawChar();
    MageChar.DrawChar();
    AssasinChar.DrawChar();
    NecromancerChar.DrawChar();
    BersekerChar.DrawChar();

    FighterBtn.draw();
    MageBtn.draw();
    AssasinBtn.draw();
    NecromancerBtn.draw();
    BersekerBtn.draw();
    ExitBtn.draw();

    nameInput.Draw();

    DrawText("FIGHTER", 49 + 180 * 0, 242, 18, WHITE);
    DrawText("MAGE", 64 + 180 * 1, 242, 18, WHITE);
    DrawText("ASSASIN", 50 + 180 * 2, 242, 18, WHITE);
    DrawText("NECROMANCER", 28 + 180 * 3, 242, 18, WHITE);
    DrawText("BERSEKER", 47 + 180 * 4, 242, 18, WHITE);
    DrawText("NAME :", 150, 45, 25, WHITE);

    vector<string> FighterDesc = {
        "- Strong fighter",
        "- Can block attacks",
        "- Skill heals with",
        "  strength",
        "- Level up boosts all,",
        "  strength the most"};

    vector<string> MageDesc = {
        "- Smart spellcaster",
        "- Attack adds mana",
        "- Skill uses mana &",
        "  deals magic damage",
        "- Level up boosts all,",
        "  intelligence most"};

    vector<string> AssasinDesc = {
        "- Fast and deadly",
        "- Critical chance on",
        "  attack",
        "- Can dodge hits",
        "- Level up boosts all,",
        "  agility the most"};

    vector<string> NecromancerDesc = {
        "- Summons minions",
        "- Attack may summon",
        "- Minions attack next",
        "- Skill lifesteals HP",
        "- Level up boosts all,",
        "  intelligence most",
        "- Reset summon after",
        "  battle"};

    vector<string> BersekerDesc = {
        "- Powered by rage",
        "- Attack builds rage",
        "- Skill boosts rage",
        "- Level up boosts all,",
        "  strength the most",
        "- Reset rage after",
        "  battle"};

    drawList(FighterDesc, 16, 284, 13, WHITE);
    drawList(MageDesc, 16 + 178 * 1, 284, 13, WHITE);
    drawList(AssasinDesc, 16 + 178 * 2, 284, 13, WHITE);
    drawList(NecromancerDesc, 16 + 178 * 3, 284, 13, WHITE);
    drawList(BersekerDesc, 16 + 178 * 4, 284, 13, WHITE);

    
    if (FighterBtn.isClicked())
    {

        if (nameInput.GetText() == "")
        {
            popUp.show();
        }
        else
        {
            popUp.trigger("Starting journey with Fighter !", GREEN, 1.5);
            popUp.show();
            getGameState().setCharacter(new Fighter(nameInput.GetText()));
        }
    }

    if (MageBtn.isClicked())
    {

        if (nameInput.GetText() == "")
        {
            popUp.show();
        }
        else
        {
            popUp.trigger("Starting journey with Mage !", GREEN, 1.5);
            popUp.show();
            getGameState().setCharacter(new Mage(nameInput.GetText()));
        }
    }

    if (AssasinBtn.isClicked())
    {
        if (nameInput.GetText() == "")
        {
            popUp.show();
        }
        else
        {
            popUp.trigger("Starting journey with Assasin !", GREEN, 1.25);
            popUp.show();
            getGameState().setCharacter(new Assasin(nameInput.GetText()));
        }
    }

    if (NecromancerBtn.isClicked())
    {
        if (nameInput.GetText() == "")
        {
            popUp.show();
        }
        else
        {
            popUp.trigger("Starting journey with Necromancer !", GREEN, 1.5);
            popUp.show();
            getGameState().setCharacter(new Necromancer(nameInput.GetText()));
        }
    }

    if (BersekerBtn.isClicked())
    {
        if (nameInput.GetText() == "")
        {
            popUp.show();
        }
        else
        {
            popUp.trigger("Starting journey with Berserker !", GREEN, 1.5);
            popUp.show();
            getGameState().setCharacter(new Berserker(nameInput.GetText()));
        }
    }

    if (ExitBtn.isClicked())
    {
        setNext("StartScreen");
    }

    popUp.update();
    popUp.draw();

    if (getGameState().getCharacter() != nullptr && !popUp.isVisible)
    {
        try
        {
            getGameState().getCharacter()->equipItem(getGameState().getInventory()->getHead());
        }
        catch (string &e)
        {
        }

        try
        {
            getGameState().getCharacter()->equipItem(getGameState().getInventory()->getBody());
        }
        catch (string &e)
        {
        }

        try
        {
            getGameState().getCharacter()->equipItem(getGameState().getInventory()->getFoot());
        }
        catch (string &e)
        {
        }

        try
        {
            getGameState().getCharacter()->equipItem(getGameState().getInventory()->getWeapon());
        }
        catch (string &e)
        {
        }

        try
        {
            getGameState().getCharacter()->equipItem(getGameState().getInventory()->getPendant());
        }
        catch (string &e)
        {
        }

        setNext("HomeScreen");
    }
}
