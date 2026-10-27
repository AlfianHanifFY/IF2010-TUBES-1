#ifndef LOADSCREEN_HPP
#define LOADSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class LoadScreen : public Screen
{
private:
    Button submitBtn;
    TextInput configInput;
    PopUp popUp;

    bool valid;

public:
    LoadScreen(GameState &GameState);
    ~LoadScreen() {}

    void Draw();
};

#endif
