#ifndef SAVESCREEN_HPP
#define SAVESCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class SaveScreen : public Screen
{
private:
    Button submitBtn;
    TextInput configInput;
    PopUp popUp;
    Button exitBtn;

public:
    SaveScreen(GameState &GameState);
    ~SaveScreen() {}

    void Draw();
};

#endif
