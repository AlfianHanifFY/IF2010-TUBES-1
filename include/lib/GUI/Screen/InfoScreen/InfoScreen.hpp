#ifndef INFOSCREEN_HPP
#define INFOSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class InfoScreen : public Screen
{
private:
    Button TitleBtn;

public:
    InfoScreen(GameState &GameState);
    ~InfoScreen();

    void Draw();
};

#endif
