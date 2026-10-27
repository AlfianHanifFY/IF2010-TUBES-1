#include "GUI/PopUp/PopUp.hpp"

PopUp::PopUp() : text(""), duration(3.5), color(RED), isVisible(false), startTime(0.0) {}

PopUp::PopUp(std::string text, double duration, Color color)
    : text(text), duration(duration), color(color), isVisible(false), startTime(0.0) {}

PopUp::~PopUp() {}

void PopUp::trigger(std::string message, Color color, double duration)
{
    this->text = message;
    this->color = color;
    this->duration = duration;
    this->startTime = GetTime();
    this->isVisible = true;
}

void PopUp::show()
{
    startTime = GetTime();
    isVisible = true;
}

void PopUp::update()
{
    if (isVisible && (GetTime() - startTime > duration))
    {
        isVisible = false;
    }
}

void PopUp::setText(std::string text)
{
    this->text = text;
}

void PopUp::setColor(Color color)
{
    this->color = color;
}

void PopUp::draw()
{
    if (!isVisible)
        return;

    int screenWidth = 960;
    int screenHeight = 540;

    int width = 640;
    int height = 120;
    int borderThickness = 4;

    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;

    
    DrawRectangle(x - borderThickness, y - borderThickness,
                  width + 2 * borderThickness, height + 2 * borderThickness, BLACK);

    
    DrawRectangle(x, y, width, height, color);

    
    DrawText("INFO:", x + 10, y + 10, 20, WHITE);

    
    DrawText(text.c_str(), x + 20, y + (height / 2) - 10, 20, BLACK);
}
