#include "Effect/ItemEffect/ManaRegenEffect/ManaRegenEffect.hpp"
#include <cstdlib>
#include <ctime>

ManaRegenEffect::ManaRegenEffect()
    : ItemEffect("ManaRegen", "Regenerates mana over time.", 3, 20) {}

ManaRegenEffect::~ManaRegenEffect() {}


void ManaRegenEffect::apply(Unit *target)
{
    cout << target->getName() << " will regenerate " << effectChance << " mana per turn for " << duration << " turns." << endl;
}

void ManaRegenEffect::tick(Unit *target)
{
    cout << target->getName() << " regenerates " << effectChance << " mana." << endl;
    target->restoreMana(static_cast<int>(effectChance));
    Effect::tick(target);
}

void ManaRegenEffect::remove(Unit *target)
{
    cout << "Mana regeneration effect on " << target->getName() << " has worn off." << endl;
    Effect::reset();
}

Effect *ManaRegenEffect::clone() const
{
    return new ManaRegenEffect(*this);
}

ManaRegenEffect::ManaRegenEffect(const ManaRegenEffect &other) : ItemEffect(other) {}