#include "Unit/Mob/BasicMob/BasicMob.hpp"

BasicMob::BasicMob(string name, int level) : Mob(name, level)
{
}

BasicMob::~BasicMob() {}

void BasicMob::act(Unit *target)
{
    if (!target)
        return;

    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (currentHealth < maxHealth * 0.5 && chance <= 0.05)
    {
        useSkill(getSkill("Heal"), this);
        return;
    }

    attack(target);
}

string BasicMob::getType()
{
    return "Basic";
}