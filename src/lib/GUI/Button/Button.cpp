#include "GUI/Button/Button.hpp"
#include <iostream>

using namespace std;

Button::Button(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = "";
    this->color = {0, 0, 0, 0};
    this->hover = false;

    hoverSfx = LoadSound("./Assets/sfx/ui/hover.wav");
    clickSfx = LoadSound("./Assets/sfx/ui/confirm.wav");
    wasHovering = false;
}
Button::Button(int x, int y, int width, int height, const char *text, Color color)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->color = color;
    this->hover = false;

    hoverSfx = LoadSound("./Assets/sfx/ui/hover.wav");
    clickSfx = LoadSound("./Assets/sfx/ui/confirm.wav");
    wasHovering = false;
}

Button::~Button()
{
    cout << "Button at position (" << x << ", " << y << ") destroyed." << endl;
}


void Button::draw()
{
    

    int w, h, fx, fy;
    double k;
    if (hover)
    {
        if (!wasHovering)
        {
            PlaySound(hoverSfx);
            cout << "sound" << endl;
        }
        wasHovering = true;
        w = width + 6;
        h = height + 6;
        fx = x - 3;
        fy = y - 3;
        k = 1.1;
    }
    else
    {
        wasHovering = false;
        w = width;
        h = height;
        fx = x;
        fy = y;
        k = 1;
    }

    DrawRectangle(fx, fy, w, h, color);

    
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 20, 2);
    float textX = fx + (w - textSize.x) / 2;
    float textY = fy + (h - textSize.y) / 2;

    DrawText(text, textX, textY, 20 * k, WHITE);
}


void Button::printInfo()
{
    
    GUI::printInfo();
    
    cout << "Button position: (" << x << ", " << y << ") with size "
         << width << "x" << height << endl;
}

bool Button::isClicked()
{
    
    Vector2 mousePos = GetMousePosition();

    
    if (mousePos.x >= x && mousePos.x <= x + width &&
        mousePos.y >= y && mousePos.y <= y + height)
    {
        hover = true;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(clickSfx);
            DrawText(TextFormat("%s clicked !", this->text), 0, 0, 20, BLACK);
            return true; 
        }
    }
    else
    {
        hover = false;
    }

    return false; 
}