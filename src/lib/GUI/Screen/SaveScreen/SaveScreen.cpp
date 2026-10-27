#include "GUI/Screen/SaveScreen/SaveScreen.hpp"

SaveScreen::SaveScreen(GameState &GameState) : Screen(GameState),
                                               configInput({76, 440}, 728 - 76, 35),
                                               submitBtn(755, 430, 900 - 755, 476 - 430, "ENTER", GREEN),
                                               popUp(),
                                               exitBtn(898, 9, 52, 45, "X", RED)
{
}

void SaveScreen::Draw()
{
    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/SaveScreen/SaveScreen.png");
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("Save Config : ", 78, 384, 35, BLACK);
    configInput.Update();

    configInput.Draw();
    submitBtn.draw();
    exitBtn.draw();

    if (exitBtn.isClicked())
    {
        setNext("ExitScreen");
    }

    if (submitBtn.isClicked())
    {
        try
        {
            string filename = "./data/" + configInput.GetText();
            getGameState().saveConfig(filename);
            popUp.trigger("Save Config Success", GREEN, 0.8);
            popUp.show();
        }
        catch (string &e)
        {
            popUp.trigger(e, RED, 0.8);
            popUp.show();
        }
    }
    popUp.update();
    popUp.draw();
}
