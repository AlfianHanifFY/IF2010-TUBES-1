#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include "GameState/GameState.hpp"
#include "GUI/CharAnimation/CharAnimation.hpp"
#include "GUI/TextInput/TextInput.hpp"
#include "GUI/GUI.hpp"
#include "GUI/Animation/Animation.hpp"
#include "GUI/Button/Button.hpp"
#include "GUI/Screen/ExitScreen/ExitScreen.hpp"
#include "GUI/Screen/ShopScreen/ShopScreen.hpp"
#include "GUI/Screen/CharacterSelectionScreen/CharacterSelectionScreen.hpp"
#include "GUI/Screen/LoadScreen/LoadScreen.hpp"
#include "GUI/Screen/StartScreen/StartScreen.hpp"
#include "GUI/Screen/DungeonSelectionScreen/DungeonSelectionScreen.hpp"
#include "GUI/Screen/InventoryScreen/InventoryScreen.hpp"
#include "GUI/Screen/SaveScreen/SaveScreen.hpp"
#include "GUI/Screen/DungeonScreen/DungeonScreen.hpp"
#include "GUI/Screen/EndDungeonScreen/EndDungeonScreen.hpp"
#include "GUI/Screen/Screen.hpp"
#include "GUI/Screen/InfoScreen/InfoScreen.hpp"
#include "GUI/Screen/HomeScreen/HomeScreen.hpp"
#include "GUI/Screen/SkillPathScreen/SkillPathScreen.hpp"

using namespace std;







































int main(void)
{
    InitAudioDevice();
    srand(static_cast<unsigned int>(time(nullptr)));
    GameState gs;
    const int DISPLAY_WIDTH = 960;
    const int DISPLAY_HEIGHT = 540;

    InitWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "akuAdalahOOP");
    SetTargetFPS(60);

    

    
    Screen *screen = new StartScreen(gs);
    bool RUN = true;

    while (!WindowShouldClose() && RUN)
    {
        
        std::string nextScreen = screen->getNext();

        if (nextScreen != "none")
        {
            delete screen; 

            try
            {
                if (nextScreen == "StartScreen")
                {
                    screen = new StartScreen(gs);
                }
                else if (nextScreen == "CharacterSelectionScreen")
                {
                    screen = new CharacterSelectionScreen(gs);
                }
                else if (nextScreen == "HomeScreen")
                {
                    screen = new HomeScreen(gs);
                }
                else if (nextScreen == "ExitScreen")
                {
                    screen = new ExitScreen(gs);
                }
                else if (nextScreen == "InfoScreen")
                {
                    screen = new InfoScreen(gs);
                }
                else if (nextScreen == "DungeonScreen")
                {
                    screen = new DungeonScreen(gs);
                }
                else if (nextScreen == "DungeonSelectionScreen")
                {
                    screen = new DungeonSelectionScreen(gs);
                }
                else if (nextScreen == "ShopScreen")
                {
                    screen = new ShopScreen(gs);
                }
                else if (nextScreen == "InventoryScreen")
                {
                    screen = new InventoryScreen(gs);
                }
                else if (nextScreen == "LoadScreen")
                {
                    screen = new LoadScreen(gs);
                }
                else if (nextScreen == "SkillScreen")
                {
                    screen = new SkillPathScreen(gs);
                }
                else if (nextScreen == "SaveScreen")
                {
                    screen = new SaveScreen(gs);
                }
                else if (nextScreen == "EndDungeonScreen")
                {
                    screen = new EndDungeonScreen(gs);
                }
                else
                {
                    RUN = false;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        
        BeginDrawing();
        ClearBackground(BLACK);
        screen->Draw();
        EndDrawing();
    }

    delete screen;
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
