#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

using namespace std;
#include <raylib.h>

class GUI
{
private:
    string assetPath;
    string type;

public:
    GUI();
    virtual ~GUI();

    void blinkText(string text, int x, int y, int font);
    void printInfo();
    void drawList(vector<string> list, int x, int y, int fontSize, Color color);
    void drawListCol(const vector<string> &list, int startX, int startY, int itemsPerColumn, int lineSpacing, int columnSpacing, int fontSize, Color color);
};

#endif
