#include "Effect/ItemEffect/DamageReductionEffect/DamageReductionEffect.hpp"
#include <cstdlib>
#include <ctime>

DamageReductionEffect::DamageReductionEffect() : ItemEffect("DamageReduction", "Reduces incoming damage.", 4, 30) {}

DamageReductionEffect::~DamageReductionEffect() {}


void DamageReductionEffect::apply(Unit *target)
{
    cout << target->getName() << " gains " << effectChance << "% damage reduction!" << endl;
    baseDefense = target->getDefense();
    target->setDefense(target->getDefense() + 5);
}

void DamageReductionEffect::remove(Unit *target)
{
    cout << "Damage Reduction effect on " << target->getName() << " has worn off!" << endl;
    target->setDefense(baseDefense);
}

Effect *DamageReductionEffect::clone() const
{
    return new DamageReductionEffect(*this);
}


DamageReductionEffect::DamageReductionEffect(const DamageReductionEffect& other) : ItemEffect (other) {}
