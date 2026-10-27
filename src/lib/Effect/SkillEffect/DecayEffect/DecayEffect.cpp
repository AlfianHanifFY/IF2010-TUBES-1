#include "Effect/SkillEffect/DecayEffect/DecayEffect.hpp"

DecayEffect::DecayEffect(string name, string description, int duration, float effectChance, int damage) : SkillEffect(name, description, duration, effectChance)
{
    this->damage = damage;
}

DecayEffect::~DecayEffect() {}

void DecayEffect::apply(Unit *target)
{
    cout << getName() << " applies " << getName() << " to " << target->getName() << "!" << endl;
}

void DecayEffect::tick(Unit *target)
{
    int currentTurn = getDuration() - getRemainingDuration() + 1;
    int currentDamage = damage * currentTurn;
    
    cout << target->getName() << " takes " << currentDamage << " damage from " << getName() << " (Turn " << currentTurn << ")!" << endl;
    
    target->takeDamage(currentDamage);
    Effect::tick(target);
}

void DecayEffect::remove(Unit *target)
{
    cout << "Decay effect on " << target->getName() << " has worn off." << endl;
}


DecayEffect::DecayEffect(const DecayEffect& other) : SkillEffect(other) {
    this->damage = other.damage;
}

Effect* DecayEffect::clone() const {
    return new DecayEffect(*this);
}