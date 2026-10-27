#include "Effect/SkillEffect/SkillEffect.hpp"

SkillEffect::SkillEffect(string name, string description, int duration, float effectChance) : Effect(name, description, duration, effectChance)
{
}

SkillEffect::~SkillEffect() {}

SkillEffect::SkillEffect(const SkillEffect &other) : Effect(other) {}

string SkillEffect::getType() const
{
    return "Skill Effect";
}