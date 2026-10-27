#include "Effect/SkillEffect/SlowEffect/SlowEffect.hpp"

SlowEffect::SlowEffect(string name, string description, int duration, float effectChance, float agilityMultiplier) : SkillEffect(name, description, duration, effectChance)
{
    this->agilityMultiplier = agilityMultiplier;
}

SlowEffect::~SlowEffect() {}

void SlowEffect::apply(Unit *target)
{
    cout << getName() << " applies " << getName() << " to " << target->getName() << "!" << endl;
    this->baseAgility = target->getStat(2);
    target->setStat(2, baseAgility * agilityMultiplier);
}

void SlowEffect::remove(Unit *target)
{
    cout << "Slow effect on " << target->getName() << " has worn off." << endl;
    target->setStat(2, baseAgility);
    
}


SlowEffect::SlowEffect(const SlowEffect &other) : SkillEffect(other)
{
    this->baseAgility = other.baseAgility;
    this->agilityMultiplier = other.agilityMultiplier;
}

Effect *SlowEffect::clone() const
{
    return new SlowEffect(*this);
}