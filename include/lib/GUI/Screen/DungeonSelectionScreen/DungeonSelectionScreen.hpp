#ifndef DUNSELSCREEN_HPP
#define DUNSELSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class DungeonSelectionScreen : public Screen
{
private:
    Button ERankBtn;
    Button CRankBtn;
    Button DRankBtn;
    Button BRankBtn;
    Button ARankBtn;
    Button SRankBtn;
    Button SpecialRankBtn;
    Button ExitBtn;

    PopUp popUp;

public:
    DungeonSelectionScreen(GameState &GameState);
    ~DungeonSelectionScreen();

    void Draw();
};

#endif
