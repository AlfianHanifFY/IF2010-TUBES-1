#include "Effect/ItemEffect/HealthRegenEffect/HealthRegenEffect.hpp"
#include <cstdlib>
#include <ctime>

HealthRegenEffect::HealthRegenEffect() : ItemEffect("HealthRegen", "Regenerates health over time.", 3, 10) {}

HealthRegenEffect::~HealthRegenEffect() {}


void HealthRegenEffect::apply(Unit *target)
{
    cout << target->getName() << " gains Health Regen effect! (" << effectChance << " HP per turn)" << endl;
}

void HealthRegenEffect::tick(Unit *target)
{
    cout << target->getName() << " regenerates " << effectChance << " HP." << endl;
    target->heal(static_cast<int>(effectChance));
    Effect::tick(target);
}

void HealthRegenEffect::remove(Unit *target)
{
    cout << "Health Regen effect on " << target->getName() << " has worn off." << endl;
    reset();
}

Effect *HealthRegenEffect::clone() const
{
    return new HealthRegenEffect(*this);
}

HealthRegenEffect::HealthRegenEffect(const HealthRegenEffect &other) : ItemEffect(other) {}