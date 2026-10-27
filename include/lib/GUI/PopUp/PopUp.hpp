#ifndef POPUP_HPP
#define POPUP_HPP

#include "../GUI.hpp"

class PopUp : GUI
{
private:
    string text;
    double duration;
    Color color;
    double startTime;

public:
    PopUp();
    PopUp(std::string text, double duration, Color color);
    ~PopUp();
    bool isVisible;
    void show();
    void update();
    void draw();

    void trigger(std::string message, Color color, double duration);

    void setColor(Color color);
    void setText(std::string s);
};

#endif
