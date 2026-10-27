#ifndef EXITSCREEN_HPP
#define EXITSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class ExitScreen : public Screen
{
private:
    Button yesBtn;
    Button noBtn;
    Button cancelBtn;

public:
    ExitScreen(GameState &GameState);
    ~ExitScreen();

    void Draw();
};

#endif
