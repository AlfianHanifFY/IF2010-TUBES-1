#include "Effect/ItemEffect/ReflectEffect/ReflectEffect.hpp"
#include <cstdlib>
#include <ctime>

ReflectEffect::ReflectEffect()
    : ItemEffect("Reflect", "Reflects some of the damage to the attacker", 1, 10)
{
    this->reflectPercentage = 0.05;
}

ReflectEffect::~ReflectEffect() {}


void ReflectEffect::apply(Unit *target)
{
    cout << target->getName() << " is now reflecting " << effectChance << "% of damage taken!" << endl;
}

void ReflectEffect::tick(Unit *target)
{
    Effect::tick(target);
}

void ReflectEffect::remove(Unit *target)
{
    cout << "Reflect effect on " << target->getName() << " has worn off!" << endl;
    Effect::reset();
}

Effect *ReflectEffect::clone() const
{
    return new ReflectEffect(*this);
}


ReflectEffect::ReflectEffect(const ReflectEffect& other) : ItemEffect (other) {}