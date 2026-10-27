#include "Effect/ItemEffect/SpeedBoostEffect/SpeedBoostEffect.hpp"
#include <cstdlib>
#include <ctime>

SpeedBoostEffect::SpeedBoostEffect()
    : ItemEffect("SpeedBoost", "Increases agility temporarily.", 1, 10) {}

SpeedBoostEffect::~SpeedBoostEffect() {}

void SpeedBoostEffect::apply(Unit *target)
{
    cout << target->getName() << " gains Speed Boost! (+" << effectChance << " agility)" << endl;
    int agility = target->getStat(2) + static_cast<int>(effectChance);
    target->setStat(2, agility);
}

void SpeedBoostEffect::tick(Unit *target)
{
    Effect::tick(target);
}

void SpeedBoostEffect::remove(Unit *target)
{
    int agility = target->getStat(2) - static_cast<int>(effectChance);
    target->setStat(2, agility);
    cout << "Speed Boost on " << target->getName() << " has worn off." << endl;
    reset();
}

Effect *SpeedBoostEffect::clone() const
{
    return new SpeedBoostEffect(*this);
}

SpeedBoostEffect::SpeedBoostEffect(const SpeedBoostEffect &other) : ItemEffect(other) {}