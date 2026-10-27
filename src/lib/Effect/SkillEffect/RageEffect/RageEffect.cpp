#include "Effect/SkillEffect/RageEffect/RageEffect.hpp"

RageEffect::RageEffect(string name, string description, int duration, float effectChance, float statMultiplier) 
    : SkillEffect(name, description, duration, effectChance) {
    this->statMultiplier = statMultiplier;
    this->originalStrength = 0;
    this->originalIntelligence = 0;
    this->originalAgility = 0;
}

RageEffect::~RageEffect() {}


float RageEffect::getStatMultiplier() const {
    return statMultiplier;
}

void RageEffect::apply(Unit *target) {
    originalStrength = target->getStat(0);
    originalIntelligence = target->getStat(1);
    originalAgility = target->getStat(2);
    
    int newStrength = static_cast<int>(originalStrength * statMultiplier);
    int newIntelligence = static_cast<int>(originalIntelligence * statMultiplier);
    int newAgility = static_cast<int>(originalAgility * statMultiplier);


    target->setStat(0, newStrength);
    target->setStat(1, newIntelligence);
    target->setStat(2, newAgility);
    cout << target->getName() << " enters RAGE mode! All stats increased by " << (statMultiplier - 1.0) * 100 << "%!" << endl;
}

void RageEffect::tick(Unit *target) {
    cout << target->getName() << " is enraged!" << endl;
    Effect::tick(target);
}

void RageEffect::remove(Unit* target) {
    target->setStat(0, originalStrength);
    target->setStat(1, originalIntelligence);
    target->setStat(2, originalAgility);
    cout << target->getName() << "'s rage has subsided. Stats returned to normal." << endl;
}


RageEffect::RageEffect(const RageEffect &other) : SkillEffect(other) {
    this->statMultiplier = other.statMultiplier;
    this->originalStrength = other.originalStrength;
    this->originalIntelligence = other.originalIntelligence;
    this->originalAgility = other.originalAgility;
}

Effect* RageEffect::clone() const {
    return new RageEffect(*this);
}