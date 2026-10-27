#include "Unit/Mob/BasicMob/Goblin/Goblin.hpp"

Goblin::Goblin(int level) : BasicMob("Goblin", level)
{
    
    
    Skill *sneakyStabSkill = new Skill("Sneaky Stab", 30, 0, 2 * attackDamage);
    addSkill(sneakyStabSkill);

    setAssets("./Assets/Unit/Mob/Basic/Goblin");
}

Goblin::~Goblin() {}

void Goblin::act(Unit *target)
{
    if (!target)
        return;

    
    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (currentHealth < maxHealth * 0.5 && chance <= 0.05)
    {
        useSkill(getSkill("Heal"), this);
        return;
    }

    
    chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= 0.2)
    {
        useSkill(getSkill("Sneaky Stab"), target);
        return;
    }

    attack(target);
}