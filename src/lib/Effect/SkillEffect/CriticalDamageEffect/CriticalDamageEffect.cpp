#include "Effect/SkillEffect/CriticalDamageEffect/CriticalDamageEffect.hpp"

CriticalDamageEffect::CriticalDamageEffect(string name, string description, int duration, float effectChance, float damageMultiplier)
    : SkillEffect(name, description, duration, effectChance)
{
    this->damageMultiplier = damageMultiplier;
}

CriticalDamageEffect::~CriticalDamageEffect() {}


float CriticalDamageEffect::getDamageMultiplier() const
{
    return damageMultiplier;
}

void CriticalDamageEffect::apply(Unit *target)
{
    baseAttackDamage = target->getAttackDamage();
    target->setAttackDamage(baseAttackDamage * damageMultiplier);
    cout << "Critical hit! " << target->getName() << " receives " << damageMultiplier << "x damage!" << endl;
}

void CriticalDamageEffect::remove(Unit *target)
{
    target->setAttackDamage(baseAttackDamage);
    cout << "Critical damage effect on " << target->getName() << " has worn off." << endl;
}


CriticalDamageEffect::CriticalDamageEffect(const CriticalDamageEffect &other) : SkillEffect(other)
{
    this->damageMultiplier = other.damageMultiplier;
    this->baseAttackDamage = other.baseAttackDamage;
}

Effect *CriticalDamageEffect::clone() const
{
    return new CriticalDamageEffect(*this);
}