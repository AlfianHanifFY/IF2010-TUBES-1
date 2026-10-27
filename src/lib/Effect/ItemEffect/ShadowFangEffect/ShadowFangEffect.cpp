#include "Effect/ItemEffect/ShadowFangEffect/ShadowFangEffect.hpp"
#include <cstdlib>
#include <ctime>

ShadowFangEffect::ShadowFangEffect() : ItemEffect("ShadowFang", "Grants a chance to deal double damage.", 1, 0.6f) {}

ShadowFangEffect::~ShadowFangEffect() {}

void ShadowFangEffect::apply(Unit *target)
{
    this->originalAttackDamage = target->getAttackDamage();
    float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (chance < effectChance)
    {
        int strike = target->getAttackDamage() * 2;
        target->setAttackDamage(strike);
        cout << target->getName() << " receives Shadow Fang! -" << strike << " HP!" << endl;
    }
    else
    {

        cout << "Shadow Fang did not trigger." << endl;
    }
}

void ShadowFangEffect::tick(Unit *target)
{
    Effect::tick(target);
}
void ShadowFangEffect::remove(Unit *target)
{
    if (originalAttackDamage != -1)
    {
        target->setAttackDamage(originalAttackDamage);
    }
    cout << name << " effect on " << target->getName() << " has worn off." << endl;
    Effect::reset();
}

Effect *ShadowFangEffect::clone() const
{
    return new ShadowFangEffect(*this);
}

ShadowFangEffect::ShadowFangEffect(const ShadowFangEffect &other) : ItemEffect(other) {}