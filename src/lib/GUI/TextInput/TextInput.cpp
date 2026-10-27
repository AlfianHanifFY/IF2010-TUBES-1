#include "GUI/TextInput/TextInput.hpp"

TextInput::TextInput(Vector2 pos, int width, int maxLen)
    : position(pos), width(width), maxLength(maxLen), text(""), isActive(false) {}

void TextInput::Update()
{
    Rectangle bounds = {position.x, position.y, (float)width, 40};
    if (CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isActive = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isActive = false;
    }

    if (isActive)
    {
        HandleInput();
    }
}

void TextInput::Draw()
{
    
    
    
    DrawText(text.c_str(), position.x + 5, position.y + 5, 20, BLACK);
}

std::string TextInput::GetText() const
{
    return text;
}

void TextInput::HandleInput()
{
    int key = GetCharPressed();
    int len = text.length();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (len < maxLength))
        {
            text += static_cast<char>(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())
    {
        text.pop_back();
    }
}
