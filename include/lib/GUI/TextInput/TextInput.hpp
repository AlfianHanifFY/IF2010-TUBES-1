#ifndef TEXT_INPUT_HPP
#define TEXT_INPUT_HPP

#include <string>
#include "../GUI.hpp"

class TextInput : public GUI
{
public:
    TextInput(Vector2 position, int width, int maxLength);

    void Update();
    void Draw();
    std::string GetText() const;

private:
    Vector2 position;
    int width;
    int maxLength;
    std::string text;
    bool isActive;

    void HandleInput();
};

#endif
