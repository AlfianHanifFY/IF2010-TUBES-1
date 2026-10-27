#include "Effect/ItemEffect/CrimsonCurseEffect/CrimsonCurseEffect.hpp"
#include <cstdlib>
#include <ctime>

CrimsonCurseEffect::CrimsonCurseEffect() : ItemEffect("CrimsonCurse", "Deals damage over time each turn.", 3, 20) {}

CrimsonCurseEffect::~CrimsonCurseEffect() {}


void CrimsonCurseEffect::apply(Unit *target)
{
    cout << target->getName() << " is bleeding! (" << effectChance << " damage per turn)" << endl;
}

void CrimsonCurseEffect::tick(Unit *target)
{
    cout << target->getName() << " suffers " << effectChance << " bleed damage." << endl;
    target->takeDamage(static_cast<int>(effectChance));
    Effect::tick(target);
}

void CrimsonCurseEffect::remove(Unit *target)
{
    cout << "Crimson Curse effect on " << target->getName() << " has worn off." << endl;
    Effect::reset();
}

Effect *CrimsonCurseEffect::clone() const
{
    return new CrimsonCurseEffect(*this);
}


CrimsonCurseEffect::CrimsonCurseEffect(const CrimsonCurseEffect &other) : ItemEffect(other) {}
