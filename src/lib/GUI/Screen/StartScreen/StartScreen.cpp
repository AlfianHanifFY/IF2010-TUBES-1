
#include "GUI/Screen/StartScreen/StartScreen.hpp"
#include "raylib.h"

StartScreen::StartScreen(GameState &GameState) : Screen(GameState),
                                                 loaGameStatetn(120, 210, 144, 42, "Start Game", BLACK),
                                                 infoBtn(120, 280, 144, 42, "Info", BLACK),
                                                 popUp()
{
}

StartScreen::~StartScreen()
{
}

void StartScreen::Draw()
{
    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/BackGround/Black_White_Border.png");
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("IF2010 Pemrograman Berorientasi Objek ...", 120, 150, 20, WHITE);
    DrawText("- (RPL) akuAdalahOOP ", 120, 170, 18, WHITE);

    loaGameStatetn.draw();
    infoBtn.draw();
    popUp.update();
    popUp.draw();

    if (loaGameStatetn.isClicked())
    {

        this->setNext("LoadScreen");
    }

    if (infoBtn.isClicked())
    {
        this->setNext("InfoScreen");
    }
}
