#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../GUI.hpp"

class Button : public GUI
{
private:
    int x, y;          
    int width, height; 
    Color color;       
    const char *text;  
    bool hover;
    Sound hoverSfx;
    Sound clickSfx;
    bool wasHovering = false;

public:
    Button(int x, int y, int width, int height);
    Button(int x, int y, int width, int height, const char *text, Color color = DARKGRAY);
    ~Button();
    void draw(); 
    bool isClicked();
    void printInfo(); 
};

#endif
