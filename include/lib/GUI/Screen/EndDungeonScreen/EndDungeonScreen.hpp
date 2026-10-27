#ifndef ENDDUNGEON_HPP
#define ENDDUNGEON_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class EndDungeonScreen : public Screen
{
private:
    Button TitleBtn;
    Texture2D bg;
    bool getPrize = false;
    PopUp popUp;
    vector<string> info;
    vector<string> itemInfo;

public:
    EndDungeonScreen(GameState &GameState);
    ~EndDungeonScreen();

    void Draw();
};

#endif
