#include "GUI/Screen/ExitScreen/ExitScreen.hpp"

ExitScreen::ExitScreen(GameState &GameState) : Screen(GameState), yesBtn(120, 210, 144, 42, "YES", BLACK),
                                               noBtn(120, 260, 144, 42, "NO", BLACK),
                                               cancelBtn(120, 310, 144, 42, "CANCEL", BLACK)

{
}

ExitScreen::~ExitScreen() {}

void ExitScreen::Draw()
{
    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/BackGround/Black_White_Border.png");
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("Are you sure ? you really want to exit ? like really ...? ", 120, 150, 20, WHITE);
    DrawText("At least save some progress? Right..? ", 120, 178, 20, WHITE);

    yesBtn.draw();
    noBtn.draw();
    cancelBtn.draw();

    if (yesBtn.isClicked())
    {
        this->setNext("SaveScreen");
    }

    if (noBtn.isClicked())
    {

        this->setNext("EXIT_PROGRAM");
    }

    if (cancelBtn.isClicked())
    {
        this->setNext("HomeScreen");
    }
}
