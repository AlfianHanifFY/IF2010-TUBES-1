#include "GUI/Screen/LoadScreen/LoadScreen.hpp"

LoadScreen::LoadScreen(GameState &GameState) : Screen(GameState),
                                               configInput({76, 440}, 728 - 76, 35),
                                               submitBtn(755, 430, 900 - 755, 476 - 430, "ENTER", GREEN),
                                               popUp()
{
    valid = false;
}

void LoadScreen::Draw()
{

    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/LoadScreen/LoadScreen.png");
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("Config : ", 78, 384, 35, BLACK);
    configInput.Update();

    configInput.Draw();
    submitBtn.draw();

    if (submitBtn.isClicked())
    {
        try
        {
            string path = string("./data/") + configInput.GetText();
            if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
            {

                getGameState().loadConfig(path);
                getGameState().setConfigPath(configInput.GetText());
                valid = true;
                popUp.trigger("Horay, Load success !", GREEN, 0.8);
                popUp.show();
            }
            else
            {
                throw string("Folder not found...");
            }
        }
        catch (string &e)
        {
            popUp.trigger(e, RED, 0.8);
            popUp.show();
        }
    }
    popUp.update();
    popUp.draw();

    if (valid && !popUp.isVisible)
    {
        if (getGameState().getNewGame())
        {
            setNext("CharacterSelectionScreen");
        }
        else
        {
            setNext("HomeScreen");
        }
    }
}
