#include "Effect/Effect.hpp"

Effect::Effect(string name, string description, int duration, float effectChance)
{
    this->name = name;
    this->description = description;
    this->duration = duration;
    this->remainingDuration = duration;
    this->effectChance = effectChance;
}

Effect::Effect(const Effect &other)
{
    this->name = other.name;
    this->description = other.description;
    this->duration = other.duration;
    this->remainingDuration = other.remainingDuration;
    this->effectChance = other.effectChance;
}

Effect::~Effect() {}

string Effect::getName() const
{
    return this->name;
}
string Effect::getDescription() const
{
    return this->description;
}
int Effect::getDuration() const
{
    return this->duration;
}
int Effect::getRemainingDuration() const
{
    return this->remainingDuration;
}
float Effect::getEffectChance() const
{
    return this->effectChance;
}


void Effect::setRemainingDuration(int duration)
{
    this->remainingDuration = duration;
}
void Effect::setEffectChance(float effectChance)
{
    this->effectChance = effectChance;
}


bool Effect::isExpired() const
{
    
    if (this->duration == -1 && this->remainingDuration == -1)
    {
        return false;
    }

    return this->remainingDuration <= 0;
}
void Effect::reduceDuration()
{
    if (remainingDuration > 0)
    {
        remainingDuration--;
    }
}

void Effect::reset()
{
    this->remainingDuration = this->duration;
}

void Effect::tick(Unit *target)
{
    reduceDuration();
}


bool Effect::operator==(const Effect &other) const
{
    return this->name == other.name && this->description == other.description && this->duration == other.duration && this->remainingDuration == other.remainingDuration && this->effectChance == other.effectChance;
}

void Effect::setPermanent()
{
    this->duration = -1;
    this->remainingDuration = -1;
}