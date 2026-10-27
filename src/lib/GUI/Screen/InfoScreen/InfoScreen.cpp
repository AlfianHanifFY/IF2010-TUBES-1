#include "GUI/Screen/InfoScreen/InfoScreen.hpp"

InfoScreen::InfoScreen(GameState &GameState) : Screen(GameState), TitleBtn(120, 300, 144, 42, "Back To Title", BLACK)
{
}

InfoScreen::~InfoScreen() {}

void InfoScreen::Draw()
{
    ClearBackground(LIGHTGRAY);
    Texture2D bg = LoadTexture("./Assets/BackGround/Black_White_Border.png");
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("Tugas BesarIF2010 Pemrograman Berorientasi Objek ...", 120, 150, 20, WHITE);
    DrawText("- (RPL) akuAdalahOOP ", 120, 170, 16, WHITE);
    DrawText("     +(13523073) Alfian Hanif Fitri Yustanto ", 120, 210, 18, WHITE);
    DrawText("     +(13523091) Carlo Angkisan ", 120, 230, 18, WHITE);
    DrawText("     +(13523105) Heleni Gratia M Tampubulon ", 120, 250, 18, WHITE);
    DrawText("     +(13523121) Ahmad Wicaksono ", 120, 270, 18, WHITE);

    TitleBtn.draw();

    if (TitleBtn.isClicked())
    {
        setNext("StartScreen");
    }
}
