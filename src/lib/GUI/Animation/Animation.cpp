#include "GUI/Animation/Animation.hpp"

Animation::Animation(const std::string &basePath, float frameTime)
    : basePath(basePath), texture({0}),
      totalFrames(0), currentFrame(0),
      frameTime(frameTime), frameTimer(0.0f)
{
}

Animation::~Animation()
{
    if (texture.id > 0)
    {
        UnloadTexture(texture);
    }
}

std::string Animation::getPath() const
{
    return basePath;
}

void Animation::Play(const std::string &animationName)
{
    if (currentAnim == animationName)
        return; 

    if (texture.id > 0)
    {
        UnloadTexture(texture);
    }

    std::string fullPath = basePath + "/" + animationName + ".png";
    texture = LoadTexture(fullPath.c_str());

    
    this->totalFrames = texture.width / 100;
    this->currentFrame = 0;
    this->frameTimer = 0.0f;
    this->currentAnim = animationName;
}

void Animation::Update()
{
    if (texture.id <= 0 || totalFrames <= 0)
        return;

    frameTimer += GetFrameTime();
    if (frameTimer >= frameTime)
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void Animation::Draw(Vector2 position, float scale)
{
    if (texture.id <= 0 || totalFrames <= 0)
        return;

    float frameWidth = static_cast<float>(texture.width) / totalFrames;
    float frameHeight = static_cast<float>(texture.height);

    Rectangle sourceRec = {
        frameWidth * currentFrame, 0.0f,
        frameWidth, frameHeight};

    Rectangle destRec = {
        position.x, position.y,
        frameWidth * scale, frameHeight * scale};

    Vector2 origin = {destRec.width / 2, destRec.height / 2};

    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
}
