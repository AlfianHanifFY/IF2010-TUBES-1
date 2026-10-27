#include "Effect/SkillEffect/HealEffect/HealEffect.hpp"

HealEffect::HealEffect(string name, string description, int duration, float effectChance, int baseHealValue)
    : SkillEffect(name, description, duration, effectChance)
{
    this->baseHealValue = baseHealValue;
    this->totalHealAmount = 0;
}

HealEffect::~HealEffect() {}


int HealEffect::getBaseHealValue() const
{
    return baseHealValue;
}

int HealEffect::getTotalHealAmount() const
{
    return totalHealAmount;
}


void HealEffect::setTotalHealAmount(int amount)
{
    this->totalHealAmount = amount;
}

void HealEffect::apply(Unit *target)
{
    totalHealAmount = baseHealValue * target->getStat(1);

    target->heal(totalHealAmount);

    cout << target->getName() << " uses Heal and recovers " << totalHealAmount << " HP!" << endl;
}

void HealEffect::remove(Unit *target)
{
    cout << getName() << " on " << target->getName() << " has worn off." << endl;
}


HealEffect::HealEffect(const HealEffect &other) : SkillEffect(other)
{
    this->baseHealValue = other.baseHealValue;
    this->totalHealAmount = other.totalHealAmount;
}

Effect *HealEffect::clone() const
{
    return new HealEffect(*this);
}