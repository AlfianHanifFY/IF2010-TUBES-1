#include "GUI/Screen/Screen.hpp"

Screen::Screen(GameState &GameStateRef) : gs(GameStateRef)
{
    this->next = "none";
}

void Screen::setNext(string next)
{
    this->next = next;
}

void Screen::clearNext()
{
    this->next = "none";
}

string Screen::getNext()
{
    return this->next;
}

void Screen::printInfo()
{
    cout << "this is screen :D";
}
GameState &Screen::getGameState()
{
    return gs;
}

Screen::~Screen() {}