#include "GUI/CharAnimation/CharAnimation.hpp"

CharAnimation::CharAnimation()
    : totalFrames(0), frameSpeed(0), scaleX(1.0f), scaleY(1.0f),
      position({0, 0}), currentFrame(0), frameCounter(0), isInitialized(false)
{
}

CharAnimation::~CharAnimation() {
    if (isInitialized) {
        UnloadTexture(texture);
    }
}

void CharAnimation::Init(const std::string &filePath, int totalFrames, int frameSpeed,
                         float scaleX, float scaleY, Vector2 position) {
    this->texture = LoadTexture(filePath.c_str());
    this->totalFrames = totalFrames;
    this->frameSpeed = frameSpeed;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->position = position;
    this->currentFrame = 0;
    this->frameCounter = 0;
    this->isInitialized = true;
}

void CharAnimation::UpdateChar() {
    if (!isInitialized) return;

    frameCounter++;
    if (frameCounter >= frameSpeed) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void CharAnimation::DrawChar() {
    if (!isInitialized) return;

    Rectangle frameRec = {
        (float)(currentFrame * (texture.width / totalFrames)),
        0.0f,
        (float)(texture.width / totalFrames),
        (float)texture.height
    };

    DrawTexturePro(texture, frameRec,
                   { position.x, position.y,
                     frameRec.width * scaleX,
                     frameRec.height * scaleY },
                   { 10.0f, 10.0f }, 0.0f, WHITE);
}
