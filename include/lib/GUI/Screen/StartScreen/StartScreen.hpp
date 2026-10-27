#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class StartScreen : public Screen
{
private:
    Button loaGameStatetn;
    Button infoBtn;
    PopUp popUp;

public:
    StartScreen(GameState &GameState);
    ~StartScreen();

    virtual void Draw();
};

#endif
