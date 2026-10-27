#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../GUI.hpp"

class Animation : public GUI
{
public:
    Animation(const std::string &basePath, float frameTime = 0.1f);
    ~Animation();

    void Play(const std::string &animationName);
    void Update();
    void Draw(Vector2 position, float scale = 1.0f);

    std::string getPath() const;

private:
    Texture2D texture;
    int totalFrames;
    int currentFrame;
    float frameTime;  
    float frameTimer; 
    std::string basePath;
    std::string currentAnim;
};

#endif
