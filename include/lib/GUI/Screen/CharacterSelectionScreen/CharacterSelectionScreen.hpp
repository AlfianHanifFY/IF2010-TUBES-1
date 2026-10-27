#ifndef CHARSELSCREEN_HPP
#define CHARSELSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"
#include "../../Button/Button.hpp"
#include "../../CharAnimation/CharAnimation.hpp"

class CharacterSelectionScreen : public Screen
{
private:
    Button FighterBtn;
    Button MageBtn;
    Button AssasinBtn;
    Button NecromancerBtn;
    Button BersekerBtn;
    Button ExitBtn;
    TextInput nameInput;
    PopUp popUp;

public:
    CharacterSelectionScreen(GameState &GameState); 
    ~CharacterSelectionScreen();

    void Draw();
};

#endif
