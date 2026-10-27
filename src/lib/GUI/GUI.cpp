#include "GUI/GUI.hpp"

GUI::GUI()
{
    this->assetPath = "";
    this->type = "none";
}

GUI ::~GUI()
{
}

void GUI::printInfo()
{
    cout << "asset path: " << this->assetPath << endl;
    cout << "tipe: " << this->type << endl;
}

void GUI::drawList(vector<string> list, int x, int y, int fontSize, Color color)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        DrawText(list[i].c_str(), x, y + (i) * (fontSize + 2), fontSize, color);
    }
}

void GUI::blinkText(string s, int x, int y, int font)
{
    if (fmod(GetTime(), 1.0) < 0.5)
    {
        DrawText(s.c_str(), x, y, font, WHITE);
    }
}

void GUI::drawListCol(const vector<string> &list, int startX, int startY, int itemsPerColumn, int lineSpacing, int columnSpacing, int fontSize, Color color)
{
    for (size_t i = 0; i < list.size(); ++i)
    {
        int col = i / itemsPerColumn;
        int row = i % itemsPerColumn;
        int x = startX + col * columnSpacing;
        int y = startY + row * lineSpacing;
        DrawText(list[i].c_str(), x, y, fontSize, color);
    }
}