#include "Effect/ItemEffect/DullingCurseEffect/DullingCurseEffect.hpp"
#include <cstdlib>
#include <ctime>

DullingCurseEffect::DullingCurseEffect() : ItemEffect("DullingCurse", "Reduces the unit's attack power temporarily.", 2, 10) {}

DullingCurseEffect::~DullingCurseEffect() {}


void DullingCurseEffect::apply(Unit *target)
{
    cout << target->getName() << " is weakened! Attack reduced by " << effectChance << "." << endl;
    int currentAttack = target->getAttackDamage();
    target->setAttackDamage(currentAttack - static_cast<int>(effectChance));
}

void DullingCurseEffect::tick(Unit *target)
{
    Effect::tick(target);
}

void DullingCurseEffect::remove(Unit *target)
{
    int currentAttack = target->getAttackDamage();
    target->setAttackDamage(currentAttack + static_cast<int>(effectChance)); 
    cout << "Weaken effect on " << target->getName() << " has worn off." << endl;
    Effect::reset();
}

Effect *DullingCurseEffect::clone() const
{
    return new DullingCurseEffect(*this);
}


DullingCurseEffect::DullingCurseEffect(const DullingCurseEffect& other) : ItemEffect (other) {}
