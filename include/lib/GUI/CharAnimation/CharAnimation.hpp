#ifndef CHARANIMATION_HPP
#define CHARANIMATION_HPP

#include "../GUI.hpp"
class CharAnimation : public GUI
{
private:
    Texture2D texture;
    int totalFrames;
    int frameSpeed;
    float scaleX;
    float scaleY;
    Vector2 position;
    int currentFrame;
    int frameCounter;
    bool isInitialized; 

public:
    CharAnimation(); 
    ~CharAnimation();

    void Init(const std::string &filePath, int totalFrames, int frameSpeed,
              float scaleX, float scaleY, Vector2 position);

    void UpdateChar();
    void DrawChar();
};

#endif
