#include "Effect/ItemEffect/ShatterArmorEffect/ShatterArmorEffect.hpp"
#include <cstdlib>
#include <ctime>


ShatterArmorEffect::ShatterArmorEffect() : ItemEffect("ShatterArmor", "Reduces target's defense", 2, 15) {}

ShatterArmorEffect::~ShatterArmorEffect() {}


void ShatterArmorEffect::apply(Unit *target)
{
    int currentDefense = target->getStat(1);
    target->setStat(0, currentDefense - static_cast<int>(effectChance));
    cout << target->getName() << "'s defense reduced by " << effectChance << "!" << endl;
}

void ShatterArmorEffect::tick(Unit *target)
{
    Effect::tick(target);
}

void ShatterArmorEffect::remove(Unit *target)
{
    int currentDefense = target->getStat(1);
    target->setStat(0, currentDefense + static_cast<int>(effectChance));
    cout << "Armor Break effect on " << target->getName() << " has worn off!" << endl;
    Effect::reset();
}

Effect *ShatterArmorEffect::clone() const
{
    return new ShatterArmorEffect(*this);
}

ShatterArmorEffect::ShatterArmorEffect(const ShatterArmorEffect& other) : ItemEffect (other) {}