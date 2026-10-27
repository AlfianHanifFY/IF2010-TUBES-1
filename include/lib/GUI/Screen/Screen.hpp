#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
using namespace std;

#include "../GUI.hpp"

#include "../Button/Button.hpp"
#include "../Animation/Animation.hpp"
#include "../TextInput/TextInput.hpp"
#include "../PopUp/PopUp.hpp"
#include "GameState/GameState.hpp"
#include <string>

class Screen : public GUI
{
private:
    string next;
    GameState &gs;

public:
    Screen(GameState &gs);
    void setNext(string s);
    void clearNext();
    string getNext();
    virtual ~Screen();

    virtual void Draw() = 0;

    void printInfo();

protected:
    GameState &getGameState();
};

#endif
